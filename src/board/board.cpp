//
// Created by mcountryman on 4/7/2020.
//

#include <chrono>
#include <string>
#include <vector>
#include <opencv2/imgproc.hpp>
#include "frame/frame_resolver.hpp"
#include "board.hpp"
#include "format.hpp"

namespace rookie::board {
  using namespace std::chrono;
  using namespace rookie::board::frame;

  typedef high_resolution_clock clock;

  void drawText(cv::Mat &in, std::initializer_list<std::string> lines) {
    auto y = 5;
    const auto x = 5;
    const auto font = cv::FONT_HERSHEY_SIMPLEX;
    const auto scale = 0.4;
    const auto color = cv::Scalar(0, 0, 255, 200);
    const auto margin = 5;
    const auto thickness = 0;

    for (const auto &line : lines) {
      const auto size = cv::getTextSize(line, font, scale, thickness, nullptr);
      y += size.height;

      cv::rectangle(
        in,
        cv::Point(x - size.width, y - size.height - margin),
        cv::Point(x + size.width + margin, y + size.height),
        cv::Scalar(0, 0, 0, 200),
        -1
      );

      cv::putText(
        in,
        line,
        cv::Point(x, y),
        font,
        scale,
        color,
        thickness
      );

      y += margin * 2;
    }
  }

  void drawCells(cv::Mat &in, const Frame &frame) {
    auto id = 0;
    const auto font = cv::FONT_HERSHEY_SIMPLEX;
    const auto scale = 0.4;
    const auto color = cv::Scalar(0, 0, 0);
    const auto margin = 5;
    const auto thickness = 0;

    for (auto y = 0; y < frame.cells().size(); y++) {
      const auto row = frame.cells()[y];

      for (auto x = 0; x < row.size(); x++) {
        const auto cell = row[x];
        const auto column = std::string("ABCDEFGH")[x];

        cv::putText(
          in,
          format("%c,%d", column, y + 1),
          static_cast<cv::Point>(cell.quad.GetCenter()),
          font,
          scale,
          color,
          thickness
        );
      }
    }
  }

  void drawLines(cv::Mat &in, const Frame &frame) {
    for (auto &line : frame.lines()) {
      cv::line(
        in,
        static_cast<cv::Point>(line.origin),
        static_cast<cv::Point>(line.end),
        cv::Scalar(0, 255, 0, 255)
      );
    }
  }

  void drawPoints(cv::Mat &in, const Frame &frame) {
    const auto points = frame.points();

    for (auto i = 0; i < points.size(); i += 2) {
      cv::circle(
        in,
        cv::Point(
          points[i],
          points[i + 1]
        ),
        3,
        cv::Scalar(255, 0, 0, 255)
      );
    }
  }

  void drawQuads(cv::Mat &in, const Frame &frame) {
    const auto font = cv::FONT_HERSHEY_SIMPLEX;
    const auto scale = 0.4;
    const auto color = cv::Scalar(0, 0, 0);
    const auto margin = 5;
    const auto thickness = 0;

    for (const auto &quad : frame.quads()) {
      auto points = std::vector<std::vector<cv::Point>>();
      points.push_back(static_cast<std::vector<cv::Point>>(quad));

      cv::fillPoly(
        in,
        points,
        cv::Scalar(255, 0, 255)
      );
    }
  }

  void drawTriangles(cv::Mat &in, const Frame &frame) {
    for (const auto &triangle : frame.triangles()) {
      cv::polylines(
        in,
        static_cast<std::vector<cv::Point>>(triangle),
        true,
        cv::Scalar(0, 0, 255, 255)
      );
    }
  }

  auto fps = 0.0;
  auto fps_factor = 0.9;
  auto frame_last = clock::now();

  auto resolve_ms = 0.0;

  void warpBoard(cv::Mat &in, const Frame &frame) {
    const auto tr = frame.cells()[0][0];
    const auto tl = frame.cells()[0][7];
    const auto br = frame.cells()[7][0];
    const auto bl = frame.cells()[7][7];

    auto m = cv::getPerspectiveTransform(
      std::vector<cv::Point2f> {
        static_cast<cv::Point2f>(tr.quad.p1),
        static_cast<cv::Point2f>(tl.quad.p4),
        static_cast<cv::Point2f>(br.quad.p2),
        static_cast<cv::Point2f>(bl.quad.p3)
      },
      std::vector<cv::Point2f> {
        cv::Point2f(0, 0),
        cv::Point2f(in.size[0], 0),
        cv::Point2f(0, in.size[1]),
        cv::Point2f(in.size[0], in.size[1]),
      }
    );

    cv::warpPerspective(in, in, m, cv::Size(in.size[0], in.size[1]));
  }

  bool Board::ProcessFrame(cv::Mat &in) {
    const auto resolve_before = clock::now();
    const auto frame = _frameResolver.Resolve(in);
    const auto resolve_delta = clock::now() - resolve_before;
    resolve_ms = (float) duration_cast<milliseconds>(resolve_delta).count();

    if (frame.cells().empty())
      return false;

    const auto frame_now = clock::now();
    const auto frame_delta = frame_now - frame_last;
    frame_last = frame_now;
    const auto frame_ms = (float) duration_cast<milliseconds>(frame_delta).count();
    const auto frame_seconds = frame_ms / 1000;

    fps = (fps * fps_factor) + (1.0 / frame_seconds * (1.0 - fps_factor));

    if (_drawDebugQuads)
      drawQuads(in, frame);
    if (_drawDebugLines)
      drawLines(in, frame);
    if (_drawDebugPoints)
      drawPoints(in, frame);
    if (_drawDebugTriangles)
      drawTriangles(in, frame);
    if (_drawDebugCells)
      drawCells(in, frame);

    warpBoard(in, frame);

    if (_drawDebugInfo)
      drawText(in, {
        format("fps  : %4.2f", fps),
        format("frame: %4.2fms", frame_ms),
        format("resolve: %4.2fms", resolve_ms),
        format("est_resolve: %4.2fms", resolve_ms * 5),
        format("lines: %zu", frame.lines().size()),
        format("quads: %zu", frame.quads().size()),
        format("points: %zu", frame.points().size()),
        format("triangles: %zu", frame.triangles().size()),
        format(
          "tri_quad_ratio %4.2f%%",
          ((float)frame.quads().size() / (float)frame.triangles().size()) * 100
        ),
      });

    return true;
  }
}
