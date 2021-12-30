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


###########################################################
# Functions
###########################################################
function(lsp_sever_set_target_options target)

    set_property(TARGET ${target} PROPERTY CXX_STANDARD_REQUIRED ON)

    # Enable C++17 (Required)
    set_property(TARGET ${target} PROPERTY CXX_STANDARD 17)

    set_property(TARGET ${target} PROPERTY CXX_EXTENSIONS OFF)


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
        target_link_libraries(${target} PUBLIC "-fsanitize=address")
    elseif(LSP_SEVER_MSAN)
        target_compile_options(${target} PUBLIC "-fsanitize=memory")
        target_link_libraries(${target} PUBLIC "-fsanitize=memory")
    elseif(LSP_SEVER_TSAN)
        target_compile_options(${target} PUBLIC "-fsanitize=thread")
        target_link_libraries(${target} PUBLIC "-fsanitize=thread")
    endif()

    # Error on undefined symbols
    # if(NOT MSVC)
    #     target_compile_options(${target} PRIVATE "-Wl,--no-undefined")
    # endif()

endfunction()



###########################################################
# Targets
###########################################################

# lsp
add_executable(lpg-language-server)

### Includes
target_include_directories(lpg-language-server
        PUBLIC ${LSP_SEVER_INCLUDE_DIR})

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

add_subdirectory(third_party/LspCpp)
add_subdirectory(third_party/LPG-cpp-runtime)
target_include_directories(lpg-language-server PRIVATE cpplpg2 lspcpp)
target_link_libraries(lpg-language-server PRIVATE cpplpg2 lspcpp)

### Sources
set(LSP_SEVER_LIST
        LPG-language-server/src/ASTUtils.cpp
        LPG-language-server/src/code.cpp
        LPG-language-server/src/CompilationUnit.cpp
        LPG-language-server/src/LPG-language-server.cpp

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

