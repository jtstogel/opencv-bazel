# opencv-bazel

Use OpenCV with bazel!

### Usage

Depend on `@opencv-bazel//:opencv`, and include the following in your `MODULE.bazel`:

```
bazel_dep(name = "opencv-bazel")
git_override(
    module_name = "opencv-bazel",
    commit = "3b7e0f50a71b8089b9c20c279c5299e9af812973",
    remote = "https://github.com/jtstogel/opencv-bazel.git",
)
```

See the `examples/` directory for usage.

### Developing

Run `bazel run //devtools:refresh_compile_commands` to get intellisense.

If you change any CMake options, run `bash devtools/generate_opencv_outputs.sh`.

OpenCV bazel setup is basically four steps:

- Download OpenCV source code and patch it to expose all files.
- Compile OpenCV with CMake.
- Expose selected headers and shared libraries.
- Wrap those headers and shared libraries in a `cc_library` rule.
