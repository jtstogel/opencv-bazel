load("@hedron_compile_commands//:refresh_compile_commands.bzl", "refresh_compile_commands")

refresh_compile_commands(
    name = "refresh_compile_commands",
    targets = {
        "//...": "--process_headers_in_dependencies=false --features=-parse_headers",
    },
)

cc_binary(
    name = "generate_opencv_headers",
    srcs = ["generate_opencv_headers.cc"],
    args = [
        "--include_dir=opencv_cmake/include",
        "--strip_prefix=opencv_cmake/",
    ],
    data = ["//:opencv_cmake"],
    deps = [
        "@abseil-cpp//absl/flags:flag",
        "@abseil-cpp//absl/flags:parse",
        "@abseil-cpp//absl/strings",
    ],
)
