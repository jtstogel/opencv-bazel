load("@rules_foreign_cc//foreign_cc:defs.bzl", "cmake")
load("//:opencv_headers.bzl", "OPENCV_HEADERS")

package(default_visibility = ["//visibility:public"])

licenses(["notice"])  # Apache 2.0

# Expose license for external usage through bazel.
exports_files(["LICENSE"])

cc_library(
    name = "opencv",
    srcs = [":opencv_shared_libs"],
    hdrs = [":opencv_hdrs"],
    strip_include_prefix = "include/opencv4/",
    copts = [
        "-fexceptions",
        "-Wno-deprecated-declarations",
    ],
)

# Selects the shared library we need.
genrule(
    name = "opencv_shared_libs",
    srcs = [":opencv_cmake"],
    outs = ["lib/libopencv_world.so"],
    cmd = "cp -r $(locations :opencv_cmake) $(@D)",
)

# Selects the headers we want to expose.
genrule(
    name = "opencv_hdrs",
    srcs = [":opencv_cmake"],
    outs = OPENCV_HEADERS,
    cmd = "cp -r $(locations :opencv_cmake) $(@D)",
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
    copts = [
        "-fexceptions",
        "-Wno-deprecated-declarations",
    ],
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
