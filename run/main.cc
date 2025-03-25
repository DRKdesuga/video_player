#include <iostream>
#include "video/video_player.hh"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cerr << "Only the path to your video is required" << std::endl;
        return 1;
    }
    std::string video_path(argv[1]);
    play_video(video_path);
    return 0;
}
