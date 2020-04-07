#include <iostream>
#include <opencv2/opencv.hpp>
#include "board/board.hpp"

int main() {
  auto board = rookie::board::Board();
  auto camera = cv::VideoCapture(0);

  if (!camera.isOpened()) {
    std::cout << "Failed to open camera" << std::endl;
    return -1;
  }

  cv::namedWindow("rookie", 1);

  for (;;) {
    auto frame = cv::Mat();
    camera >> frame;

    board.ProcessFrame(frame);
    cv::imshow("rookie", frame);

    if (cv::waitKey(30) >= 0) {
      break;
    }
  }

  return 0;
}
