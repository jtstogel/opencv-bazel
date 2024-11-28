load("@hedron_compile_commands//:refresh_compile_commands.bzl", "refresh_compile_commands")

refresh_compile_commands(
    name = "refresh_compile_commands",
    targets = {
        "//...": "--process_headers_in_dependencies=false --features=-parse_headers",
    },
)

cc_library(
    name = "bzl_export_files",
    srcs = ["bzl_export_files.cc"],
    deps = [
        "@abseil-cpp//absl/flags:flag",
        "@abseil-cpp//absl/flags:parse",
        "@abseil-cpp//absl/functional:any_invocable",
        "@abseil-cpp//absl/strings",
    ],
)

cc_binary(
    name = "generate_opencv_headers",
    args = [
        "--directory=private/opencv_cmake/opencv_cmake/include",
        "--strip_prefix=private/opencv_cmake/opencv_cmake/",
        "--path_regex=\"[.](h|hpp)$$\"",
    ],
    data = ["//private/opencv_cmake"],
    deps = [":bzl_export_files"],
)

cc_binary(
    name = "generate_opencv_libraries",
    args = [
        "--directory=private/opencv_cmake/opencv_cmake/lib",
        "--strip_prefix=private/opencv_cmake/opencv_cmake/",
        "--path_regex=\"[.]so([.]\\d+)?$$\"",
    ],
    data = ["//private/opencv_cmake"],
    deps = [":bzl_export_files"],
)
