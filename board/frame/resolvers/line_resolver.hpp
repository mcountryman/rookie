//
// Created by mcountryman on 4/7/2020.
//

#ifndef ROOKIE_LINE_RESOLVER_HPP
#define ROOKIE_LINE_RESOLVER_HPP

#include <vector>
#include <opencv2/core/mat.hpp>
#include "line_segment.hpp"

namespace rookie::board::frame::resolvers {
  using rookie::math::LineSegment;

  class LineResolver {
  public:
    LineResolver() :
      _maxLines(150),
      _rho(1),
      _theta(M_PI / 180),
      _blurWidth(3),
      _blurHeight(3),
      _apertureSize(3),
      _maxLineGap(350),
      _minLineLength(250),
      _houghThreshold(70),
      _cannyThreshold1(75),
      _cannyThreshold2(150) {}
  public:
    std::vector<LineSegment<float>> Resolve(cv::Mat &frame) const;
  private:
    std::size_t _maxLines;
    double _rho;
    double _theta;
    int _blurWidth;
    int _blurHeight;
    int _apertureSize;
    double _maxLineGap;
    double _minLineLength;
    int _houghThreshold;
    double _cannyThreshold1;
    double _cannyThreshold2;
  };
}

#endif //ROOKIE_LINE_RESOLVER_HPP
