cmake_minimum_required(VERSION 3.21)
# Set the project name
project(tests VERSION 1.0.0)
add_subdirectory(tests)
add_subdirectory(${JETSON_IMAGER_DIR}/imaging)
add_subdirectory(${JETSON_IMAGER_DIR}/utils)