//
// Created by mcountryman on 4/7/2020.
//

#ifndef ROOKIE_BOARD_HPP
#define ROOKIE_BOARD_HPP

#include "frame/frame.hpp"
#include "frame/frame_resolver.hpp"

#include <opencv2/core/mat.hpp>

namespace rookie::board {
  class Board {
  public:
    void ProcessFrame(cv::Mat &frame);
  private:
    frame::FrameResolver _frameResolver;
  };
}


#endif //ROOKIE_BOARD_HPP
