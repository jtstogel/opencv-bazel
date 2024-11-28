"""
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

PATHS = [
    "lib/libopencv_world.so.410",
]
