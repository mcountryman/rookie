//
// Created by mcountryman on 4/7/2020.
//

#include <map>
#include <vector>
#include <opencv2/imgproc/imgproc.hpp>

#include "../../../math/segment.hpp"
#include "line_resolver.hpp"

namespace rookie::board::frame::resolvers {
  using namespace rookie::math;

  std::vector<Segmenti> GetMergedLines(const std::vector<cv::Vec4i>& lines) {
    std::map<int, bool> merged;
    std::vector<Segmenti> result;

    for (auto i = 0; i < lines.size(); i++) {
      if (merged[i]) {
        continue;
      }

      auto segmentA = Segmenti(lines[i]);

      for (auto j = i + 1; j < lines.size(); j++) {
        auto segmentB = Segmenti(lines[j]);

      }
    }

    return result;
  }

  std::vector<Segmenti> LineResolver::Resolve(cv::Mat &frame) const {
    cv::Mat gray;
    cv::Mat edges;
    cv::Mat blurred;
    std::vector<cv::Vec4i> lines;

    // Edge detection
    cv::blur(frame, blurred, cv::Size(_blurWidth, _blurHeight));
    cv::Canny(blurred, edges, _cannyThreshold1, _cannyThreshold2, _apertureSize);

    // Probabilistic line detection
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    cv::HoughLinesP(gray, lines, _rho, _theta, _houghThreshold, _minLineLength, _maxLineGap);

    return GetMergedLines(lines);
  }
}