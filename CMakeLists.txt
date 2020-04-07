cmake_minimum_required(VERSION 3.16)
project(rookie)

set(CMAKE_CXX_STANDARD 20)

if(EXISTS "${PROJECT_SOURCE_DIR}/thirdparty/opencv")
  message("Using local opencv directory")
  set(OpenCV_DIR thirdparty/opencv/build/x64/vc15/lib)
endif()

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(
    rookie
    main.cpp
    math/line.cpp
    math/line.hpp
    math/vector.cpp
    math/vector.hpp
    math/segment.cpp
    math/segment.hpp
    math/constants.hpp
    board/board.cpp
    board/board.hpp
    board/frame/frame.cpp
    board/frame/frame.hpp
    board/frame/frame_resolver.cpp
    board/frame/frame_resolver.hpp
    board/frame/resolvers/line_resolver.cpp
    board/frame/resolvers/line_resolver.hpp)

target_link_libraries(rookie ${OpenCV_LIBS})
