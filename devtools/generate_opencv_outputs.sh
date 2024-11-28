if [ ! -f WORKSPACE ]; then
    echo "Must be run from workspace root!"
    exit 1
fi

TMP=$(mktemp)
bazel run //devtools:generate_opencv_headers > $TMP || { echo 'Failed to generate headers!' ; exit 1; }
cp $TMP private/opencv_headers.bzl

TMP=$(mktemp)
bazel run //devtools:generate_opencv_libraries > $TMP || { echo 'Failed to generate libraries!' ; exit 1; }
cp $TMP private/opencv_libraries.bzl
