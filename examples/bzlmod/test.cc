#include "gtest/gtest.h"
#include "opencv2/core/mat.hpp"
#include "opencv2/imgcodecs.hpp"

TEST(OpenCV, ImageRead) {
  cv::Mat img = cv::imread("test_image.jpeg", cv::IMREAD_COLOR);
  cv::Size size = img.size();

  EXPECT_EQ(size.width, 600);
  EXPECT_EQ(size.height, 600);
}
