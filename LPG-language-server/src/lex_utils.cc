#include "lex_utils.h"



#include <algorithm>
#include <iostream>

#include "utils.h"

// VSCode (UTF-16) disagrees with Emacs lsp-mode (UTF-8) on how to represent
// text documents.
// We use a UTF-8 iterator to approximate UTF-16 in the specification (weird).
// This is good enough and fails only for UTF-16 surrogate pairs.
int GetOffsetForPosition(lsPosition position, std::string_view content) {
  size_t i = 0;
  // Iterate lines until we have found the correct line.
  while (position.line > 0 && i < content.size()) {
    if (content[i] == '\n')
      position.line--;
    i++;
  }
  // Iterate characters on the target line.
  while (position.character > 0 && i < content.size()) {
    if (uint8_t(content[i++]) >= 128) {
      // Skip 0b10xxxxxx
      while (i < content.size() && uint8_t(content[i]) >= 128 &&
             uint8_t(content[i]) < 192)
        i++;
    }
    position.character--;
  }
  return int(i);
}

lsPosition GetPositionForOffset(int offset, std::string_view content) {
  lsPosition result;
  for (int i = 0; i < offset && i < content.length(); ++i) {
    if (content[i] == '\n') {
      result.line++;
      result.character = 0;
    } else {
      result.character++;
    }
  }
  return result;
}

lsPosition CharPos(std::string_view search,
                   char character,
                   int character_offset) {
  lsPosition result;
  size_t index = 0;
  while (index < search.size()) {
    char c = search[index];
    if (c == character)
      break;
    if (c == '\n') {
      result.line += 1;
      result.character = 0;
    } else {
      result.character += 1;
    }
    ++index;
  }
  assert(index < search.size());
  result.character += character_offset;
  return result;
}

// TODO: eliminate |line_number| param.
boost::optional<lsRange> ExtractQuotedRange(int line_number, const std::string& line) {
  // Find starting and ending quote.
  int start = 0;
  while (start < (int)line.size()) {
    char c = line[start];
    ++start;
    if (c == '"' || c == '<')
      break;
  }
  if (start == (int)line.size())
    return {};

  int end = (int)line.size();
  while (end > 0) {
    char c = line[end];
    if (c == '"' || c == '>')
      break;
    --end;
  }

  if (start >= end)
    return {};

  return lsRange(lsPosition(line_number, start), lsPosition(line_number, end));
}

void LexFunctionDeclaration(const std::string& buffer_content,
                            lsPosition declaration_spelling,
                            boost::optional<std::string> type_name,
                            std::string* insert_text,
                            int* newlines_after_name) {
  int name_start = GetOffsetForPosition(declaration_spelling, buffer_content);

  bool parse_return_type = true;
  // We need to check if we have a return type (ctors and dtors do not).
  if (type_name) {
    int name_end = name_start;
    while (name_end < buffer_content.size()) {
      char c = buffer_content[name_end];
      if (isspace(c) || c == '(')
        break;
      ++name_end;
    }

    std::string func_name =
        buffer_content.substr(name_start, name_end - name_start);
    if (func_name == *type_name || func_name == ("~" + *type_name))
      parse_return_type = false;
  }

  // We need to fetch the return type. This can get complex, ie,
  //
  //  std::vector <int> foo();
  //
  int return_start = name_start;
  if (parse_return_type) {
    int paren_balance = 0;
    int angle_balance = 0;
    bool expect_token = true;
    while (return_start > 0) {
      char c = buffer_content[return_start - 1];
      if (paren_balance == 0 && angle_balance == 0) {
        if (isspace(c) && !expect_token) {
          break;
        }
        if (!isspace(c))
          expect_token = false;
      }

      if (c == ')')
        ++paren_balance;
      if (c == '(') {
        --paren_balance;
        expect_token = true;
      }

      if (c == '>')
        ++angle_balance;
      if (c == '<') {
        --angle_balance;
        expect_token = true;
      }

      return_start -= 1;
    }
  }

  // We need to fetch the arguments. Just scan for the next ';'.
  *newlines_after_name = 0;
  int end = name_start;
  while (end < buffer_content.size()) {
    char c = buffer_content[end];
    if (c == ';')
      break;
    if (c == '\n')
      *newlines_after_name += 1;
    ++end;
  }

  std::string result;
  result += buffer_content.substr(return_start, name_start - return_start);
  if (type_name && !type_name->empty())
    result += *type_name + "::";
  result += buffer_content.substr(name_start, end - name_start);
  TrimEndInPlace(result);
  result += " {\n}";
  *insert_text = result;
}

std::string_view LexIdentifierAroundPos(lsPosition position,
                                        std::string_view content) {
  int start = GetOffsetForPosition(position, content);
  int end = start + 1;
  char c;

  // We search for :: before the cursor but not after to get the qualifier.
  for (; start > 0; start--) {
    c = content[start - 1];
    if (isalnum(c) || c == '_')
      ;
    else if (c == ':' && start > 1 && content[start - 2] == ':')
      start--;
    else
      break;
  }

  for (; end < (int)content.size(); end++)
    if (c = content[end], !(isalnum(c) || c == '_'))
      break;

  return content.substr(start, end - start);
}

// Find discontinous |search| in |content|.
// Return |found| and the count of skipped chars before found.
std::pair<bool, int> CaseFoldingSubsequenceMatch(std::string_view search,
                                                 std::string_view content) {
  bool hasUppercaseLetter = std::any_of(search.begin(), search.end(), isupper);
  int skip = 0;
  size_t j = 0;
  for (char c : search) {
    while (j < content.size() &&
           (hasUppercaseLetter ? content[j] != c
                               : tolower(content[j]) != tolower(c)))
      ++j, ++skip;
    if (j == content.size())
      return {false, skip};
    ++j;
  }
  return {true, skip};
}
