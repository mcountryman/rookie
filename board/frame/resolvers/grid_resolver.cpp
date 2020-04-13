//
// Created by maarvin on 4/10/20.
//

#include <map>
#include <vector>
#include <cell.hpp>
#include "quad.hpp"
#include "position.hpp"
#include "grid_resolver.hpp"

namespace rookie::board::frame::resolvers {
  using namespace rookie::math;

  bool TryResolveGridRow(
    const Quad<float> &first_quad,
    std::vector<Quad<float>> &quads,
    std::vector<std::vector<Cell>> &result
  ) {

    std::vector<Cell> row;

    auto current_quad = first_quad;
    row.emplace_back(current_quad);

    for (auto x = 0; x < 7; x++) {
      if (auto neighbor = current_quad.GetRightNeighbor(quads)) {
        current_quad = neighbor.value();
        row.emplace_back(current_quad);
      } else {
        return false;
      }
    }

    result.push_back(row);
    return true;
  }

  bool TryResolveGrid(
    const Quad<float> &quad,
    std::vector<Quad<float>> &quads,
    std::vector<std::vector<Cell>> &result
  ) {

    auto current_quad = quad;

    for (auto y = 0; y < 7; y++) {
      std::vector<Cell> row;

      if (!TryResolveGridRow(current_quad, quads, result)) {
        return false;
      }

      if (auto neighbor = current_quad.GetBottomNeighbor(quads)) {
        current_quad = neighbor.value();
      } else {
        return false;
      }
    }

    return TryResolveGridRow(current_quad, quads, result);
  }

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

    for (const auto &quad : quads) {
      std::vector<std::vector<Cell>> results;

      if (TryResolveGrid(quad, quads, results)) {
        return results;
      }
    }

    return std::vector<std::vector<Cell>>();
  }
}
