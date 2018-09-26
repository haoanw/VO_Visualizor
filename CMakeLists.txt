# project
cmake_minimum_required (VERSION 2.6)
project (vo_result_visualizor)

# package
find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)

# directories
set (TEST_SRC_DIR src)

# include directory
include_directories("${EIGEN3_INCLUDE_DIR}")

# use sse3 instruction set
SET(CMAKE_CXX_FLAGS "-msse3")

# sources
FILE(GLOB TEST_SRC_FILES "src/*.cpp")

# make release version
set(CMAKE_BUILD_TYPE Release)

# demo program
add_executable(demo ${TEST_SRC_FILES})
target_link_libraries(demo ${OpenCV_LIBS}
${EIGEN3_LIBS})
