//
// Created by maarvin on 4/9/20.
//

#ifndef ROOKIE_QUAD_RESOLVER_HPP
#define ROOKIE_QUAD_RESOLVER_HPP

#include <vector>
#include "quad.hpp"
#include "triangle.hpp"

namespace rookie::board::frame::resolvers {
  using rookie::math::Quad;
  using rookie::math::Triangle;

  class QuadResolver {
  public:
    std::vector<Quad<float>> Resolve(std::vector<Triangle<float>> &triangles);
  };
}

#endif //ROOKIE_QUAD_RESOLVER_HPP
