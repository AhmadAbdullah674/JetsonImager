cmake_minimum_required(VERSION 3.21)
project(utils VERSION 1.0.0)
enable_language(CUDA)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${TEGRA_MULTIMEDIA_API_INCLUDE_DIR}
	${CUDA_INCLUDE_DIRS}
)

FILE(GLOB SOURCES "src/*.cpp")
add_library(${PROJECT_NAME} SHARED ${SOURCES})
