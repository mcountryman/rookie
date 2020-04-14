//
// Created by maarvin on 4/8/20.
//

#include <map>
#include <vector>
#include <opencv2/opencv.hpp>
#include "point.hpp"
#include "line_segment.hpp"
#include "point_resolver.hpp"

namespace rookie::board::frame::resolvers {
  using namespace rookie::math;

  float round(float value, float multiple) {
    const int valueRound = (int)std::round(value);
    const int multipleRound = (int)std::round(multiple);
    const int remainder = std::abs(valueRound) % multipleRound;

    if (remainder == 0)
      return (float)valueRound;
    if ((float)remainder < multiple / 2)
      return (float)(valueRound - remainder);

    return (float)(valueRound + multipleRound - remainder);
  }

  std::vector<float> PointResolver::Resolve(
    const std::vector<LineSegment<float>> &lines
  ) const {

    std::vector<float> result;

    for (auto i = 0; i < lines.size(); i++) {
      for (auto j = i + 1; j < lines.size(); j++) {
        // CPU throttle
        if (result.size() >= _maxPoints)
          return result;

        const auto angleA = lines[i].GetAngle();
        const auto angleB = lines[j].GetAngle();
        const auto angleDelta = std::abs(angleA - angleB);

        if (_angleThreshold >= angleDelta) {
          continue;
        }

        Point<float> point;

        if (!lines[i].TryGetIntersection(lines[j], &point)) {
          continue;
        }

        auto ignore = false;

        for (auto k = 0; k < result.size(); k += 2) {
          if (
            std::abs(result[k] - point.x) < _distanceThreshold &&
            std::abs(result[k + 1] - point.y) < _distanceThreshold
          ) {
            ignore = true;
            break;
          }
        }

        if (ignore) {
          continue;
        }

        result.push_back(point.x);
        result.push_back(point.y);
      }
    }

    return result;
  }
}