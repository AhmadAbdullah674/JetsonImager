cmake_minimum_required(VERSION 3.21)

set (CMAKE_CXX_STANDARD 20)
link_libraries(stdc++fs)
#Building a debug or a release
if(RELEASE)
  set(CMAKE_BUILD_TYPE Release)
  set(CMAKE_CXX_FLAGS_RELEASE "-O3")
  message("Building with Optimizations")
else()
  set(CMAKE_BUILD_TYPE Debug) 
  set(CMAKE_CXX_FLAGS_DEBUG "-O0 -DDEBUG -Wall -Wno-unused-function -Wno-sign-compare -Wno-dev")
  message("${red}\nBuild with  Debugging${nc}\n")
endif()

# To show meteric, will do later
# set("-DSHOW_V4L2_DEVICE_CAPTURE_FPS -DSHOW_CAM_INPUT_FPS -DSHOW_CUDA_TIMING")
set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -arch=sm_53")

set(SYS_ROOT "/")

execute_process(COMMAND "cat" ${SYS_ROOT}sys/module/tegra_fuse/parameters/tegra_chip_id OUTPUT_VARIABLE JETSON_ID)
if (${JETSON_ID} EQUAL "33")
	set(TEGRA_MULTIMEDIA_API_DIR "${SYS_ROOT}usr/src/jetson_multimedia_api")
else()
	message(FATAL_ERROR "Jetson Chip ID ${JETSON_ID} not supported")
endif()

set(CUDA_TOOLKIT_ROOT_DIR "/usr/local/cuda-10.2")
set(CMAKE_CUDA_COMPILER "${CUDA_TOOLKIT_ROOT_DIR}/bin/nvcc")
set(CUDA_CUDART_LIBRARY "${CUDA_TOOLKIT_ROOT_DIR}/targets/aarch64-linux/lib/libcudart.so")
find_package(CUDA REQUIRED)
enable_language(CUDA)

set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -Xcompiler --sysroot=${SYS_ROOT} -ccbin ${CMAKE_CXX_COMPILER}")
set(CMAKE_CUDA_IMPLICIT_LINK_DIRECTORIES /usr/local/cuda/targets/aarch64-linux/lib)

set(TEGRA_MULTIMEDIA_API_INCLUDE_DIR "${TEGRA_MULTIMEDIA_API_DIR}/include")

# Setting common Modules
set(JETSON_IMAGER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/modules")

# Linking
link_directories(${CMAKE_LIB_DIR}:${SYS_ROOT}usr/lib/aarch64-linux-gnu:${SYS_ROOT}usr/lib/aarch64-linux-gnu/tegra:${SYS_ROOT}lib/aarch64-linux-gnu;${SYS_ROOT}/usr/lib/aarch64-linux-gnu/tegra)
set(EXECUTABLE_OUTPUT_PATH bin)

if(APPS)
  include(cmakes/apps.cmake)
else()
  include(cmakes/tests.cmake)
endif()