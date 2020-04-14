//
// Created by maarvin on 4/9/20.
//

#include <delaunator.hpp>
#include "triangle.hpp"
#include "triangle_resolver.hpp"

namespace rookie::board::frame::resolvers {
  using namespace rookie::math;

  std::vector<Triangle<float>> TriangleResolver::Resolve(
    const std::vector<float> &points
  ) const {
    std::vector<Triangle<float>> result;

    if (points.size() < 3) {
      return result;
    }

    try {
      delaunator::Delaunator d(points);

      for (auto i = 0; i < d.triangles.size(); i += 3) {
        result.emplace_back(
          points[2 * d.triangles[i + 0] + 0],
          points[2 * d.triangles[i + 0] + 1],
          points[2 * d.triangles[i + 1] + 0],
          points[2 * d.triangles[i + 1] + 1],
          points[2 * d.triangles[i + 2] + 0],
          points[2 * d.triangles[i + 2] + 1]
        );
      }
    } catch(std::exception &ex) {
      // do nothing
    }

    return result;
  }
}