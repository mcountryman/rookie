//
// Created by maarvin on 4/8/20.
//

#ifndef ROOKIE_POINT_RESOLVER_HPP
#define ROOKIE_POINT_RESOLVER_HPP

#include <vector>
#include <opencv2/opencv.hpp>
#include "point.hpp"
#include "line_segment.hpp"

namespace rookie::board::frame::resolvers {
  using rookie::math::Point;
  using rookie::math::LineSegment;

  class PointResolver {
  public:
    PointResolver() :
      _maxPoints(800),
      _angleThreshold(45.0),
      _distanceThreshold(20.0) {}
  public:
    [[nodiscard]] std::vector<float> Resolve(const std::vector<LineSegment<float>> &lines) const;
  private:
    std::size_t _maxPoints;
    /// \note Describes how much difference in angle two lines must be before
    // determining intersection point
    float _angleThreshold;
    /// \note Describes how far a point must be from another in order to store
    float _distanceThreshold;
  };
}

#endif //ROOKIE_POINT_RESOLVER_HPP
