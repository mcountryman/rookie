//
// Created by maarvin on 4/7/20.
//

#ifndef ROOKIE_POINT_HPP
#define ROOKIE_POINT_HPP

#include <cmath>
#include <type_traits>
#include <opencv2/core/types.hpp>

namespace rookie::math {
  template<
    typename T,
    typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
  >
  class Point {
  public:
    T x, y;
  public:
    Point() : Point(0.0, 0.0) {}
    Point(T &x, T &y) : x(x), y(y) {}
    Point(const T &x, const T &y) : x(x), y(y) {}
  public:
    Point<T> abs() const { Point<T>(std::abs(x), std::abs(y)); }
    T clockwise_angle() const { return (-1 * std::atan2(x, -1 * y)); }
  public:

    T GetDot(Point<T> that) const {
      return x * that.x + y * that.y;
    }

    T GetDistance(Point<T> that) const {
      const T xDelta = x - that.x;
      const T yDelta = y - that.y;

      return std::sqrt(
        xDelta * xDelta +
        yDelta * yDelta
      );
    }

    T GetDistanceSquared(Point<T> that) const {
      const T xDelta = x - that.x;
      const T yDelta = y - that.y;

      return xDelta * xDelta + yDelta * yDelta;
    }

    T GetClockwiseAngle(Point<T> center) const {
      return std::atan2(x - center.x, y - center.y);
    }
  public:
    // Comparison

    inline bool operator==(const Point<T> &that) const {
      static auto epsilon = std::numeric_limits<T>::epsilon();
      auto x_delta = std::abs(x - that.x);
      auto y_delta = std::abs(y - that.y);

      return x_delta <= epsilon && y_delta <= epsilon;
    }

    inline bool operator!=(const Point<T> &that) const {
      return !(*this == that);
    }

    inline bool operator<(const Point<T> &that) const {
      return x < that.x && y < that.y;
    }

    inline bool operator>(const Point<T> &that) const {
      return x > that.x && y > that.y;
    }

    inline bool operator<=(const Point<T> &that) const {
      return this < that || this == that;
    }

    inline bool operator>=(const Point<T> &that) const {
      return this > that || this == that;
    }

    // Arithmetic

    Point<T> operator+(T that) const { return Point<T>(x + that, y + that); }
    Point<T> operator-(T that) const { return Point<T>(x - that, y - that); }
    Point<T> operator*(T that) const { return Point<T>(x * that, y * that); }
    Point<T> operator/(T that) const { return Point<T>(x / that, y / that); }
    Point<T> operator+(Point<T> that) const { return Point<T>(x + that.x, y + that.y); }
    Point<T> operator-(Point<T> that) const { return Point<T>(x - that.x, y - that.y); }
    Point<T> operator*(Point<T> that) const { return Point<T>(x * that.x, y * that.y); }
    Point<T> operator/(Point<T> that) const { return Point<T>(x / that.x, y / that.y); }

    template<
      typename TOther,
      typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
    >
    explicit operator cv::Point_<TOther>() const {
      return cv::Point_<TOther>((TOther)x, (TOther)y);
    }
  public:
    static Point<T> epsilon() {
      static Point<T> epsilon(
        std::numeric_limits<T>::epsilon(),
        std::numeric_limits<T>::epsilon()
      );

      return epsilon;
    }
  };

  template<
    typename T,
    typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
  >
  Point<T> operator+(const T &rhs, const Point<T> &lhs) {
    return Point<T>(rhs + lhs.x, rhs + lhs.y);
  }

  template<
    typename T,
    typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
  >
  Point<T> operator-(const T &rhs, const Point<T> &lhs) {
    return Point<T>(rhs - lhs.x, rhs - lhs.y);
  }

  template<
    typename T,
    typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
  >
  Point<T> operator*(const T &rhs, const Point<T> &lhs) {
    return Point<T>(rhs * lhs.x, rhs * lhs.y);
  }

  template<
    typename T,
    typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
  >
  Point<T> operator/(const T &rhs, const Point<T> &lhs) {
    return Point<T>(rhs / lhs.x, rhs / lhs.y);
  }
}

#endif //ROOKIE_POINT_HPP
