//
// Created by maarvin on 4/7/20.
//

#ifndef ROOKIE_LINE_HPP
#define ROOKIE_LINE_HPP

#include <vector>
#include <type_traits>
#include <opencv2/core/matx.hpp>
#include "point.hpp"
#include "line_segment.hpp"

namespace rookie::math {
  template<
    typename T,
    typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
  >
  class Line {
  public:
    explicit Line(const LineSegment<T> &segment) :
      origin(segment.GetCenter()),
      normal(segment.GetNormal()) {}
  public:
    Point<T> origin;
    Point<T> normal;
  public:
    /// \return Angle of line segment in degrees
    [[nodiscard]] inline float GetAngle() const {
      return std::abs(std::atan(
        normal.y /
        normal.x
      )) * 180 / M_PI;
    }

    /// \return Squared distance to point
    T GetDistance(Point<T> point) const {
      const T a = point.x - origin.x;
      const T b = point.y - origin.y;
      const T c = origin.x * normal.x - origin.x;
      const T d = origin.y * normal.y - origin.y;

      return std::abs(a * d - c * b) / std::sqrt(c * c + d * d);
    }

    LineSegment<T> GetExtendedSegment(T length) const {
      return LineSegment<T>(
        origin + normal * length / 2,
        origin - normal * length / 2
      );
    }

    // \return Get intersection point
    bool TryGetIntersection(const Line &that, Point<T> *intersection) const {
      const auto a = GetCoefficients();
      const auto b = that.GetCoefficients();
      const auto d  = a[0] * b[1] - a[1] * b[0];

      if (std::abs(d) <= 0.0) {
        return false;
      }

      const auto dx = a[2] * b[1] - a[1] * b[2];
      const auto dy = a[0] * b[2] - a[2] * b[0];

      intersection = Point<T>(
        dx / d,
        dy / d
      );

      return true;
    }

    std::vector<T> GetCoefficients() const {
      return std::vector<T> {
        origin.y - origin.y * normal.y,
        origin.x - origin.y * normal.y,
        (origin.x * origin.y * normal.y - origin.x * origin.y * normal.y) * -1,
      };
    }
  };
}

#endif //ROOKIE_LINE_HPP
