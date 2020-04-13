//
// Created by maarvin on 4/10/20.
//

#ifndef ROOKIE_CELL_HPP
#define ROOKIE_CELL_HPP

#include "quad.hpp"

namespace rookie::board {
  using rookie::math::Quad;

  class Cell {
  public:
    int id;
    Quad<float> quad;
  public:
    explicit Cell(int id, const Quad<float> &quad) : id(id), quad(quad) {}
  };
}

#endif //ROOKIE_CELL_HPP
