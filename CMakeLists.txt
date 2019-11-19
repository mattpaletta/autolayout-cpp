cmake_minimum_required(VERSION 3.15)

project(autolayout LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
	set(CMAKE_CXX_FLAGS         "-Wall -Wno-unknown-pragmas -Wno-sign-compare -Woverloaded-virtual -Wwrite-strings -Wno-unused")
	set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g3")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

add_library(autolayout src/rectangle.h src/view.h src/view.cpp src/size.h src/rectangle.h src/constraint.h src/point.h)
SET_TARGET_PROPERTIES(autolayout PROPERTIES LINKER_LANGUAGE CXX)

find_package(Catch2 CONFIG REQUIRED)

add_executable(test_autolayout app/test_autolayout.cpp)
target_link_libraries(test_autolayout autolayout Catch2::Catch2)
