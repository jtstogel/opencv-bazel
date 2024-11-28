load("@rules_foreign_cc//foreign_cc:defs.bzl", "cmake")
load(":opencv_headers.bzl", OPENCV_HEADERS = "PATHS")
load(":opencv_libraries.bzl", OPENCV_LIBRARIES = "PATHS")

package(default_visibility = ["//:__subpackages__"])

cc_library(
    name = "opencv",
    srcs = OPENCV_LIBRARIES,
    hdrs = OPENCV_HEADERS,
    copts = [
        "-fexceptions",
        "-Wno-deprecated-declarations",
    ],
    strip_include_prefix = "include/opencv4/",
    deps = [":opencv_outputs"],
)

# Selects the outputs we want to expose.
genrule(
    name = "opencv_outputs",
    srcs = ["//private/opencv_cmake"],
    outs = OPENCV_HEADERS + OPENCV_LIBRARIES,
    cmd = "cp -fRL \"$(RULEDIR)/opencv_cmake/opencv_cmake/\"* \"$(RULEDIR)\"",
)
