#include "utils.h"


#include <loguru.hpp>

#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstring>
#include <fstream>
#include <functional>
#include <loguru.hpp>
#include <queue>
#include <sstream>
#include <string>
#include <stringex.h>
#include <unordered_map>
#include <sys/stat.h>

// DEFAULT_RESOURCE_DIRECTORY is passed with quotes for non-MSVC compilers, ie,
// foo vs "foo".
#if defined(_MSC_VER)
#define _STRINGIFY(x) #x
#define ENSURE_STRING_MACRO_ARGUMENT(x) _STRINGIFY(x)
#else
#define ENSURE_STRING_MACRO_ARGUMENT(x) x
#endif


// See http://stackoverflow.com/a/2072890
bool EndsWith(std::string_view value, std::string_view ending) {
  if (ending.size() > value.size())
    return false;
  return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

bool StartsWith(std::string_view value, std::string_view start) {
  if (start.size() > value.size())
    return false;
  return std::equal(start.begin(), start.end(), value.begin());
}

bool AnyStartsWith(const std::vector<std::string>& values,
                   const std::string& start) {
  return std::any_of(
      std::begin(values), std::end(values),
      [&start](const std::string& value) { return StartsWith(value, start); });
}

bool StartsWithAny(const std::string& value,
                   const std::vector<std::string>& startings) {
  return std::any_of(std::begin(startings), std::end(startings),
                     [&value](const std::string& starting) {
                       return StartsWith(value, starting);
                     });
}

bool EndsWithAny(const std::string& value,
                 const std::vector<std::string>& endings) {
  return std::any_of(
      std::begin(endings), std::end(endings),
      [&value](const std::string& ending) { return EndsWith(value, ending); });
}

bool FindAnyPartial(const std::string& value,
                    const std::vector<std::string>& values) {
  return std::any_of(std::begin(values), std::end(values),
                     [&value](const std::string& v) {
                       return value.find(v) != std::string::npos;
                     });
}

std::string GetDirName(std::string temp_path) {
    std::stringex path;
    path.swap(temp_path);
    path.replace('\\', '/');
  if (path.size() && path.back() == '/')
    path.pop_back();
  size_t last_slash = path.find_last_of('/');
  if (last_slash == std::string::npos)
    return "./";
  return path.substr(0, last_slash + 1);
}

std::string GetBaseName(const std::string& path) {
  size_t last_slash = path.find_last_of('/');
  if (last_slash != std::string::npos && (last_slash + 1) < path.size())
    return path.substr(last_slash + 1);
  return path;
}

std::string StripFileType(const std::string& path) {
  size_t last_period = path.find_last_of('.');
  if (last_period != std::string::npos)
    return path.substr(0, last_period);
  return path;
}

// See http://stackoverflow.com/a/29752943
std::string ReplaceAll(const std::string& source,
                       const std::string& from,
                       const std::string& to) {
  std::string result;
  result.reserve(source.length());  // avoids a few memory allocations

  std::string::size_type last_pos = 0;
  std::string::size_type find_pos;

  while (std::string::npos != (find_pos = source.find(from, last_pos))) {
    result.append(source, last_pos, find_pos - last_pos);
    result += to;
    last_pos = find_pos + from.length();
  }

  // Care for the rest after last occurrence
  result += source.substr(last_pos);

  return result;
}

std::vector<std::string> SplitString(const std::string& str,
                                     const std::string& delimiter) {
  // http://stackoverflow.com/a/13172514
  std::vector<std::string> strings;

  std::string::size_type pos = 0;
  std::string::size_type prev = 0;
  while ((pos = str.find(delimiter, prev)) != std::string::npos) {
    strings.emplace_back(str.substr(prev, pos - prev));
    prev = pos + 1;
  }

  // To get the last substring (or only, if delimiter is not found)
  strings.emplace_back(str.substr(prev));

  return strings;
}

void EnsureEndsInSlash(std::string& path) {
  if (path.empty() || path[path.size() - 1] != '/')
    path += '/';
}

std::string EscapeFileName(std::string path) {
  if (path.size() && path.back() == '/')
    path.pop_back();
  std::replace(path.begin(), path.end(), '\\', '@');
  std::replace(path.begin(), path.end(), '/', '@');
  std::replace(path.begin(), path.end(), ':', '@');
  return path;
}

// http://stackoverflow.com/a/6089413
std::istream& SafeGetline(std::istream& is, std::string& t) {
  t.clear();

  // The characters in the stream are read one-by-one using a std::streambuf.
  // That is faster than reading them one-by-one using the std::istream. Code
  // that uses streambuf this way must be guarded by a sentry object. The sentry
  // object performs various tasks, such as thread synchronization and updating
  // the stream state.

  std::istream::sentry se(is, true);
  std::streambuf* sb = is.rdbuf();

  for (;;) {
    int c = sb->sbumpc();
    if (c == EOF) {
      // Also handle the case when the last line has no line ending
      if (t.empty())
        is.setstate(std::ios::eofbit);
      return is;
    }

    t += (char)c;

    if (c == '\n')
      return is;
  }
}

bool FileExists(const std::string& filename) {
  std::ifstream cache(filename);
  return cache.is_open();
}

boost::optional<std::string> ReadContent(const AbsolutePath& filename) {
  LOG_S(INFO) << "Reading " << filename;
  std::ifstream cache;
  cache.open(filename.path);

  try {
    return std::string(std::istreambuf_iterator<char>(cache),
                       std::istreambuf_iterator<char>());
  } catch (std::ios_base::failure&) {
    return {};
  }
}

std::vector<std::string> ReadLinesWithEnding(const AbsolutePath& filename) {
  std::vector<std::string> result;

  std::ifstream input(filename.path);
  for (std::string line; SafeGetline(input, line);)
    result.emplace_back(line);

  return result;
}

void WriteToFile(const std::string& filename, const std::string& content) {
  std::ofstream file(filename,
                     std::ios::out | std::ios::trunc | std::ios::binary);
  if (!file.good()) {
    LOG_S(ERROR) << "Cannot write to " << filename;
    return;
  }

  file << content;
}


std::string FormatMicroseconds(long long microseconds) {
  long long milliseconds = microseconds / 1000;
  long long remaining = microseconds - milliseconds;

  // Only show two digits after the dot.
  while (remaining >= 100)
    remaining /= 10;

  return std::to_string(milliseconds) + "." + std::to_string(remaining) + "ms";
}



std::string UpdateToRnNewlines(std::string output) {
  size_t idx = 0;
  while (true) {
    idx = output.find('\n', idx);

    // No more matches.
    if (idx == std::string::npos)
      break;

    // Skip an existing "\r\n" match.
    if (idx > 0 && output[idx - 1] == '\r') {
      ++idx;
      continue;
    }

    // Replace "\n" with "\r|n".
    output.replace(output.begin() + idx, output.begin() + idx + 1, "\r\n");
  }

  return output;
}



bool IsAbsolutePath(const std::string& path) {
  return IsUnixAbsolutePath(path) || IsWindowsAbsolutePath(path);
}

bool IsUnixAbsolutePath(const std::string& path) {
  return !path.empty() && path[0] == '/';
}

bool IsWindowsAbsolutePath(const std::string& path) {
  auto is_drive_letter = [](char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
  };

  return path.size() > 3 && path[1] == ':' &&
         (path[2] == '/' || path[2] == '\\') && is_drive_letter(path[0]);
}

bool IsDirectory(const std::string& path) {
  struct stat path_stat;

  if (stat(path.c_str(), &path_stat) != 0) {
    perror("cannot access path");
    return false;
  }

  return path_stat.st_mode & S_IFDIR;
}

