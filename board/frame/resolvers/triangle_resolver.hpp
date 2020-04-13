//
// Created by maarvin on 4/9/20.
//

#ifndef ROOKIE_TRIANGLE_RESOLVER_HPP
#define ROOKIE_TRIANGLE_RESOLVER_HPP

#include <vector>
#include "triangle.hpp"

namespace rookie::board::frame::resolvers {
  using rookie::math::Triangle;

  class TriangleResolver {
  public:
    [[nodiscard]] std::vector<Triangle<float>> Resolve(
      const std::vector<float> &points
    ) const;
  };
}

#endif //ROOKIE_TRIANGLE_RESOLVER_HPP
