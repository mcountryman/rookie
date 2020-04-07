//
// Created by mcountryman on 4/7/2020.
//

#ifndef ROOKIE_LINE_RESOLVER_HPP
#define ROOKIE_LINE_RESOLVER_HPP

#include <vector>
#include <opencv2/core/mat.hpp>
#include "../../../math/segment.hpp"

namespace rookie::board::frame::resolvers {
  class LineResolver {
  public:
    LineResolver() :
      _rho(MATH_PI / 180),
      _theta(50),
      _blurWidth(3),
      _blurHeight(3),
      _apertureSize(3),
      _maxLineGap(0),
      _minLineLength(10),
      _houghThreshold(50),
      _cannyThreshold1(50),
      _cannyThreshold2(200) {}
  public:
    std::vector<math::Segmenti> Resolve(cv::Mat &frame) const;
  private:
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
