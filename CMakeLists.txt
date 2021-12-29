cmake_minimum_required(VERSION 3.8)

if(POLICY CMP0025)
    # detect Apple's Clang
    cmake_policy(SET CMP0025 NEW)
endif()
if(POLICY CMP0054)
    cmake_policy(SET CMP0054 NEW)
endif()

set(LIB_MAJOR_VERSION "1")
set(LIB_MINOR_VERSION "0")
set(LIB_PATCH_VERSION "0")
set(LIB_VERSION_STRING "${LIB_MAJOR_VERSION}.${LIB_MINOR_VERSION}.${LIB_PATCH_VERSION}")

# Without this, paths are not relative in the sources list
cmake_policy(SET CMP0076 NEW)
project(lpg-language-server VERSION "${LIB_VERSION_STRING}" LANGUAGES CXX C)


# compile in RelWithDebInfo  mode by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif()

###########################################################
# Options
###########################################################
function (option_if_not_defined name description default)
    if(NOT DEFINED ${name})
        option(${name} ${description} ${default})
    endif()
endfunction()

option_if_not_defined(USE_SYSTEM_RAPIDJSON "Use system RapidJSON instead of the git submodule if exists" OFF)
option_if_not_defined(LSP_SEVER_WARNINGS_AS_ERRORS "Treat warnings as errors" OFF)
option_if_not_defined(LSP_SEVER_BUILD_EXAMPLES "Build example applications" OFF)
option_if_not_defined(LSP_SEVER_BUILD_FUZZER "Build fuzzer" OFF)
option_if_not_defined(LSP_SEVER_ASAN "Build lsp-sever with address sanitizer" OFF)
option_if_not_defined(LSP_SEVER_MSAN "Build lsp-sever with memory sanitizer" OFF)
option_if_not_defined(LSP_SEVER_TSAN "Build lsp-sever with thread sanitizer" OFF)
option_if_not_defined(LSP_SEVER_INSTALL "Create lsp-sever install target" OFF)

###########################################################
# Directories
###########################################################
function (set_if_not_defined name value)
    if(NOT DEFINED ${name})
        set(${name} ${value} PARENT_SCOPE)
    endif()
endfunction()

set(LSP_SEVER_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/LPG-language-server/src)
set(LSP_SEVER_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/LPG-language-server/src)


macro(lspcpp_set_target_options_with_nuget_pkg target id version)
    if (CMAKE_GENERATOR MATCHES "Visual Studio.*")
        target_link_libraries(${target}  ${CMAKE_BINARY_DIR}/packages/${id}.${version}/build/${id}.targets)
    else()
        message(FATAL_ERROR "NUGET package only use in Visual Studio")
    endif()

endmacro()

macro(INSTALL_NUGET id version)
    if (CMAKE_GENERATOR MATCHES "Visual Studio.*")
        unset(nuget_cmd)
        list(APPEND nuget_cmd install ${id} -Prerelease -Version ${version} -OutputDirectory ${CMAKE_BINARY_DIR}/packages)
        message("excute nuget install:${nuget_cmd}")
        execute_process(COMMAND nuget ${nuget_cmd} ENCODING AUTO)
    else()
        message(FATAL_ERROR "INSTALL_NUGET only use in Visual Studio")
    endif()

endmacro()
###########################################################
# Functions
###########################################################
function(lsp_sever_set_target_options target)

    set_property(TARGET ${target} PROPERTY CXX_STANDARD_REQUIRED ON)

    # Enable C++17 (Required)
    set_property(TARGET ${target} PROPERTY CXX_STANDARD 17)

    set_property(TARGET ${target} PROPERTY CXX_EXTENSIONS OFF)

    if (CMAKE_GENERATOR MATCHES "Visual Studio.*")
        lspcpp_set_target_options_with_nuget_pkg(${target} boost 1.76.0.0)
        lspcpp_set_target_options_with_nuget_pkg(${target} boost_chrono-vc141 1.76.0.0)
        lspcpp_set_target_options_with_nuget_pkg(${target} boost_date_time-vc141 1.76.0.0)
        lspcpp_set_target_options_with_nuget_pkg(${target} boost_filesystem-vc141 1.76.0.0)
        lspcpp_set_target_options_with_nuget_pkg(${target} boost_program_options-vc141 1.76.0.0)
        lspcpp_set_target_options_with_nuget_pkg(${target} boost_system-vc141 1.76.0.0)
        lspcpp_set_target_options_with_nuget_pkg(${target} boost_thread-vc141 1.76.0.0)
    endif()

    # Enable all warnings
    if(MSVC)
        target_compile_options(${target} PRIVATE "-W4")
    else()
        target_compile_options(${target} PRIVATE "-Wall")
    endif()

    # Disable specific, pedantic warnings
    if(MSVC)
        target_compile_options(${target} PRIVATE
                "-D_CRT_SECURE_NO_WARNINGS"

                # Warnings from nlohmann/json headers.
                "/wd4267" # 'argument': conversion from 'size_t' to 'int', possible loss of data
                "/bigobj" # for visual studio 2022 x64 or later.
                )
    endif()

    # Add define for JSON library in use
    set_target_properties(${target} PROPERTIES
            COMPILE_DEFINITIONS "LSP_SEVER_JSON_${LSP_SEVER_JSON_LIBRARY_UPPER}=1"
            )

    # Treat all warnings as errors
    if(LSP_SEVER_WARNINGS_AS_ERRORS)
        if(MSVC)
            target_compile_options(${target} PRIVATE "/WX")
        else()
            target_compile_options(${target} PRIVATE "-Werror")
        endif()
    endif(LSP_SEVER_WARNINGS_AS_ERRORS)

    if(LSP_SEVER_ASAN)
        target_compile_options(${target} PUBLIC "-fsanitize=address")
        target_link_libraries(${target} "-fsanitize=address")
    elseif(LSP_SEVER_MSAN)
        target_compile_options(${target} PUBLIC "-fsanitize=memory")
        target_link_libraries(${target} "-fsanitize=memory")
    elseif(LSP_SEVER_TSAN)
        target_compile_options(${target} PUBLIC "-fsanitize=thread")
        target_link_libraries(${target} "-fsanitize=thread")
    endif()

    # Error on undefined symbols
    # if(NOT MSVC)
    #     target_compile_options(${target} PRIVATE "-Wl,--no-undefined")
    # endif()

endfunction()


# Libraries

###########################################################
# boost library
###########################################################
if (CMAKE_GENERATOR MATCHES "Visual Studio.*")
    INSTALL_NUGET(boost 1.76.0.0)
    INSTALL_NUGET(boost_chrono-vc141 1.76.0.0)
    INSTALL_NUGET(boost_date_time-vc141 1.76.0.0)
    INSTALL_NUGET(boost_filesystem-vc141 1.76.0.0)
    INSTALL_NUGET(boost_program_options-vc141 1.76.0.0)
    INSTALL_NUGET(boost_system-vc141 1.76.0.0)
    INSTALL_NUGET(boost_thread-vc141 1.76.0.0)
else()
    if(LSP_SEVER_BUILD_EXAMPLES)
        find_package(Boost COMPONENTS date_time  chrono filesystem system thread program_options)
    else()
        find_package(Boost)
    endif()
    if(NOT Boost_FOUND)
        if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
            message(FATAL_ERROR "Can't find boost,lease build boost and install it or install boost with : brew install boost")
        elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
            message(FATAL_ERROR "Can't find boost,please build boost and install it. or install boost with : sudo apt-get install libboost-dev")
        endif()
    endif()
endif()


###########################################################
# JSON library
###########################################################
if(USE_SYSTEM_RAPIDJSON)
    set(RapidJSON_MIN_VERSION "1.1.0")
    find_package(RapidJSON ${RapidJSON_MIN_VERSION} QUIET)
    if(NOT DEFINED RapidJSON_INCLUDE_DIRS AND DEFINED RAPIDJSON_INCLUDE_DIRS)
        set(RapidJSON_INCLUDE_DIRS "${RAPIDJSON_INCLUDE_DIRS}")
    endif()
endif()
if(NOT RapidJSON_FOUND)
    if(EXISTS "${CMAKE_SOURCE_DIR}/third_party/rapidjson/include")
        message(STATUS "Using local RapidJSON")
        set(RapidJSON_INCLUDE_DIRS third_party/rapidjson/include)
    else()
        message(STATUS "Please initialize rapidJSON git submodule as currently installed version is to old:")
        message(STATUS "git submodule init && git submodule update")
        message(FATAL_ERROR "RapidJSON version is likely too old.")
    endif()
endif()


###########################################################
# Targets
###########################################################

# lsp
add_executable(lpg-language-server)

### Includes
target_include_directories(lpg-language-server
        PUBLIC ${LSP_SEVER_INCLUDE_DIR}  ${Boost_INCLUDE_DIRS})

set(LSP_SEVER_THIRD_PARTY_DIR
        ${RapidJSON_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/loguru)

foreach(include_dir  ${LSP_SEVER_THIRD_PARTY_DIR})
    get_filename_component(include_dir_realpath ${include_dir} REALPATH)
    # Don't add as SYSTEM if they are in CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES.
    # It would reorder the system search paths and cause issues with libstdc++'s
    # use of #include_next.
    if(NOT "${include_dir_realpath}" IN_LIST CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES)
        target_include_directories(lpg-language-server SYSTEM PRIVATE ${include_dir})
    endif()
endforeach()


target_include_directories(lpg-language-server  PRIVATE network-uri)

if (CMAKE_GENERATOR MATCHES "Visual Studio.*")

    target_include_directories(lpg-language-server PRIVATE

            ${CMAKE_CURRENT_SOURCE_DIR}/third_party/LspCpp/include

            ${CMAKE_CURRENT_SOURCE_DIR}/third_party/LPG-cpp-runtime/include
            )

    target_link_libraries(lpg-language-server PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/lib/liblspcpp.lib
            ${CMAKE_CURRENT_SOURCE_DIR}/lib/libcpplpg2.lib
            ${CMAKE_CURRENT_SOURCE_DIR}/lib/libnetwork-uri.lib
            )

else()
    add_subdirectory(third_party/LspCpp)
    add_subdirectory(third_party/LPG-cpp-runtime)
    target_include_directories(lpg-language-server PRIVATE cpplpg2 lspcpp)
    target_link_libraries(lpg-language-server PRIVATE cpplpg2 lspcpp)
endif()
### Sources
set(LSP_SEVER_LIST
        LPG-language-server/src/ASTUtils.cpp
        LPG-language-server/src/code.cpp
        LPG-language-server/src/CompilationUnit.cpp
        LPG-language-server/src/LPG-language-server.cpp
        LPG-language-server/src/timer.cpp
        LPG-language-server/src/WorkSpaceManager.cpp

        LPG-language-server/src/message/Analysis.cpp
        LPG-language-server/src/message/CompletionHandler.cpp
        LPG-language-server/src/message/DocumentColorHandler.cpp
        LPG-language-server/src/message/DocumentFormatHandler.cpp
        LPG-language-server/src/message/DocumentSymbolHandler.cpp
        LPG-language-server/src/message/FoldingRangeHandler.cpp

        LPG-language-server/src/message/HoverHandler.cpp
        LPG-language-server/src/message/NavigateToDefinitionHandler.cpp
        LPG-language-server/src/message/Refactoring.cpp
        LPG-language-server/src/message/ReferencesHandler.cpp
        LPG-language-server/src/message/SemanticTokensHandler.cpp

        LPG-language-server/src/parser/base.cpp
        LPG-language-server/src/parser/Binding.cpp
        LPG-language-server/src/parser/buffer.cpp
        LPG-language-server/src/parser/dfa.cpp
        LPG-language-server/src/parser/grammar.cpp
        LPG-language-server/src/parser/JikesPGOptionDesc.cpp
        LPG-language-server/src/parser/JikesPGOptionParser.cpp
        LPG-language-server/src/parser/JikesPGOptions.cpp
        LPG-language-server/src/parser/JikesPGOptionValues.cpp
        LPG-language-server/src/parser/JikesPGUtil.cpp
        LPG-language-server/src/parser/JiksPGControl.cpp
        LPG-language-server/src/parser/JiksPgOption.cpp

        LPG-language-server/src/parser/LPGParser_top_level_ast.cpp
        LPG-language-server/src/parser/LPGParser.cpp

        LPG-language-server/src/parser/pda.cpp
        LPG-language-server/src/parser/produce.cpp
        LPG-language-server/src/parser/resolve.cpp
        LPG-language-server/src/parser/sp.cpp

        )

target_sources(lpg-language-server PRIVATE
        ${LSP_SEVER_LIST})

### Compile options

lsp_sever_set_target_options(lpg-language-server)


# install
if(LSP_SEVER_INSTALL)
    include(GNUInstallDirs)
    
    install(TARGETS lpg-language-server
            EXPORT lpg-language-server-targets
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
            )
    
endif()

