//
// Created by mcountryman on 4/7/2020.
//

#ifndef ROOKIE_FRAME_HPP
#define ROOKIE_FRAME_HPP

#include <utility>
#include <vector>
#include "../cell.hpp"
#include "quad.hpp"
#include "triangle.hpp"
#include "line_segment.hpp"

namespace rookie::board::frame {
  using rookie::math::Quad;
  using rookie::math::Triangle;
  using rookie::math::LineSegment;

  class Frame {
  public:
    Frame(
      std::vector<std::vector<Cell>> &cells,
      std::vector<LineSegment<float>> &lines,
      std::vector<float> &points,
      std::vector<Quad<float>> &quads,
      std::vector<Triangle<float>> &triangles
    ) :
      _cells(cells),
      _lines(lines),
      _quads(quads),
      _points(points),
      _triangles(triangles) {}

  public:
    [[nodiscard]] std::vector<float> points() const { return _points; }
    [[nodiscard]] std::vector<Quad<float>> quads() const { return _quads; }
    [[nodiscard]] std::vector<std::vector<Cell>> cells() const { return _cells; }
    [[nodiscard]] std::vector<LineSegment<float>> lines() const { return _lines; }
    [[nodiscard]] std::vector<Triangle<float>> triangles() const { return _triangles; }

  private:
    std::vector<float> _points;
    std::vector<Quad<float>> _quads;
    std::vector<std::vector<Cell>> _cells;
    std::vector<LineSegment<float>> _lines;
    std::vector<Triangle<float>> _triangles;
  };
}

#endif //ROOKIE_FRAME_HPP
