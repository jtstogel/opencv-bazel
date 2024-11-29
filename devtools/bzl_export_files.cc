#include <algorithm>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/functional/any_invocable.h"
#include "absl/strings/strip.h"

ABSL_FLAG(std::string, directory, "",
          "Directory to traverse for header files.");

ABSL_FLAG(std::string, strip_prefix, "", "Prefix to remove from all paths.");

ABSL_FLAG(std::string, path_regex, "", "Allowed path regular expressions.");

constexpr char kFileComment[] = R"("""
DO NOT EDIT. This file is generated.

To regenerate this file, from the workspace root, run:
 $ bash devtools/generate_opencv_outputs.sh

The above command just lists all files from the CMake output
and writes them into this file.

Bazel needs to know ahead of time what all the outputs of a rule are.
OpenCV's CMake workflow does all sorts of things to make this annoying.
For instance, `opencv_modules.hpp` is actually a text template file
that gets substituded with enabled modules during the CMake process.
Without having a pre-build time understanding of the generated headers,
we instead provide all the expected outputs statically.

TODO(jtstogel): Consider adding a test to ensure this file is always up-to-date.
"""

)";

std::vector<std::string> ListPaths(
    absl::string_view directory, absl::string_view strip_prefix,
    absl::AnyInvocable<bool(absl::string_view path)> predicate) {
  std::vector<std::string> paths;
  for (const auto& entry :
       std::filesystem::recursive_directory_iterator(directory)) {
    if (predicate(entry.path().string())) {
      paths.emplace_back(
          absl::StripPrefix(entry.path().string(), strip_prefix));
    }
  }
  std::sort(paths.begin(), paths.end());
  return paths;
}

std::string GenerateBzlFile(absl::string_view directory,
                            absl::string_view strip_prefix,
                            const std::regex& re) {
  std::vector<std::string> paths =
      ListPaths(directory, strip_prefix, [re](absl::string_view path) {
        return std::regex_search(std::string(path), re);
      });

  std::stringstream output;
  output << kFileComment;
  output << "PATHS = [" << "\n";
  for (const auto& path : paths) {
    output << "    " << std::quoted(path) << "," << "\n";
  }
  output << "]\n";
  return output.str();
}

int main(int argc, char** argv) {
  absl::ParseCommandLine(argc, argv);

  std::regex path_regex(absl::GetFlag(FLAGS_path_regex));
  std::cout << GenerateBzlFile(absl::GetFlag(FLAGS_directory),
                               absl::GetFlag(FLAGS_strip_prefix), path_regex);
}
