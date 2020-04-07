//
// Created by mcountryman on 4/7/2020.
//

#ifndef ROOKIE_FRAME_HPP
#define ROOKIE_FRAME_HPP

#include <vector>

#include "../../math/segment.hpp"

namespace rookie::board::frame {
  class Frame {
  public:
    Frame(std::vector<rookie::math::Segmenti> lines) : _lines(lines) {}
  public:
    std::vector<rookie::math::Segmenti> lines() { return _lines; }
  private:
    std::vector<rookie::math::Segmenti> _lines;
  };
}

#endif //ROOKIE_FRAME_HPP
