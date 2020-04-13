//
// Created by mcountryman on 4/7/2020.
//

#ifndef ROOKIE_FRAME_RESOLVER_HPP
#define ROOKIE_FRAME_RESOLVER_HPP

#include <opencv2/core/mat.hpp>
#include <frame/resolvers/grid_resolver.hpp>
#include "frame.hpp"
#include "resolvers/line_resolver.hpp"
#include "resolvers/quad_resolver.hpp"
#include "resolvers/point_resolver.hpp"
#include "resolvers/triangle_resolver.hpp"

namespace rookie::board::frame {
  class FrameResolver {
  public:
    inline Frame Resolve(cv::Mat &frame) {
      auto lines = _lineResolver.Resolve(frame);
      auto points = _pointResolver.Resolve(lines);
      auto triangles = _triangleResolver.Resolve(points);
      auto quads = _quadResolver.Resolve(triangles);
      auto cells = _gridResolver.Resolve(quads);

      return Frame(cells, lines, points, quads, triangles);
    }
  private:
    resolvers::GridResolver _gridResolver;
    resolvers::LineResolver _lineResolver;
    resolvers::QuadResolver _quadResolver;
    resolvers::PointResolver _pointResolver;
    resolvers::TriangleResolver _triangleResolver;
  };
}

#endif //ROOKIE_FRAME_RESOLVER_HPP
