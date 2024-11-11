if [ ! -f WORKSPACE ]; then
    echo "Must be run from workspace root!"
    exit 1
fi

TMP=$(mktemp)
bazel run //devtools:generate_opencv_headers > $TMP || { echo 'Failed to generate headers!' ; exit 1; }
cp $TMP opencv_headers.bzl
