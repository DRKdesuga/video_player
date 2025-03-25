cmake_minimum_required(VERSION 3.21.2)
project(vid_player)

add_executable(player)

target_include_directories(player PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(player PRIVATE ${PROJECT_SOURCE_DIR}/src)

add_subdirectory(src)
add_subdirectory(run)
