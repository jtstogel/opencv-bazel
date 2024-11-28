load("@rules_foreign_cc//foreign_cc:defs.bzl", "cmake")

package(default_visibility = ["//:__subpackages__"])

cmake(
    name = "opencv_cmake",
    cache_entries = {
        "BUILD_opencv_world": "ON",
        "BUILD_SHARED_LIBS": "ON",
        "WITH_JPEG": "ON",

        # Disable a bunch of auxiliary binaries.
        "BUILD_DOCS": "OFF",
        "BUILD_EXAMPLES": "OFF",
        "BUILD_PERF_TESTS": "OFF",
        "BUILD_TESTS": "OFF",
        "BUILD_opencv_apps": "OFF",
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
    out_shared_libs = ["libopencv_world.so.410"],
    targets = ["install"],
)
