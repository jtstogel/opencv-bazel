# opencv-bazel

Use OpenCV with bazel!

### Usage

Depend on `@opencv-bazel//:opencv`. See the `examples/` directory for usage.

### Developing

Run `bazel run //devtools:refresh_compile_commands` to get intellisense.

If you change any CMake options, run `bash devtools/generate_opencv_headers.sh`.

OpenCV bazel setup is basically four steps:

- Download OpenCV source code and patch it to expose all files.
- Compile OpenCV with CMake.
- Expose selected headers and shared libraries.
- Wrap those headers and shared libraries in a `cc_library` rule.
