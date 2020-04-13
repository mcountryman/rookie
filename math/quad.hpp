//
// Created by maarvin on 4/9/20.
//

#ifndef ROOKIE_QUAD_HPP
#define ROOKIE_QUAD_HPP

#include <map>
#include <optional>
#include <type_traits>
#include "point.hpp"
#include "position.hpp"
#include "line_segment.hpp"

namespace rookie::math {
  template<
    typename T,
    typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
  >
  class Quad {
  public:
    Point<T> p1, p2, p3, p4;
    LineSegment<T> left, bottom, right, top;
  public:
    Quad() : Quad(Point<T>(), Point<T>(), Point<T>(), Point<T>()) {}
    Quad(const Point<T> &p1, const Point<T> &p2, const Point<T> &p3, const Point<T> &p4) :
      p1(p1),
      p2(p2),
      p3(p3),
      p4(p4),
      left(p1, p2),
      bottom(p2, p3),
      right(p3, p4),
      top(p4, p1) {}
  public:
    std::vector<Point<T>> points() const {
      return std::vector<Point<T>> {
        p1,
        p2,
        p3,
        p4,
      };
    }

    std::vector<LineSegment<T>> lines() const {
      return std::vector<LineSegment<T>> {
        left,
        bottom,
        right,
        top,
      };
    }
  public:
    T GetArea() const {
      T area = 0;

      for (const auto &line : lines()) {
        area += line.GetLengthSquared();
      }

      return area;
    }

    Point<T> GetCenter() const {
      return LineSegment<T>(p2, p4).GetCenter();
    }

    T GetLineDelta() const {
      return GetLongestLineLengthSquared() - GetShortestLineLengthSquared();
    }

    T GetLongestLineLengthSquared() const {
      auto length = 0;

      for (const auto &line : lines()) {
        auto line_length = line.GetLengthSquared();
        if (line_length > length)
          length = line_length;
      }

      return length;
    }

    T GetShortestLineLengthSquared() const {
      auto length = std::numeric_limits<T>::max();

      for (const auto &line : lines()) {
        auto line_length = line.GetLengthSquared();
        if (line_length < length)
          length = line_length;
      }

      return length;
    }

    Position GetNeighborPosition(const Quad<T> &candidate) const {
      if (top == candidate.bottom)
        return Position::Left;
      if (left == candidate.right)
        return Position::Left;
      if (right == candidate.left)
        return Position::Right;
      if (bottom == candidate.top)
        return Position::Bottom;

      return Position::None;
    }

    std::optional<Quad<T>> GetBottomNeighbor(std::vector<Quad<T>> &quads) const {
      for (const auto &candidate : quads) {
        const auto position = GetNeighborPosition(candidate);

        if (position == Position::Bottom) {
          return candidate;
        }
      }

      return {};
    }

    std::optional<Quad<T>> GetRightNeighbor(std::vector<Quad<T>> &quads) const {
      for (const auto &candidate : quads) {
        const auto position = GetNeighborPosition(candidate);

        if (position == Position::Right) {
          return candidate;
        }
      }

      return {};
    }

    std::map<Position, Quad<T>> GetNeighbors(std::vector<Quad<T>> &quads) const {
      std::map<Position, Quad<T>> neighbors;

      for (const auto &candidate : quads) {
        const auto position = GetNeighborPosition(candidate);

        if (position != Position::None) {
          neighbors[position] = candidate;
        }
      }

      return neighbors;
    }
  public:
    bool operator ==(const Quad<T> &that) const {
      for (const auto &pa : points())
      for (const auto &pb : that.points())
        if (pa != pb)
          return false;

      return true;
    }

    template<typename TInner>
    explicit operator std::vector<TInner>() const {
      return std::vector {
        static_cast<TInner>(p1),
        static_cast<TInner>(p2),
        static_cast<TInner>(p3),
        static_cast<TInner>(p4),
      };
    }
  };
}

#endif //ROOKIE_QUAD_HPP
