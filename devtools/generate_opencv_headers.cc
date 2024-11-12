#include <algorithm>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/strings/strip.h"

ABSL_FLAG(std::string, include_dir, "",
          "Directory to traverse for header files.");

ABSL_FLAG(std::string, strip_prefix, "", "Prefix to remove from all paths.");

constexpr char kFileComment[] = R"("""
DO NOT EDIT. This file is generated.

To regenerate this file, from the workspace root, run:
 $ bash devtools/generate_opencv_headers.sh

The above command just lists all header files from the CMake output
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

template <typename StringLike>
bool HasExt(StringLike filename, const std::string& ext) {
  return std::string(filename).ends_with(ext);
}

std::string GenerateBzlFile(absl::string_view include_dir,
                            absl::string_view strip_prefix) {
  std::vector<std::string> paths;

  for (const auto& entry :
       std::filesystem::recursive_directory_iterator(include_dir)) {
    if (HasExt(entry.path(), ".h") || HasExt(entry.path(), ".hpp")) {
      std::string path(entry.path());
      paths.emplace_back(absl::StripPrefix(path, strip_prefix));
    }
  }
  std::sort(paths.begin(), paths.end());

  std::stringstream output;
  output << kFileComment;
  output << "OPENCV_HEADERS = [" << "\n";
  for (const auto& path : paths) {
    output << "    " << std::quoted(path) << "," << "\n";
  }
  output << "]\n";
  return output.str();
}

int main(int argc, char** argv) {
  absl::ParseCommandLine(argc, argv);

  std::cout << GenerateBzlFile(absl::GetFlag(FLAGS_include_dir),
                               absl::GetFlag(FLAGS_strip_prefix));
}
