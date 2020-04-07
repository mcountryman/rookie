//
// Created by mcountryman on 4/7/2020.
//

#include <opencv2/imgproc.hpp>
#include "frame/frame_resolver.hpp"
#include "board.hpp"

namespace rookie::board {
  void Board::ProcessFrame(cv::Mat &in) {
    auto frame = _frameResolver.Resolve(in);

    for (auto &line : frame.lines()) {
      cv::line(
        in,
        static_cast<cv::Point>(line.begin()),
        static_cast<cv::Point>(line.end()),
        cv::Scalar(0, 255, 0, 255)
      );
    }
  }
}
