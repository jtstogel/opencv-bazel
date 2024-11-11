#include <algorithm>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

constexpr char kDataDirectory[] = "opencv_cmake";

constexpr char kGenfilePreScript[] = R"(
"""
DO NOT EDIT. This file is generated.

To regenerate this file, from the workspace root, run:
 $ bazel run //src:list_headers > src/opencv_headers.bzl
"""

OPENCV_HEADERS = [
)";

constexpr char kGenfilePostScript[] = R"(
]
)";

template <typename StringLike>
bool HasExt(StringLike filename, const std::string& ext) {
  return std::string(filename).ends_with(ext);
}

int main(int, char**) {
  std::vector<std::string> paths;

  std::string include_dir = std::string(kDataDirectory) + "/include";
  for (const auto& entry :
       std::filesystem::recursive_directory_iterator(include_dir)) {
    if (HasExt(entry.path(), ".h") || HasExt(entry.path(), ".hpp")) {
      std::string header_file(entry.path());
      header_file.erase(0, sizeof(kDataDirectory));
      paths.push_back(std::move(header_file));
    }
  }
  std::sort(paths.begin(), paths.end());

  std::stringstream output;
  output << kGenfilePreScript;
  for (const auto& path : paths) {
    output << "    " << std::quoted(path) << "," << "\n";
  }
  output << kGenfilePostScript;

  std::cout << output.str() << std::endl;
}
