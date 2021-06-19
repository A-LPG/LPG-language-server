#include "JiksPgOption.h"
#include "IcuUtil.h"
#include <IPrsStream.h>

#include "JiksPGControl.h"
//
// Change the following static to "true" to enable the new options-processing code
//
static bool NEW_OPTIONS_CODE = false;

const char* JiksPgOption::GetPrefix(const char* filename)
{
    const char* forward_slash = strrchr(filename, '/'),
        * backward_slash = strrchr(filename, '\\'),
        * slash = (forward_slash > backward_slash ? forward_slash : backward_slash),
        * colon = strrchr(filename, ':'), // Windows files may use format: d:filename
        * separator = (colon > slash ? colon : slash);
    int length = (separator == NULL ? 0 : separator - filename + 1);
    return NewString(filename, length);
}

//
//
//
void JiksPgOption::ProcessPath(Tuple<const char*>& list, const char* path, const char* start_directory)
{
    int allocation_length = strlen(path) + (start_directory == NULL ? 0 : strlen(start_directory));
    if (allocation_length == 0)
        return;

    char* str = NewString(allocation_length + 3); // 2 semicolons 1 for terminating \0
    if (start_directory != NULL)
    {
        strcpy(str, start_directory);
        strcat(str, ";");
    }
    else *str = '\0';
    strcat(str, path);
    NormalizeSlashes(str);

    int length;
    for (length = strlen(str) - 1; length >= 0 && IsSpace(str[length]); length--)
        ; // remove trailing spaces
    if (length < 0)
        length = 0;

    if (str[length] != ';') // make sure that the path ends with a terminating semicolon
        str[++length] = ';';
    str[++length] = NULL_CHAR;

    list.reset();
    list.Next() = str;
    for (int i = 0; i < length; i++)
    {
        if (str[i] == ';')
        {
            str[i] = '\0';
            if (str[i + 1] != '\0')
                list.Next() = &(str[i + 1]);
        }
    }

    return;
}

JiksPgOption::JiksPgOption(JikesPGLexStream* lex,const std::string& file_path)
: home_directory(nullptr), template_directory(nullptr), ast_directory_prefix(nullptr),lex_stream(lex)
{
	for_parser = true;
    for_lsp = true;

	return_code = 0;


	// All of the initializations below are to fields that have cmd-line options
	// >>>
	if (!NEW_OPTIONS_CODE)
	{
		quiet = false;
		automatic_ast = NONE;
		attributes = false;
		backtrack = false;
		legacy = true;
		list = false;
		glr = false;
		slr = false;
		verbose = false;
		first = false;
		follow = false;
		priority = true;
		edit = false;
		states = false;
		xref = false;
		nt_check = false;
		conflicts = true;
		read_reduce = true;
		remap_terminals = true;
		goto_default = false;
		shift_default = false;
		byte = true;
		warnings = true;
		single_productions = false;
		error_maps = false;
		debug = false;
		parent_saved = false;
		precedence = false;
		scopes = false;
		serialize = false;
		soft_keywords = false;
		table = false;
		variables = NONE;
		visitor = NONE;
		lalr_level = 1;
		margin = 0;
		max_cases = 1024;
		names = OPTIMIZED;
		rule_classnames = SEQUENTIAL;
		trace = CONFLICTS;
		programming_language = XML;
		escape = ' ';
		or_marker = '|';
		factory = NULL;
		file_prefix = NULL;
		dat_directory = NULL;
		dat_file = NULL;
		dcl_file = NULL;
		def_file = NULL;
		directory_prefix = NULL;
		imp_file = NULL;
		out_directory = NULL;
		ast_directory = NULL;
		ast_type = NULL;
		visitor_type = NULL;
		include_directory = NULL;
		template_name = NULL;
		extends_parsetable = NULL;
		parsetable_interfaces = NULL;
		package = NULL;
		prefix = NULL;
		suffix = NULL;
	}
	// <<<

	// The following fields have option descriptors, but use a "handler" rather
	// than a direct field member ptr, and so don't get auto initialization.
	filter = NULL;
	import_terminals = NULL;

	// The remaining fields have no associated cmd-line options
	ast_package = NULL;
	grm_file = NULL;
	lis_file = NULL;
	tab_file = NULL;
	prs_file = NULL;
	sym_file = NULL;
	top_level_ast_file = NULL;
	top_level_ast_file_prefix = NULL;
	exp_file = NULL;
	exp_prefix = NULL;
	exp_suffix = NULL;
	exp_type = NULL;
	prs_type = NULL;
	sym_type = NULL;
	dcl_type = NULL;
	imp_type = NULL;
	def_type = NULL;
	action_type = NULL;


    const char* main_input_file = file_path.c_str(),
        * lpg_template = getenv("LPG_TEMPLATE"),
        * lpg_include = getenv("LPG_INCLUDE");

    this->home_directory = GetPrefix(main_input_file);
    char* temp = NewString(strlen(home_directory) +
        (lpg_template == NULL ? 0 : strlen(lpg_template)) +
        4);
    template_directory = temp;
    strcpy(temp, home_directory);
    if (lpg_template != NULL)
    {
        strcat(temp, ";");
        strcat(temp, lpg_template);
    }
    ProcessPath(template_search_directory, template_directory);

    temp = NewString(strlen(home_directory) +
        (lpg_include == NULL ? 0 : strlen(lpg_include)) +
        4);
    include_directory = temp;
    strcpy(temp, home_directory);
    if (lpg_include != NULL)
    {
        strcat(temp, ";");
        strcat(temp, lpg_include);
    }
    ProcessPath(include_search_directory, temp);

    int length = strlen(main_input_file);
    char* temp_file_prefix = NewString(length + 3);
    file_prefix = temp_file_prefix;

    char* temp_lis_file = NewString(length + 3);
    lis_file = temp_lis_file;

    char* temp_tab_file = NewString(length + 3);
    tab_file = temp_tab_file;

    char* grm_file_ptr = NewString(length + 3);
    strcpy(grm_file_ptr, main_input_file);
    NormalizeSlashes(grm_file_ptr); // Turn all (windows) backslashes into forward slashes in filename.
    grm_file = grm_file_ptr;

    int slash_index,
        dot_index = -1;
    for (slash_index = length - 1;
        slash_index >= 0 /* && grm_file[slash_index] != '\\' */ && grm_file[slash_index] != '/';
        slash_index--)
    {
        if (grm_file[slash_index] == '.')
            dot_index = slash_index;
    }

    const char* slash = (slash_index >= 0 ? &grm_file[slash_index] : NULL),
        * dot = (dot_index >= 0 ? &grm_file[dot_index] : NULL),
        * start = (slash ? slash + 1 : grm_file);
    if (dot == NULL) // if filename has no extension, copy it.
    {
        strcpy(temp_file_prefix, start);
        strcpy(temp_lis_file, start);
        strcpy(temp_tab_file, start);

        strcat(((char*)grm_file), ".g"); // add .g extension for input file
    }
    else // if file name contains an extension copy up to the dot
    {
        memcpy(temp_file_prefix, start, dot - start);
        memcpy(temp_lis_file, start, dot - start);
        memcpy(temp_tab_file, start, dot - start);
        temp_lis_file[dot - start] = '\0';
        temp_tab_file[dot - start] = '\0';
        temp_file_prefix[dot - start] = '\0';
    }

    strcat(temp_lis_file, ".l"); // add .l extension for listing file
    strcat(temp_tab_file, ".t"); // add .t extension for table file
}
const char* JiksPgOption::GetFile(const char* directory, const char* file_suffix, const char* file_type)
{
    assert(directory);

    int dir_length = strlen(directory),
        filename_length = dir_length + strlen(file_prefix) + strlen(file_suffix) + strlen(file_type);
    char* temp = NewString(filename_length + 2);
    strcpy(temp, directory);
    if (dir_length > 0 && temp[dir_length - 1] != '/' && temp[dir_length - 1] != '\\')
        strcat(temp, "/");
    strcat(temp, file_prefix);
    strcat(temp, file_suffix);
    strcat(temp, file_type);

    return temp;
}
//
// Strip out the directory prefix if any and return just
// the filename.
//
const char* JiksPgOption::GetFilename(const char* filespec)
{
    const char* forward_slash = strrchr(filespec, '/'),
        * backward_slash = strrchr(filespec, '\\'),
        * slash = (forward_slash > backward_slash ? forward_slash : backward_slash),
        * colon = strrchr(filespec, ':'), // Windows files may use format: d:filename
        * separator = (colon > slash ? colon : slash);
    return (separator ? separator + 1 : filespec);
}

const char* JiksPgOption::GetType(const char* filespec)
{
    const char* start = GetFilename(filespec),
        * dot = strrchr(filespec, '.');
    int length = (dot == NULL ? strlen(start) : dot - start);
    return NewString(start, length);
}

//
//
//

void JiksPgOption::CompleteOptionProcessing()
{
    //
    //
    //
    if (escape == ' ')
    {
        escape = (programming_language == JAVA ||
            programming_language == C ||
            programming_language == CPP2 ||
            programming_language == CPP
            ? '$'
            : '%');
    }

    //
    //
    //
    if (package == NULL)
        package = NewString("");

    //
    //
    //
    if (prefix == NULL)
        prefix = NewString("");

    //
    //
    //
    if (suffix == NULL)
        suffix = NewString("");

    //
    //
    //
    if (template_name == NULL)
        template_name = NewString("");

    assert(file_prefix);

    //
    // The out_directory must be processed prior to all the output files
    // which will use it: prs_file, sym_file, dcl_file, def_file,
    // exp_file, imp_file and the action files.
    //
    if (out_directory == NULL)
        out_directory = NewString(home_directory, strlen(home_directory));
  

    
    //
    //
    //


    //
    //
    //
    if (ast_directory == NULL)
        ast_directory = NewString("");
    else; // The ast directory will be checked if automatic_ast generation is requested. See CheckAutomaticAst.

    //
    //
    //
    if (automatic_ast != NONE)
    {
        if (variables == NONE)
            variables = BOTH;


    }

    //
    //
    //
    if (ast_package == NULL)
        ast_package = NewString("");

    //
    //
    //
    if (ast_type == NULL)
        ast_type = NewString("Ast");

    //
    //
    //
    if (visitor_type == NULL)
        visitor_type = NewString("Visitor");

    //
    //
    //

    if (prs_file == NULL)
    {
        prs_file = GetFile(out_directory,
            "prs.",
            (programming_language == JAVA
                ? "java"
                : (programming_language == ML
                    ? "ml"
                    : (programming_language == PLX || programming_language == PLXASM
                        ? "copy"
                        : (programming_language == C
                            || programming_language == CPP
                            || programming_language == CPP2
                            ? "h"
                            : "xml")))));
    }
    prs_type = GetType(prs_file);

    //
    //
    //
    if (sym_file == NULL)
    {
        sym_file = GetFile(out_directory,
            "sym.",
            (programming_language == JAVA
                ? "java"
                : (programming_language == ML
                    ? "ml"
                    : (programming_language == PLX || programming_language == PLXASM
                        ? "copy"
                        : (programming_language == C
                            || programming_language == CPP
                            || programming_language == CPP2
                            ? "h"
                            : "xml")))));
    }
    sym_type = GetType(sym_file);

    if (NULL == top_level_ast_file)
    {
        top_level_ast_file = GetFile(out_directory,
            "_top_level_ast.",
            (programming_language == JAVA
                ? "java"
                : (programming_language == ML
                    ? "ml"
                    : (programming_language == PLX || programming_language == PLXASM
                        ? "copy"
                        : (programming_language == C
                            || programming_language == CPP
                            || programming_language == CPP2
                            ? "h"
                            : "xml")))));
    }
    top_level_ast_file_prefix = GetType(top_level_ast_file);

    //
    // The dat_directory must be processed prior to the 
    // dat_file which uses it.
    //
    if (dat_directory == NULL)
        dat_directory = NewString(home_directory, strlen(home_directory));


    if (dat_file == NULL)
        dat_file = GetFile(dat_directory, "dcl.", "data");

    //
    //
    //
    if (dcl_file == NULL)
    {
        dcl_file = GetFile(out_directory,
            (programming_language == C || programming_language == CPP || programming_language == CPP2) ? "prs." : "dcl.",
            (programming_language == JAVA
                ? "java"
                : (programming_language == ML
                    ? "ml"
                    : (programming_language == CPP
                        ? "cpp"
                        : (programming_language == PLX
                            ? "copy"
                            : (programming_language == PLXASM
                                ? "assemble"
                                : (programming_language == C
                                    ? "c"
                                    : "xml")))))));
    }
    dcl_type = GetType(dcl_file);

    //
    //
    //
    if (def_file == NULL)
    {
        def_file = GetFile(out_directory,
            "def.",
            (programming_language == JAVA
                ? "java"
                : (programming_language == ML
                    ? "ml"
                    : (programming_language == CPP
                        ? "cpp"
                        : (programming_language == PLX || programming_language == PLXASM
                            ? "copy"
                            : (programming_language == C
                                ? "c"
                                : "xml"))))));
    }
    def_type = GetType(def_file);

    //
    //
    //
    if (directory_prefix == NULL)
    {
        char* p = NewString(1);
        *p = '\0';
        directory_prefix = p;
    }
    else
    {
        NormalizeSlashes((char*)directory_prefix); // turn all backward slashes into forward slashes.
        //
        // Remove all extraneous trailing slashes, if any.
        //
        for (char* tail = (char*)&(directory_prefix[strlen(directory_prefix) - 1]); tail > directory_prefix; tail--)
        {
            if (*tail == '/')
                *tail = '\0';
            else break;
        }
    }

    //
    // Check export_terminals option.
    //
    if (exp_file == NULL)
    {
        exp_file = GetFile(out_directory,
            "exp.",
            (programming_language == JAVA
                ? "java"
                : (programming_language == ML
                    ? "ml"
                    : (programming_language == PLX || programming_language == PLXASM
                        ? "copy"
                        : (programming_language == C
                            || programming_language == CPP
                            || programming_language == CPP2
                            ? "h"
                            : "xml")))));
    }
    else exp_file = ExpandFilename(exp_file);

    exp_type = GetType(exp_file);

    if (exp_prefix == NULL)
        exp_prefix = NewString("");

    if (exp_suffix == NULL)
        exp_suffix = NewString("");

    if (factory == NULL)
        factory = NewString("new ");

    //
    //
    //
    if (imp_file == NULL)
    {
        imp_file = GetFile(out_directory,
            "imp",
            (programming_language == XML
                ? ".xml"
                : (programming_language == C
                    || programming_language == CPP
                    || programming_language == CPP2
                    ? ".h"
                    : (programming_language == PLX || programming_language == PLXASM
                        ? ".copy"
                        : (programming_language == JAVA
                            ? ".java"
                            : ".ml")))));
    }
    imp_type = GetType(imp_file);

    //
    //
    //
    if (soft_keywords)
    {
        lalr_level = 1;
        single_productions = false;
        backtrack = true;
    }

    //
    //
    //
    if (glr)
    {
        lalr_level = 1;
        single_productions = false;
        backtrack = true;
    }

    //
    //
    //
    if (verbose)
    {
        first = true;
        follow = true;
        list = true;
        states = true;
        xref = true;
        warnings = true;
    }

    return;
}

const char* JiksPgOption::ExpandFilename(const char* filename)
{
    return (*filename == '*'
        ? GetFile(out_directory, filename + 1, "")
        : filename);
}

void JiksPgOption::EmitHeader(IToken* startToken, IToken* endToken, const char* header)
{
    startToken = (startToken != NULL ? startToken : lex_stream->GetTokenReference(0));
    endToken = (endToken != NULL ? endToken : lex_stream->GetTokenReference(0));
    
    report.Put(IcuUtil::ws2s( startToken->getIPrsStream()->getFileName()).c_str());
    report.Put(":");
    report.Put(startToken->getLine());
    report.Put(":");
    report.Put(startToken->getColumn());
    report.Put(":");
    report.Put(endToken->getEndLine());
    report.Put(":");
    report.Put(endToken->getEndColumn());
    report.Put(":");
    report.Put(startToken->getStartOffset());
    report.PutChar(':');
    report.Put(endToken->getEndOffset());
    report.Put(": ");

    if (*header != '\0')
        report.Put(header);

    return;
}

void JiksPgOption::EmitHeader(IToken* token, const char* header)
{
    EmitHeader(token, token, header);
}

void JiksPgOption::EmitError(int index, const char* msg)
{
    Emit(lex_stream->GetTokenReference(index), lsDiagnosticSeverity::Error, msg);
}
void JiksPgOption::EmitError(int index, Tuple<const char*>& msg)
{
    Emit(lex_stream->GetTokenReference(index), lsDiagnosticSeverity::Error, msg);
}
void JiksPgOption::EmitWarning(int index, const char* msg)
{
    Emit(lex_stream->GetTokenReference(index), lsDiagnosticSeverity::Warning, msg);
}
void JiksPgOption::EmitWarning(int index, Tuple<const char*>& msg)
{
    Emit(lex_stream->GetTokenReference(index), lsDiagnosticSeverity::Warning, msg);
}
void JiksPgOption::EmitInformative(int index, const char* msg)
{
    Emit(lex_stream->GetTokenReference(index), lsDiagnosticSeverity::Information, msg);
}
void JiksPgOption::EmitInformative(int index, Tuple<const char*>& msg)
{
    Emit(lex_stream->GetTokenReference(index), lsDiagnosticSeverity::Information, msg);
}

void JiksPgOption::Emit(IToken* token, lsDiagnosticSeverity severity, const char* msg)
{
  
    Emit(token, token, severity, msg);

    return;
}

void JiksPgOption::FlushReport()
{
    report.Flush(stdout);
}
void JiksPgOption::Emit(IToken* startToken, IToken* endToken,const  lsDiagnosticSeverity severity, const char* msg)
{
    const char* header;
    if (severity == lsDiagnosticSeverity::Error)
    {
        header = "Error: ";
    }
	else if(severity == lsDiagnosticSeverity::Warning)
	{
        header = "Warning: ";
	}
    else 
    {
        header = "Informative: ";
    }
    EmitHeader(startToken, endToken, header);
    report.Put(msg);
    report.PutChar('\n');

    //FlushReport();

    return;
}


void JiksPgOption::Emit(IToken* token,const lsDiagnosticSeverity severity,  Tuple<const char*>& msg)
{
    Emit(token, token, severity, msg);

    return;
}

void JiksPgOption::Emit(IToken* startToken, IToken* endToken, const lsDiagnosticSeverity severity, Tuple<const char*>& msg)
{
	/*if(message_handler_)
	{
        message_handler_->handleMessage(severity, startToken, endToken, msg);
		return;
	}*/
    const char* header;
    if (severity == lsDiagnosticSeverity::Error)
    {
        header = "Error: ";
    }
    else if (severity == lsDiagnosticSeverity::Warning)
    {
        header = "Warning: ";
    }
    else
    {
        header = "Informative: ";
    }
     EmitHeader(startToken, endToken, header);
     for (int i = 0; i < msg.Length(); i++)
         report.Put(msg[i]);
     report.PutChar('\n');

     FlushReport();

    return;
}

