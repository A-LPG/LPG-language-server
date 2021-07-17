/*
 *  options.cpp
 *  lpg
 *
 *  Created by Robert M. Fuhrer on 3/13/11.
 *  Copyright 2011 IBM. All rights reserved.
 */

#include "JikesPGOptions.h"
#include "JiksPgOption.h"
#include <limits.h>

OptionProcessor::OptionProcessor(JiksPgOption *option)
: options(option)
{ }

std::string
trimQuotes(std::string& s)
{
    std::string result;
    int begin= 0, len = s.length();

    while (s[begin] == ' ') {
        begin++; len--;
    }
    if (s[begin] == '"') {
        begin++; len--;
    }
    if (s[begin+len-1] == '"') {
        len--;
    }
    result += s.substr(begin, len);
    return result;
}

std::list<OptionDescriptor*> OptionDescriptor::allOptionDescriptors;

OptionDescriptor *actionBlock = new OptionDescriptor(STRING_LIST, "action", "block", "???", &OptionProcessor::processActionBlock);
OptionDescriptor* astBlock = new OptionDescriptor(STRING_LIST, "ast", "block", "???", &OptionProcessor::processAstBlock);

void
OptionProcessor::processActionBlock(OptionValue *v)
{
    StringListOptionValue *slv = static_cast<StringListOptionValue*> (v);
    std::list<std::string> values = slv->getValue();
    if (values.size() != 3){
        throw ValueFormatException("action-block value must be a string list of  3 elements", *v->toString(), v->getOptionDescriptor());
    }
    std::list<std::string>::iterator i = values.begin();
    std::string fileName = trimQuotes(*i++);
    std::string blockBegin = trimQuotes(*i++);
    std::string blockEnd = trimQuotes(*i++);

  
}
void
OptionProcessor::processAstBlock(OptionValue* v)
{
    StringListOptionValue* slv = static_cast<StringListOptionValue*> (v);
    std::list<std::string> values = slv->getValue();
    if (values.size() != 2) {
        throw ValueFormatException("ast-block value must be a string list of  3 elements", *v->toString(), v->getOptionDescriptor());
    }
    std::list<std::string>::iterator i = values.begin();
    std::string blockBegin = trimQuotes(*i++);
    std::string blockEnd = trimQuotes(*i++);


}

OptionDescriptor *astDirectory = new PathOptionDescriptor("ast", "directory",
                                                          "the directory in which generated AST classes will be placed, if automatic-ast is 'toplevel'",
                                                          NULL,
                                                          &JiksPgOption::ast_directory, true);

OptionDescriptor *astType = new StringOptionDescriptor("ast", "type", "the name of the AST root class", NULL, &JiksPgOption::ast_type, false);

OptionDescriptor *attributes = new BooleanOptionDescriptor("attributes", "???", false, &JiksPgOption::attributes);

OptionDescriptor *automaticAST = new EnumOptionDescriptor("automatic", "ast", 
                                                          "determines where generated AST classes will be placed",
                                                          &JiksPgOption::automatic_ast, "none", "nested", "none",
                                                          new EnumValue("none", JiksPgOption::NONE),
                                                          new EnumValue("nested", JiksPgOption::NESTED),
                                                          new EnumValue("toplevel", JiksPgOption::TOPLEVEL), NULL);

OptionDescriptor *backtrack = new BooleanOptionDescriptor("backtrack", "???", false,
                                                          &JiksPgOption::backtrack);

OptionDescriptor *byte = new BooleanOptionDescriptor("byte", "???", true,
                                                     &JiksPgOption::byte);

OptionDescriptor *conflicts = new BooleanOptionDescriptor("conflicts", "???", true,
                                                          &JiksPgOption::conflicts);

OptionDescriptor *dataDirectory = new PathOptionDescriptor("dat", "directory", "???", NULL,
                                                       &JiksPgOption::dat_directory);

OptionDescriptor *dataFile = new PathOptionDescriptor("dat", "file", "???", NULL,
                                                      &JiksPgOption::dat_file);

OptionDescriptor *dclFile = new PathOptionDescriptor("dcl", "file", "???", NULL,
                                                     &JiksPgOption::dcl_file);

OptionDescriptor *defFile = new PathOptionDescriptor("def", "file", "???", NULL,
                                                     &JiksPgOption::def_file);

OptionDescriptor *dirPrefix = new PathOptionDescriptor("directory", "prefix", "???", NULL,
                                                       &JiksPgOption::directory_prefix, true);

OptionDescriptor *debug = new BooleanOptionDescriptor("debug", "???", false, &JiksPgOption::debug);

OptionDescriptor *edit = new BooleanOptionDescriptor("edit", "???", false, &JiksPgOption::edit);

OptionDescriptor *errorMaps = new BooleanOptionDescriptor("error", "maps", "???", false, &JiksPgOption::error_maps);

OptionDescriptor *escapeChar = new CharOptionDescriptor("escape", "???", " ",
                                                        &JiksPgOption::escape);

OptionDescriptor *exportsTerminals = new OptionDescriptor(STRING_LIST, "export", "terminals", "???",
                                                          &OptionProcessor::processExportTerminals);

void
OptionProcessor::processExportTerminals(OptionValue *v)
{
    StringListOptionValue *slv = static_cast<StringListOptionValue*> (v);
    const std::list<std::string>& values = slv->getValue();
    if (values.size() < 1 || values.size() > 3) {
        throw ValueFormatException("Export-terminals value must be a string list of 1 to 3 elements", *v->toString(), v->getOptionDescriptor());
    }
    std::list<std::string>::const_iterator iter = values.begin();
    options->exp_file = _strdup((*iter++).c_str());
    if (iter != values.end()) {
        options->exp_prefix = _strdup((*iter++).c_str());
    }
    if (iter != values.end()) {
        options->exp_suffix = _strdup((*iter++).c_str());
    }
}

OptionDescriptor *extendsParseTable = new StringOptionDescriptor("extends", "parsetable", "???", NULL,
                                                                 &JiksPgOption::extends_parsetable, false);

OptionDescriptor *factory = new StringOptionDescriptor("factory", "???", NULL,
                                                       &JiksPgOption::factory, false);

OptionDescriptor *filePrefix = new StringOptionDescriptor("file", "prefix", "???", NULL,
                                                          &JiksPgOption::file_prefix, true);

//
// Can't just do the following b/c the 'filter' option affects two JiksPgOption fields (filter and filter_file)
//OptionDescriptor *filter = new StringOptionDescriptor("filter", NULL, "???",
//                                                      &JiksPgOption::filter, false);
//
OptionDescriptor *filter = new OptionDescriptor(STRING, "filter", "???", &OptionProcessor::processFilter, false);

void
OptionProcessor::processFilter(OptionValue *v)
{
    StringOptionValue *sv = static_cast<StringOptionValue*> (v);
    options->filter_file.reset();
    const char *valStr = _strdup(sv->getValue().c_str());
    options->filter_file.Next() = valStr;
    options->filter = valStr;
}

OptionDescriptor *first = new BooleanOptionDescriptor("first", "???", false, &JiksPgOption::first);

OptionDescriptor *follow = new BooleanOptionDescriptor("follow", "???", false, &JiksPgOption::follow);

OptionDescriptor *glr = new BooleanOptionDescriptor("glr", "???", false, &JiksPgOption::glr);

OptionDescriptor *gotoDefault = new BooleanOptionDescriptor("goto", "default", "???", false,
                                                            &JiksPgOption::goto_default);

OptionDescriptor *ignoreBlock = new OptionDescriptor(STRING, "ignore", "block", "???",
                                                     &OptionProcessor::processIgnoreBlock);
void
OptionProcessor::processIgnoreBlock(OptionValue *v)
{
    StringOptionValue *sv = static_cast<StringOptionValue*> (v);
    if (sv->getValue().length() < 1) {
        throw ValueFormatException("Ignore-block value must be a non-empty string", *v->toString(), v->getOptionDescriptor());
    }
  //  const char *ignore_block = _strdup(sv->getValue().c_str());
   // options->action_blocks.FindOrInsertIgnoredBlock(ignore_block, strlen(ignore_block));
}

OptionDescriptor *impFile = new StringOptionDescriptor("imp", "file", "???",
                                                       &JiksPgOption::imp_file);

// Can't just do the following b/c the 'import-terminals' option affects two JiksPgOption fields (import_file and import_terminals)
//OptionDescriptor *importTerminals = new StringOptionDescriptor("import", "terminals", "???",
//                                                               &JiksPgOption::import_terminals, false);
OptionDescriptor *importTerminals = new OptionDescriptor(STRING, "import", "terminals", "???",
                                                         &OptionProcessor::processImportTerminals);
void
OptionProcessor::processImportTerminals(OptionValue *v)
{
    StringOptionValue *sv = static_cast<StringOptionValue*> (v);
    options->import_file.reset();
    const char *valStr = _strdup(sv->getValue().c_str());
    options->import_file.Next() = valStr;
    options->import_terminals = valStr;
}

OptionDescriptor *includeDirs = new OptionDescriptor(PATH_LIST, "include", "directory",
                                                     "a semi-colon separated list of directories to search when processing include directives",
                                                     &OptionProcessor::processIncludeDir, false);

void
OptionProcessor::processIncludeDir(OptionValue *v)
{
    PathListOptionValue *plv = static_cast<PathListOptionValue*> (v);
    std::list<std::string> values = plv->getValue();
    std::string includeDirOption;

    options->include_search_directory.reset();
    options->include_search_directory.Next() = _strdup(options->home_directory);
    for(std::list<std::string>::iterator i= values.begin(); i != values.end(); i++) {
        std::string path = *i;
//      cerr << "include-dir path: " << path << endl;
        options->include_search_directory.Next() = _strdup(path.c_str());
        if (includeDirOption.length() > 0) {
            includeDirOption += ";";
        }
        includeDirOption += path;
    }
    options->include_directory = _strdup(includeDirOption.c_str());
}

OptionDescriptor *lalr = new IntegerOptionDescriptor("lalr", "", 1, 1, INT_MAX,
                                                     "determines how many tokens of look-ahead can be used to disambiguate",
                                                     &JiksPgOption::lalr_level);

OptionDescriptor *legacy = new BooleanOptionDescriptor("legacy", "???", true, &JiksPgOption::legacy);

OptionDescriptor *list = new BooleanOptionDescriptor("list", "???", false, &JiksPgOption::list);

OptionDescriptor *margin = new IntegerOptionDescriptor("margin", 0, 1, INT_MAX,
                                                       "???",
                                                       &JiksPgOption::margin);

OptionDescriptor *maxCases = new IntegerOptionDescriptor("max", "cases", 1024, 1, INT_MAX,
                                                         "???",
                                                         &JiksPgOption::max_cases);

OptionDescriptor *names = new EnumOptionDescriptor("names", "???", &JiksPgOption::names, "optimized", "", "",
                                                   new EnumValue("optimized", JiksPgOption::OPTIMIZED),
                                                   new EnumValue("minimum", JiksPgOption::MINIMUM),
                                                   new EnumValue("maximum", JiksPgOption::MAXIMUM), NULL);

OptionDescriptor *ntCheck = new BooleanOptionDescriptor("nt", "check", "???", false, &JiksPgOption::nt_check);

OptionDescriptor *orMarker = new CharOptionDescriptor("or", "marker", "???", 
                                                      "|",
                                                      &JiksPgOption::or_marker);

OptionDescriptor *outDirectory = new StringOptionDescriptor("out", "directory", "???", NULL,
                                                            &JiksPgOption::out_directory, true);

OptionDescriptor *package = new StringOptionDescriptor("package", "???", NULL,
                                                       &JiksPgOption::package, false);

OptionDescriptor* parentSaved = new BooleanOptionDescriptor("parent", "saved", "???", false, &JiksPgOption::parent_saved);

OptionDescriptor *parseTableInterfaces = new StringOptionDescriptor("parsetable", "interfaces", "???", NULL,
                                                                    &JiksPgOption::parsetable_interfaces, false);

OptionDescriptor *precedence = new BooleanOptionDescriptor("precedence",
                                                           "if true, allow conflicting actions to be ordered",
                                                           false, &JiksPgOption::precedence, false);

OptionDescriptor *prefix = new StringOptionDescriptor("prefix", "???", NULL,
                                                      &JiksPgOption::prefix, true);

OptionDescriptor *priority = new BooleanOptionDescriptor("priority", "???", true,
                                                         &JiksPgOption::priority);

OptionDescriptor *programmingLang = new EnumOptionDescriptor("programming", "language",
                                                             "identifies the desired parser implementation language",
                                                             &JiksPgOption::programming_language, "xml", "", "",
                                                             new EnumValue("c", JiksPgOption::C),
															 new EnumValue("rt_cpp", JiksPgOption::CPP2),
                                                             new EnumValue("cpp", JiksPgOption::CPP),
                                                             new EnumValue("c++", JiksPgOption::CPP),
															    new EnumValue("csharp", JiksPgOption::CSHARP),
															    new EnumValue("c#", JiksPgOption::CSHARP),
                                                             new EnumValue("java", JiksPgOption::JAVA),
                                                             new EnumValue("ml", JiksPgOption::ML),
                                                             new EnumValue("plx", JiksPgOption::PLX),
                                                             new EnumValue("plxasm", JiksPgOption::PLXASM),
                                                             new EnumValue("xml", JiksPgOption::XML), NULL);

OptionDescriptor *prsFile = new StringOptionDescriptor("prs", "file", "???", NULL,
                                                       &JiksPgOption::prs_file, false);

OptionDescriptor *quiet = new BooleanOptionDescriptor("quiet",
                                                      "???", false,
                                                      &JiksPgOption::quiet);

OptionDescriptor *readReduce = new BooleanOptionDescriptor("read", "reduce",
                                                           "???", true,
                                                           &JiksPgOption::read_reduce);

OptionDescriptor *remapTerminals = new BooleanOptionDescriptor("remap", "terminals",
                                                               "???", true,
                                                               &JiksPgOption::remap_terminals);

OptionDescriptor *ruleClassNames = new EnumOptionDescriptor("rule", "classnames", "???",
                                                            &JiksPgOption::rule_classnames,
                                                            "sequential", "", "",
                                                            new EnumValue("sequential", JiksPgOption::SEQUENTIAL),
                                                            new EnumValue("stable", JiksPgOption::STABLE), NULL);

OptionDescriptor *scopes = new BooleanOptionDescriptor("scopes",
                                                       "???", false,
                                                       &JiksPgOption::scopes);

OptionDescriptor *serialize = new BooleanOptionDescriptor("serialize",
                                                          "???", false,
                                                          &JiksPgOption::serialize);

OptionDescriptor *shiftDefault = new BooleanOptionDescriptor("shift", "default",
                                                             "???", false,
                                                             &JiksPgOption::shift_default);

OptionDescriptor *singleProductions = new BooleanOptionDescriptor("single", "productions",
                                                           "???", false,
                                                           &JiksPgOption::single_productions);

OptionDescriptor *slr = new BooleanOptionDescriptor("slr",
                                                    "???", false,
                                                    &JiksPgOption::slr);

OptionDescriptor *softKeywords = new BooleanOptionDescriptor("soft", "keywords",
                                                             "if true, try treating keywords as identifiers if parsing fails otherwise",
                                                             false,
                                                             &JiksPgOption::soft_keywords);

OptionDescriptor *states = new BooleanOptionDescriptor("states",
                                                       "???", false,
                                                       &JiksPgOption::states);

OptionDescriptor *suffix = new StringOptionDescriptor("suffix", "???", NULL,
                                                      &JiksPgOption::suffix, true);

OptionDescriptor *symFile = new StringOptionDescriptor("sym", "file", "???", NULL,
                                                       &JiksPgOption::sym_file, false);

OptionDescriptor *tabFile = new StringOptionDescriptor("tab", "file", "???", NULL,
                                                       &JiksPgOption::tab_file, false);

OptionDescriptor *table = new EnumOptionDescriptor("table", "???",
                                                   &OptionProcessor::processTable,
                                                   "",
                                                   new EnumValue("c", JiksPgOption::C),
												   new EnumValue("rt_cpp", JiksPgOption::CPP2),
                                                   new EnumValue("cpp", JiksPgOption::CPP),
                                                   new EnumValue("c++", JiksPgOption::CPP),
												   new EnumValue("csharp", JiksPgOption::CSHARP),
											       new EnumValue("c#", JiksPgOption::CSHARP),
                                                   new EnumValue("java", JiksPgOption::JAVA),
                                                   new EnumValue("ml", JiksPgOption::ML),
                                                   new EnumValue("none", JiksPgOption::XML),
                                                   new EnumValue("plx", JiksPgOption::PLX),
                                                   new EnumValue("plxasm", JiksPgOption::PLXASM),
                                                   new EnumValue("xml", JiksPgOption::XML), NULL);
void
OptionProcessor::processTable(OptionValue *v)
{
    EnumOptionValue *ev = static_cast<EnumOptionValue*> (v);
    std::string value = ev->getValue();

    if (!value.compare("none")) {
        options->table = false;
        options->programming_language = JiksPgOption::XML;
    } else {
        if (!value.compare("c")) {
            options->programming_language = JiksPgOption::C;
        } else if (!value.compare("cpp") || !value.compare("c++")) {
            options->programming_language = JiksPgOption::CPP;
        }
        else if (!value.compare("rt_cpp")) {
            options->programming_language = JiksPgOption::CPP2;
        }
        else if (!value.compare("c#") || !value.compare("csharp")) {
            options->programming_language = JiksPgOption::CSHARP;
        }
    	else if (!value.compare("java")) {
            options->programming_language = JiksPgOption::JAVA;
        } else if (!value.compare("ml")) {
            options->programming_language = JiksPgOption::ML;
        } else if (!value.compare("plx")) {
            options->programming_language = JiksPgOption::PLX;
        } else if (!value.compare("plxasm")) {
            options->programming_language = JiksPgOption::PLXASM;
        } else if (!value.compare("xml")) {
            options->programming_language = JiksPgOption::XML;
        }
        options->table = true;
    }
}

OptionDescriptor *template_ = new StringOptionDescriptor("template", "???", NULL,
                                                         &JiksPgOption::template_name, false);

OptionDescriptor *trace = new EnumOptionDescriptor("trace", "???",
                                                   &JiksPgOption::trace,
                                                   "conflicts", "conflicts", "none",
                                                   new EnumValue("none", JiksPgOption::NONE),
                                                   new EnumValue("conflicts", JiksPgOption::CONFLICTS),
                                                   new EnumValue("full", JiksPgOption::FULL), NULL);

OptionDescriptor *trailers = new OptionDescriptor(STRING_LIST, "trailers", "???",
                                                  &OptionProcessor::processTrailers);
void
OptionProcessor::processTrailers(OptionValue *v)
{
    StringListOptionValue *slv = static_cast<StringListOptionValue*> (v);
    const std::list<std::string>& values = slv->getValue();
    if (values.size() != 3) {
        throw ValueFormatException("Trailers value must be a string list of 3 elements", *v->toString(), v->getOptionDescriptor());
    }
    std::list<std::string>::const_iterator iter = values.begin();
    const char *filename = _strdup((*iter++).c_str());
    const char *block_begin = _strdup((*iter++).c_str());
    const char *block_end = _strdup((*iter++).c_str());
  //  options->trailer_options.Next().Set(NULL, filename, block_begin, block_end);
}

OptionDescriptor *variables = new EnumOptionDescriptor("variables",
                                                       "determines the set of right-hand side symbols for which local variables will be defined within action blocks",
                                                       &JiksPgOption::variables,
                                                       "none", "both", "none",
                                                       new EnumValue("none", JiksPgOption::NONE),
                                                       new EnumValue("both", JiksPgOption::BOTH),
                                                       new EnumValue("terminals", JiksPgOption::TERMINALS),
                                                       new EnumValue("nt", JiksPgOption::NON_TERMINALS),
                                                       new EnumValue("nonterminals", JiksPgOption::NON_TERMINALS),
                                                       new EnumValue("non-terminals", JiksPgOption::NON_TERMINALS), NULL);

OptionDescriptor *verbose = new BooleanOptionDescriptor("verbose",
                                                        "???", false,
                                                        &JiksPgOption::verbose);

OptionDescriptor *visitor = new EnumOptionDescriptor("visitor", "???",
                                                     &JiksPgOption::visitor,
                                                     "none", "default", "none",
                                                     new EnumValue("none", JiksPgOption::NONE),
                                                     new EnumValue("default", JiksPgOption::DEFAULT),
                                                     new EnumValue("preorder", JiksPgOption::PREORDER), NULL);

OptionDescriptor *visitorType = new StringOptionDescriptor("visitor", "type", "???", NULL,
                                                           &JiksPgOption::visitor_type, false);

OptionDescriptor *warnings = new BooleanOptionDescriptor("warnings",
                                                         "???", true,
                                                         &JiksPgOption::warnings);

OptionDescriptor *xref = new BooleanOptionDescriptor("xref",
                                                     "???", false,
                                                     &JiksPgOption::xref);
