cmake_minimum_required(VERSION 3.16)
project(rookie)

set(CMAKE_CXX_STANDARD 20)

if (EXISTS "${PROJECT_SOURCE_DIR}/thirdparty/opencv")
  message("Using local opencv directory")
  set(OpenCV_DIR thirdparty/opencv/build/x64/vc15/lib)
endif ()

find_package(OpenCV REQUIRED)
include_directories(
  math
  utils
  board
  thirdparty
  ${OpenCV_INCLUDE_DIRS}
)

add_executable(
  rookie
  main.cpp
  math/line.hpp
  math/point.hpp
  math/line_segment.hpp
  board/board.cpp
  board/board.hpp
  board/frame/frame.cpp
  board/frame/frame.hpp
  board/frame/frame_resolver.cpp
  board/frame/frame_resolver.hpp
  board/frame/resolvers/line_resolver.cpp
  board/frame/resolvers/line_resolver.hpp
  board/frame/resolvers/point_resolver.cpp
  board/frame/resolvers/point_resolver.hpp
  board/frame/resolvers/triangle_resolver.cpp
  board/frame/resolvers/triangle_resolver.hpp
  utils/format.cpp
  utils/format.hpp
  thirdparty/delaunator.hpp
  math/triangle.hpp board/frame/resolvers/quad_resolver.cpp board/frame/resolvers/quad_resolver.hpp math/quad.hpp board/frame/resolvers/grid_resolver.cpp board/frame/resolvers/grid_resolver.hpp board/cell.cpp board/cell.hpp math/position.hpp)

message("${OpenCV_LIBS}")
target_link_libraries(rookie ${OpenCV_LIBS})
