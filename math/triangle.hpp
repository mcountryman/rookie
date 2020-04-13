//
// Created by maarvin on 4/9/20.
//

#ifndef ROOKIE_TRIANGLE_HPP
#define ROOKIE_TRIANGLE_HPP

#include <vector>
#include <algorithm>
#include "point.hpp"
#include "line_segment.hpp"

namespace rookie::math {
  template<
    typename T,
    typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
  >
  class Triangle {
  public:
    Point<T> p1, p2, p3;
    LineSegment<T> l1, l2, l3;
  public:
    Triangle(T x1, T y1, T x2, T y2, T x3, T y3) :
      Triangle(
        Point<T>(x1, y1),
        Point<T>(x2, y2),
        Point<T>(x3, y3)
      ) {}

    Triangle(const Point<T> &p1, const Point<T> &p2, const Point<T> &p3) :
      p1(p1),
      p2(p2),
      p3(p3),
      l1(p1, p2),
      l2(p2, p3),
      l3(p3, p1) {}
  public:
    std::vector<Point<T>> points() const {
      return std::vector<Point<T>> {
        p1,
        p2,
        p3,
      };
    }

    std::vector<LineSegment<T>> lines() const {
      return std::vector<LineSegment<T>> {
        l1,
        l2,
        l3,
      };
    }
  public:
    bool HasSharedLine(const Triangle<T> &that) const {
      auto shared_count = 0;

      for (auto &pa : points()) {
        for (auto &pb : points()) {
          if (pa == pb) {
            shared_count++;
            break;
          }
        }

        if (shared_count == 2)
          return true;
      }

      return false;
    }

    LineSegment<T> GetLongestLine() const {
      const auto l1_length = l1.GetLengthSquared();
      const auto l2_length = l2.GetLengthSquared();
      const auto l3_length = l3.GetLengthSquared();
      const auto max_length = std::max(std::max(l1_length, l2_length), l3_length);

      if (max_length == l1_length)
        return l1;
      if (max_length == l2_length)
        return l2;

      return l3;
    }
  public:
    template<typename TInner>
    explicit operator std::vector<TInner>() const {
      return std::vector {
        static_cast<TInner>(p1),
        static_cast<TInner>(p2),
        static_cast<TInner>(p3),
      };
    }
  };
}

#endif //ROOKIE_TRIANGLE_HPP
