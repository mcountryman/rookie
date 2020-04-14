cmake_minimum_required(VERSION 3.16)
project(rookie)

set(CMAKE_CXX_STANDARD 20)

if (EXISTS "${PROJECT_SOURCE_DIR}/thirdparty/opencv")
  message("Using local opencv directory")
  set(OpenCV_DIR thirdparty/opencv/build/x64/vc15/lib)
endif ()

find_package(OpenCV REQUIRED)
include_directories(
  src/math
  src/utils
  src/board
  thirdparty
  ${OpenCV_INCLUDE_DIRS}
)

add_executable(
  rookie
  src/main.cpp
  src/math/line.hpp
  src/math/quad.hpp
  src/math/point.hpp
  src/math/position.hpp
  src/math/triangle.hpp
  src/math/line_segment.hpp
  src/board/board.cpp
  src/board/board.hpp
  src/board/cell.cpp
  src/board/cell.hpp
  src/board/frame/frame.cpp
  src/board/frame/frame.hpp
  src/board/frame/frame_resolver.cpp
  src/board/frame/frame_resolver.hpp
  src/board/frame/resolvers/quad_resolver.cpp
  src/board/frame/resolvers/quad_resolver.hpp
  src/board/frame/resolvers/grid_resolver.cpp
  src/board/frame/resolvers/grid_resolver.hpp
  src/board/frame/resolvers/line_resolver.cpp
  src/board/frame/resolvers/line_resolver.hpp
  src/board/frame/resolvers/point_resolver.cpp
  src/board/frame/resolvers/point_resolver.hpp
  src/board/frame/resolvers/triangle_resolver.cpp
  src/board/frame/resolvers/triangle_resolver.hpp
  src/utils/format.cpp
  src/utils/format.hpp
  thirdparty/delaunator.hpp
)

add_library(
  librookie SHARED
  src/math/line.hpp
  src/math/quad.hpp
  src/math/point.hpp
  src/math/position.hpp
  src/math/triangle.hpp
  src/math/line_segment.hpp
  src/board/board.cpp
  src/board/board.hpp
  src/board/cell.cpp
  src/board/cell.hpp
  src/board/frame/frame.cpp
  src/board/frame/frame.hpp
  src/board/frame/frame_resolver.cpp
  src/board/frame/frame_resolver.hpp
  src/board/frame/resolvers/quad_resolver.cpp
  src/board/frame/resolvers/quad_resolver.hpp
  src/board/frame/resolvers/grid_resolver.cpp
  src/board/frame/resolvers/grid_resolver.hpp
  src/board/frame/resolvers/line_resolver.cpp
  src/board/frame/resolvers/line_resolver.hpp
  src/board/frame/resolvers/point_resolver.cpp
  src/board/frame/resolvers/point_resolver.hpp
  src/board/frame/resolvers/triangle_resolver.cpp
  src/board/frame/resolvers/triangle_resolver.hpp
  src/utils/format.cpp
  src/utils/format.hpp
  thirdparty/delaunator.hpp
)

message("${OpenCV_LIBS}")
target_link_libraries(rookie ${OpenCV_LIBS})
