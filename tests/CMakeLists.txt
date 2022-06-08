cmake_minimum_required(VERSION 3.21)
project(tests VERSION 1.0.0)
enable_language(CUDA)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${TEGRA_MULTIMEDIA_API_INCLUDE_DIR}
	${CUDA_INCLUDE_DIRS}
	${JETSON_IMAGER_DIR}/imaging/include
	${JETSON_IMAGER_DIR}/utils/include
)

# add all source files
FILE(GLOB SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} imaging utils)