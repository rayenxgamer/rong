cmake_minimum_required(VERSION 3.10)
include(FetchContent)

project(rong
  LANGUAGES C
)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/deps)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(rong
  src/main.c
  src/game/window.c
  src/input/input.c
  src/game/ball.c
  src/graphics/renderer.c
  src/graphics/shader.c
  src/graphics/buffer.c
  src/graphics/texture.c
  src/graphics/camera.c
  src/graphics/font/font.c
  src/graphics/atlas/atlas.c
  src/graphics/particlesystem/particle_emmiter.c
)
if(MSVC)
  #    target_compile_options(rong PUBLIC /Wall)
endif()

target_compile_options(rong PUBLIC -g)

find_package(glfw3 3.4 QUIET)
if (NOT glfw3_FOUND)
  FetchContent_Declare(
    glfw3
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.zip
  )
  FetchContent_GetProperties(glfw3)
  if(NOT glfw3_POPULATED)

  set(FETCHCONTENT_QUIET NO)
  #[[ you can toggle these to have either wayland or X11 support, useful for systems
  which were setup without one of them ]]
  if(LINUX)
    set(GLFW_BUILD_WAYLAND 0)
    set(GLFW_BUILD_X11 1)
  endif()

  FetchContent_MakeAvailable(glfw3)
  endif()
endif()

find_package(OpenGL REQUIRED)

FetchContent_Declare(
    glad
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/Dav1dde/glad/archive/refs/tags/v2.0.8.zip
)

FetchContent_GetProperties(glad)
if(NOT glad_POPULATED)
    set(FETCHCONTENT_QUIET NO)
    FetchContent_MakeAvailable(glad)

   add_subdirectory("${glad_SOURCE_DIR}/cmake" ${glad_BINARY_DIR})
    glad_add_library(glad REPRODUCIBLE EXCLUDE_FROM_ALL LOADER API gl:core=3.3)
endif()

if(WIN32)
    target_link_libraries(rong PUBLIC glad glfw)
else()
    target_link_libraries(rong PUBLIC glad glfw m)
endif()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
