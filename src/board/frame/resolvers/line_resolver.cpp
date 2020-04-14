//
// Created by mcountryman on 4/7/2020.
//

#include <vector>
#include <opencv2/imgproc/imgproc.hpp>
#include "line_segment.hpp"
#include "line_resolver.hpp"

namespace rookie::board::frame::resolvers {
  using namespace rookie::math;

  std::vector<LineSegment<float>> GetExtendedLines(
    cv::Mat &frame,
    const std::size_t maxLines,
    const std::vector<cv::Vec4i> &lines
  ) {

    std::vector<LineSegment<float>> result;

    for (const auto &i : lines) {
      // CPU throttle
      if (result.size() >= maxLines)
        return result;

      const auto line = LineSegment<float>(i);
      const auto length = line.GetLength();
      const auto extended = line.GetExtended(length * 4);

      result.push_back(extended);
    }

    return result;
  }

  std::vector<LineSegment<float>> LineResolver::Resolve(cv::Mat &frame) const {
    cv::Mat gray;
    cv::Mat edges;
    cv::Mat blurred;
    std::vector<cv::Vec4i> lines;

    // Edge detection
    cv::blur(frame, blurred, cv::Size(_blurWidth, _blurHeight));
    cv::Canny(frame, edges, _cannyThreshold1, _cannyThreshold2);

    // Probabilistic line detection
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    cv::HoughLinesP(
      edges,
      lines,
      _rho,
      _theta,
      _houghThreshold,
      _minLineLength,
      _maxLineGap
    );

    return GetExtendedLines(frame, _maxLines, lines);
  }
}