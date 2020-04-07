//
// Created by mcountryman on 4/7/2020.
//

#ifndef ROOKIE_FRAME_RESOLVER_HPP
#define ROOKIE_FRAME_RESOLVER_HPP

#include <opencv2/core/mat.hpp>
#include "frame.hpp"
#include "resolvers/line_resolver.hpp"

namespace rookie::board::frame {
  class FrameResolver {
  public:
    inline Frame Resolve(cv::Mat &frame) {
      auto lines = _lineResolver.Resolve(frame);

      return Frame(lines);
    }
  private:
    resolvers::LineResolver _lineResolver;
  };
}

#endif //ROOKIE_FRAME_RESOLVER_HPP
