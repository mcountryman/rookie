//
// Created by maarvin on 4/9/20.
//

#include <set>
#include <map>
#include "quad_resolver.hpp"

namespace rookie::board::frame::resolvers {
  using namespace rookie::math;

  std::vector<Quad<float> > QuadResolver::Resolve(
    std::vector<Triangle<float>> &triangles
  ) {

    std::map<int, bool> merged;
    std::vector<Quad<float>> result;

    for (auto i = 0; i < triangles.size(); i++) {
      if (merged[i]) {
        continue;
      }

      const auto triangle_a = triangles[i];
      const auto longest = triangle_a.GetLongestLine();
      const auto longest_center = longest.GetCenter();

      for (auto j = i + 1; j < triangles.size(); j++) {
        if (merged[j]) {
          continue;
        }

        auto sort = [longest_center](Point<float> a, Point<float> b) {
          return
            a.GetClockwiseAngle(longest_center) <
            b.GetClockwiseAngle(longest_center);
        };

        std::set<Point<float>, decltype(sort)> points(sort);
        const auto triangle_b = triangles[j];

        if (longest != triangle_b.GetLongestLine())
          continue;

        for (const auto &point : triangle_a.points())
          points.insert(point);
        for (const auto &point : triangle_b.points())
          points.insert(point);
        if (points.size() < 4)
          continue;

        std::vector<Point<float>> corners(points.begin(), points.end());
        Quad<float> quad(
          corners[0],
          corners[1],
          corners[2],
          corners[3]
        );

        auto shortest_length = quad.GetShortestLineLengthSquared();
        auto longest_length = quad.GetLongestLineLengthSquared();

        if (longest_length / 2 <= shortest_length) {
          result.push_back(quad);
        }

        merged[j] = true;
      }
    }

    return result;
  }
}