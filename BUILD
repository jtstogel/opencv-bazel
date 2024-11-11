load("@hedron_compile_commands//:refresh_compile_commands.bzl", "refresh_compile_commands")
load("@rules_foreign_cc//foreign_cc:defs.bzl", "cmake")
load("//src:opencv_headers.bzl", "OPENCV_HEADERS")

package(default_visibility = ["//visibility:public"])

licenses(["notice"])  # Apache 2.0

# Expose license for external usage through bazel.
exports_files(["LICENSE"])

refresh_compile_commands(
    name = "refresh_compile_commands",
    targets = {
        "//...": "--process_headers_in_dependencies=false --features=-parse_headers",
    },
)

cc_library(
    name = "opencv",
    srcs = [":opencv_shared_libs"],
    hdrs = [":opencv_hdrs"],
    strip_include_prefix = "include/opencv4/",
)

# Selects the shared library we care about.
genrule(
    name = "opencv_shared_libs",
    srcs = [":opencv_cmake"],
    cmd = "cp -r $(locations :opencv_cmake) $(@D)",
    outs = ["lib/libopencv_world.so"],
)

# Selects the headers we need.
genrule(
    name = "opencv_hdrs",
    srcs = [":opencv_cmake"],
    cmd = "cp -r $(locations :opencv_cmake) $(@D)",
    outs = OPENCV_HEADERS,
)

cmake(
    name = "opencv_cmake",
    cache_entries = {
        "BUILD_opencv_world": "ON",
        "BUILD_SHARED_LIBS": "ON",
        "BUILD_TESTS": "OFF",
        "BUILD_PERF_TESTS": "OFF",
        "WITH_JPEG": "ON",
    },
    env = {
        "CMAKE_BUILD_TYPE": "Release",
        "CMAKE_BUILD_PARALLEL_LEVEL": "24",
    },
    lib_source = "@opencv_4_10_0//:all",
    out_include_dir = "include",
    out_lib_dir = "lib",
    out_shared_libs = ["libopencv_world.so"],
    targets = ["install"],
    visibility = ["//visibility:public"],
)
