#include "video/video_player.hh"
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <string>


static std::string rgbToAnsiForeground(int r, int g, int b) {
    return "\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
}
static std::string rgbToAnsiBackground(int r, int g, int b) {
    return "\033[48;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
}


void play_video(const std::string& video_path, int cols, int rows)
{

    std::cout << "\033[2J\033[H";


    cv::VideoCapture video(video_path);
    if (!video.isOpened()) {
        std::cerr << "Issue in video Opening" << std::endl;
        return;
    }

    cv::Mat frame, resizedFrame;
    int targetWidth  = cols;
    int targetHeight = rows * 2;

    while (true) {
        video >> frame;
        if (frame.empty())
            break;


        cv::resize(frame, resizedFrame, cv::Size(targetWidth, targetHeight));

        std::ostringstream oss;
        oss << "\033[H";

        for (int i = 0; i < resizedFrame.rows; i += 2) {
            for (int j = 0; j < resizedFrame.cols; ++j) {
                auto topPixel    = resizedFrame.at<cv::Vec3b>(i, j);
                auto bottomPixel = (i + 1 < resizedFrame.rows)
                                   ? resizedFrame.at<cv::Vec3b>(i + 1, j)
                                   : topPixel;


                oss << rgbToAnsiForeground(topPixel[2], topPixel[1], topPixel[0])
                    << rgbToAnsiBackground(bottomPixel[2], bottomPixel[1], bottomPixel[0])
                    << "\u2580";
            }
            oss << "\033[0m\n";
        }


        std::cout << oss.str();
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }

    video.release();
    std::cout << "\033[0m" << std::endl;
}
