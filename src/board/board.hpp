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
    bool ProcessFrame(cv::Mat &frame);
  private:
    bool _drawDebugInfo = true;
    bool _drawDebugCells = false;
    bool _drawDebugLines = false;
    bool _drawDebugQuads = false;
    bool _drawDebugPoints = true;
    bool _drawDebugTriangles = false;
    frame::FrameResolver _frameResolver;
  };
}


#endif //ROOKIE_BOARD_HPP
