cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0048 NEW)

project(helloworld VERSION 0.1)

find_package(wxWidgets COMPONENTS core base REQUIRED)

include("${wxWidgets_USE_FILE}")
set(SRC app.cpp frame.cpp)

add_executable(helloworld ${SRC})

target_link_libraries(helloworld
  ${wxWidgets_LIBRARIES}
  GL
  GLEW)
