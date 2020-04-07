//
// Created by mcountryman on 4/7/2020.
//

#ifndef ROOKIE_LINE_HPP
#define ROOKIE_LINE_HPP

#include <cmath>
#include "vector.hpp"
#include "constants.hpp"
#include "segment.hpp"

namespace rookie::math {
  template<
    typename T,
    typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
  >
  class Line {
  public:
    Line() : Line(Vector2<T>(), T()) {}
    Line(Vector2<T> point, T angle) : _point(point), _angle(angle) {}
  private:
    Vector2<T> _point;
    T          _angle;
  };

  class Linei : public Line<int> { using Line::Line; };
  class Linef : public Line<float> { using Line::Line; };
}

#endif //ROOKIE_LINE_HPP
