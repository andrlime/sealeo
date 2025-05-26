cmake_minimum_required(VERSION 3.20)

project(
	SEALEO
	VERSION 0.1
	DESCRIPTION "A modern C++ clone of Goroutines and Channels in Go"
	LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "-O3 -march=native -flto")
message(STATUS "CMAKE_CXX_STANDARD = ${CMAKE_CXX_STANDARD}")
message(STATUS "CMAKE_CXX_COMPILER = ${CMAKE_CXX_COMPILER}")
message(STATUS "CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}")


# -- Dependencies --

# -- Add files to object library --
file(GLOB_RECURSE SEALEO_OBJ_SOURCES "src/*.cc")
list(FILTER SEALEO_OBJ_SOURCES EXCLUDE REGEX ".*/main\\.cc$")
add_library(
	SEALEO_obj OBJECT
	${SEALEO_OBJ_SOURCES}
)
target_include_directories(SEALEO_obj PRIVATE "./src/include")


# -- Link library and dependencies --
# none for now

# -- Create executable --
add_executable(SEALEO_exe src/main.cc)
set_property(TARGET SEALEO_exe PROPERTY OUTPUT_NAME sealeo)
target_include_directories(SEALEO_exe PRIVATE "./src/include")
target_compile_features(SEALEO_exe PRIVATE cxx_std_${CMAKE_CXX_STANDARD})

# -- Link object library and dependencies --
target_link_libraries(SEALEO_exe PRIVATE SEALEO_obj)

