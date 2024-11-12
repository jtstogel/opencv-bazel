#include <iostream>

#include "opencv2/core/mat.hpp"
#include "opencv2/imgcodecs.hpp"

int main(int, char**) {
  cv::Mat img =
      cv::imread("src/examples/local/test_image.jpeg", cv::IMREAD_COLOR);
  cv::Size size = img.size();

  std::cout << size.width << "x" << size.height << std::endl;
}
