//
// Created by maarvin on 4/7/20.
//

#ifndef ROOKIE_LINE_SEGMENT_HPP
#define ROOKIE_LINE_SEGMENT_HPP

#include <cmath>
#include <type_traits>
#include <opencv2/core/matx.hpp>
#include "point.hpp"

namespace rookie::math {
  template<
    typename T,
    typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
  >
  class LineSegment {
  public:
    LineSegment() :
      LineSegment(Point<T>(), Point<T>()) {}

    LineSegment(T x1, T y1, T x2, T y2) :
      LineSegment(Point<T>(x1, y1), Point<T>(x2, y2)) {}

    template<
      typename TOther,
      typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
    >
    explicit LineSegment(cv::Vec<TOther, 4> vec) :
      LineSegment((T)vec[0], (T)vec[1], (T)vec[2], (T)vec[3]) {}

    LineSegment(Point<T> origin, Point<T> end) :
      origin(origin),
      end(end) {}
  public:
    Point<T> origin, end;
  public:
    T GetDot() const {
      return origin.GetDot(end);
    }

    /// \return Angle of line segment in degrees
    [[nodiscard]] inline float GetAngle() const {
      return std::atan2(
        origin.y - end.y,
        origin.x - end.y
      ) * 180 / M_PI;
    }

    Point<T> GetCenter() const {
      return Point<T>(
        (origin.x + end.x) / 2,
        (origin.y + end.y) / 2
      );
    }

    Point<T> GetNormal() const {
      const auto length = GetLength();

      return Point<T>(
        (end.x - origin.x) / length,
        (end.y - origin.y) / length
      );
    }

    /// \return Distance between origin and end
    T GetLength() const {
      return origin.GetDistance(end);
    }

    /// \return Squared distance between origin and end
    T GetLengthSquared() const {
      return origin.GetDistanceSquared(end);
    }

    /// \return Distance to point
    T GetDistance(Point<T> point) const {
      return std::sqrt(GetDistanceSquared(point));
    }

    LineSegment<T> GetExtended(T length) const {
      const auto center = GetCenter();
      const auto normal = GetNormal();

      return LineSegment<T>(
        center + normal * length / 2,
        center - normal * length / 2
      );
    }

    /// \return Squared distance to point
    T GetDistanceSquared(Point<T> point) const {
      const T length = GetLengthSquared();

      if (length == 0.0) {
        return origin.GetDistance(point);
      }

      const T c = (point - origin).GetDot(end - origin);
      const T t = std::max(0, std::min(1, c / length));
      const Point<T> projection = origin + t * (end - origin);

      return point.GetDistanceSquared(projection);
    }

    /// \return Distance to line
    T GetDistance(LineSegment<T> that) const {
      return std::min(
        GetDistance(that.origin),
        GetDistance(that.end)
      );
    }

    /// \return Squared distance to line
    T GetDistanceSquared(LineSegment<T> that) const {
      return std::min(
        GetDistance(that.origin),
        GetDistance(that.end)
      );
    }

    /// \note Kindly stolen from https://stackoverflow.com/a/1968345
    /// \return Get intersection point
    bool TryGetIntersection(const LineSegment<T> &that, Point<T> *intersection) const {
      T s1_x = end.x - origin.x;
      T s1_y = end.y - origin.y;
      T s2_x = that.end.x - that.origin.x;
      T s2_y = that.end.y - that.origin.y;
      T s = (-s1_y * (origin.x - that.origin.x) + s1_x * (origin.y - that.origin.y)) /
        (-s2_x *
        s1_y +
        s1_x *
        s2_y);
      T t = ( s2_x * (origin.y - that.origin.y) - s2_y * (origin.x - that.origin.x)) /
        (-s2_x *
        s1_y +
        s1_x *
        s2_y);


      if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
        // Collision detected
        *intersection = Point<T>(
          origin.x + (t * s1_x),
          origin.y + (t * s1_y)
        );

        return true;
      }

      return false; // No collision
    }
  public:
    bool operator ==(const LineSegment<T> &that) const {
      return
        (origin == that.origin && end == that.end) ||
        (origin == that.end && end == that.origin);
    }

    bool operator !=(const LineSegment<T> &that) const {
      return !(*this == that);
    }

    template<
      typename TOther,
      typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
    >
    explicit operator cv::Vec<TOther, 4>() const {
      return cv::Vec<T, 4>((TOther)origin.x, (TOther)origin.y, (TOther)end.x, (TOther)end.y);
    }
  };
}

#endif //ROOKIE_LINE_SEGMENT_HPP
