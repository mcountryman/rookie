//
// Created by mcountryman on 4/7/2020.
//

#ifndef ROOKIE_SEGMENT_HPP
#define ROOKIE_SEGMENT_HPP

#include <cmath>
#include "vector.hpp"
#include "constants.hpp"
#include "line.hpp"

namespace rookie::math {
  template<
    typename T,
    typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
  >
  class Segment {
  public:
    Segment() : Segment(Vector2<T>(), Vector2<T>()) {}
    Segment(T x1, T y1, T x2, T y2) : Segment(Vector2<T>(x1, y1), Vector2<T>(x2, y2)) {}
    explicit Segment(const cv::Vec<T, 4> &vector) :
      Segment(
        vector[0],
        vector[1],
        vector[2],
        vector[3]
      ) {}

    Segment(Vector2<T> begin, Vector2<T> end) : _begin(begin), _end(end) {}

  public:
    inline Vector2<T> begin() { return _begin; }

    inline Vector2<T> end() { return _end; }

    inline T angle() {
      return std::acos(
        std::pow(_end.x() - _begin.x(), 2) +
        std::pow(_end.y() - _begin.y(), 2)
      ) * 180 / MATH_PI;
    }

    inline T length() { return T(); }
    Vector2<T> middle() { return Vector2<T>(); }

    template<
      typename TThat,
      typename TResult,
      typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
    >
    inline TResult distance(Segment<TThat> that) {
      return TResult();
    }

  public:
  private:
    Vector2<T> _begin;
    Vector2<T> _end;
  };

  class Segmenti : public Segment<int> {
    using Segment::Segment;
  };

  class Segmentf : public Segment<float> {
    using Segment::Segment;
  };

  class Segmentd : public Segment<double> {
    using Segment::Segment;
  };
}

#endif //ROOKIE_SEGMENT_HPP
