#---------------------------------------------------------------------------------------------------
# CMake Build Configuration for the Ray Tracing Weekend Series
#
# See README.md for guidance.
#---------------------------------------------------------------------------------------------------

cmake_minimum_required ( VERSION 3.1.0...3.27.0 )

project ( RTWeekend LANGUAGES CXX )

# Set to C++11
set ( CMAKE_CXX_STANDARD          11 )
set ( CMAKE_CXX_STANDARD_REQUIRED ON )
set ( CMAKE_CXX_EXTENSIONS        OFF )

# Source


set ( SOURCE_ONE_WEEKEND
  src/main.cc
  src/vec3.h
  src/color.h
  src/ray.h
  src/hittable.h
  src/sphere.h
  src/hittable_list.h
  src/rtweekend.h
)

# Executables
add_executable(inOneWeekend      ${EXTERNAL} ${SOURCE_ONE_WEEKEND})