cmake_minimum_required(VERSION 3.21.2)
project(vid_player)


add_subdirectory(video_player)


find_package(OpenCV REQUIRED)
target_link_libraries(player PUBLIC ${OpenCV_LIBS})
target_include_directories(player PUBLIC ${OpenCV_INCLUDE_DIRS})
