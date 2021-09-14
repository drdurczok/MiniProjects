cmake_minimum_required(VERSION 3.1)
project(game)
# Enable C++11
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(GLEW_INC_DIRS /usr/include/GL)
set(GLEW_LIBS -lglfw -lGLEW -lGLU -lGL)

# dependencies
# find_package(GLEW REQUIRED)

# provide library headers
include_directories(${GLEW_INC_DIRS})
add_executable(game ../src/main.cpp)

# link OpenCV libraries
target_link_libraries(game ${GLEW_LIBS})

# display opencv libs found
MESSAGE("OpenGL_LIBS: " ${GLEW_INC_DIRS})
