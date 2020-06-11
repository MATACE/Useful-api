#
# For x64 compile, please use command
# cmake ..
#

cmake_minimum_required(VERSION 3.5)

set(GNU_FLAGS "-DCOM_X64 -g -W")
set(CMAKE_CXX_FLAGS "${GNU_FLAGS}")
set(CMAKE_C_FLAGS   "${GNU_FLAGS}")

# Add the other lib.
# include_directories(${CMAKE_CURRENT_LIST_DIR}/libs/x64/glog/include/)
# link_directories(${CMAKE_CURRENT_LIST_DIR}/libs/x64/glog/lib)

# Add the project head file.
include_directories(${PROJECT_SOURCE_DIR}/include/)
# Add the all file to the 
# set(coroutine_src
#     ${PROJECT_SOURCE_DIR}/src/coroutines/example_switch_coroutine.cpp)

# Add the build file to the static lib or share lib.
# add_library(switch_coroutine ${coroutine_src})

# set_property(TARGET switch_coroutine PROPERTY CXX_STANDARD 11)
# set_property(TARGET switch_coroutine PROPERTY CXX_STANDARD_REQUIRED ON)

add_executable(md5_app
    ${PROJECT_SOURCE_DIR}/src/md5.cpp
    ${PROJECT_SOURCE_DIR}/src/main.cpp
)

set_property(TARGET md5_app PROPERTY CXX_STANDARD 11)
set_property(TARGET md5_app PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(md5_app)