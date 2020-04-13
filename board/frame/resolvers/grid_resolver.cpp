//
// Created by maarvin on 4/10/20.
//

#include <map>
#include <vector>
#include <cell.hpp>
#include "quad.hpp"
#include "grid_resolver.hpp"

namespace rookie::board::frame::resolvers {
  using namespace rookie::math;

  enum class Position {
    None = -1,

    Top,
    Left,
    Right,
    Bottom,
  };

  Position GetNeighborPosition(const Quad<float> &quad, Quad<float> &candidate) {
    if (quad.top == candidate.bottom)
      return Position::Left;
    if (quad.left == candidate.right)
      return Position::Left;
    if (quad.right == candidate.left)
      return Position::Right;
    if (quad.bottom == candidate.top)
      return Position::Bottom;

    return Position::None;
  }

  std::map<Position, int> GetNeighbors(
    int i,
    const Quad<float> &quad,
    std::vector<Quad<float>> &quads
  ) {

    std::map<Position, int> neighbors;

    for (auto j = 0; j < quads.size(); j++) {
      if (i == j)
        continue;

      const auto position = GetNeighborPosition(quad, quads[j]);

      if (position != Position::None) {
        neighbors[position] = j;
      }
    }

    return neighbors;
  };

  std::vector<std::vector<Cell>> GridResolver::Resolve(std::vector<Quad<float>> &quads) {
    std::sort(
      quads.begin(),
      quads.end(),
      [](Quad<float> lhs, Quad<float> rhs) {
        const auto lhs_center = lhs.GetCenter();
        const auto rhs_center = rhs.GetCenter();

        return
          std::tie(lhs_center.y, lhs_center.x) <
          std::tie(rhs_center.y, rhs_center.x);
      }
    );

    std::vector<std::vector<Cell>> results;

    for (auto i = 0; i < quads.size(); i++) {
      auto quad = quads[i];
      auto neighbors = GetNeighbors(i, quad, quads);
      auto quad_row_start = quad;

      if (neighbors.size() != 2) {
        continue;
      }

      auto x = 0;
      auto y = 0;

      for (;;) {
        if (x < 7) {
          const auto it = neighbors.find(Position::Right);

          if (it == neighbors.end())
            break;

          quad = quads[it->second];
        }

      }
    }

    return results;
  }
}
