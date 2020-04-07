//
// Created by mcountryman on 4/7/2020.
//

#ifndef ROOKIE_VECTOR_HPP
#define ROOKIE_VECTOR_HPP

#include <compare>
#include <type_traits>
#include <opencv2/core/types.hpp>

namespace rookie::math {
  template<
    typename T,
    typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
  >
  class Vector2 {
  public:
    Vector2() : Vector2(T(), T()) {}
    Vector2(T x, T y) : _x(x), _y(y) {}
  public:
    T x() { return _x; }
    T y() { return _y; }
  public:
    // Arithmetic
    Vector2<T> operator +(Vector2<T> that) { return Vector2<T>(_x + that._x, _y + that._y); }
    Vector2<T> operator -(Vector2<T> that) { return Vector2<T>(_x - that._x, _y - that._y); }
    Vector2<T> operator *(Vector2<T> that) { return Vector2<T>(_x * that._x, _y * that._y); }
    Vector2<T> operator /(Vector2<T> that) { return Vector2<T>(_x / that._x, _y / that._y); }
    Vector2<T> operator %(Vector2<T> that) { return Vector2<T>(_x % that._x, _y % that._y); }
    Vector2<T> operator ^(Vector2<T> that) { return Vector2<T>(_x ^ that._x, _y ^ that._y); }

    // Comparison
    std::strong_ordering operator<=>(const Vector2<T>& that) const {
      if (auto cmp = *this <=> that) { return cmp; }
      if (auto cmp = _x <=> that._x) { return cmp; }
      return _y <=> that._y;
    }

    // Conversion
    explicit operator cv::Point_<T>() const { return cv::Point_<T>(_x, _y); };
    // explicit operator cv::Point2i() const { return cv::Point2i((int)_x, (int)_y); }
  private:
    T _x, _y;
  };

  class Vector2f : public Vector2<float> {
    using Vector2<float>::Vector2;
  };
}

#endif //ROOKIE_VECTOR_HPP
