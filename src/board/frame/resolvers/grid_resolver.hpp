//
// Created by maarvin on 4/10/20.
//

#ifndef ROOKIE_GRID_RESOLVER_HPP
#define ROOKIE_GRID_RESOLVER_HPP

#include <vector>
#include "quad.hpp"
#include "../../cell.hpp"

namespace rookie::board::frame::resolvers {
  using rookie::math::Quad;

  class GridResolver {
  public:
    std::vector<std::vector<Cell>> Resolve(std::vector<Quad<float>> &quads);
  };
}

#endif //ROOKIE_GRID_RESOLVER_HPP
