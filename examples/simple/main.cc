#include <iostream>

#include "opencv2/core/mat.hpp"

using namespace cv;

int main(int /* argc */, char** argv) {
  Mat image = Mat::zeros(1000, 700, CV_8UC3);

  std::cout << "Image width: " << image.elemSize() << std::endl;

  return 0;
}
