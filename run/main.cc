#include "video/video_player.hh"
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sstream>
#include <string>


int getTerminalSize(int &cols, int &rows) {
    winsize w{};
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
        return -1;
    }
    cols = w.ws_col;
    rows = w.ws_row;
    return 0;
}


bool parseResolution(const std::string &arg, int &w, int &h) {
    std::size_t xPos = arg.find('x');
    if (xPos == std::string::npos) return false;
    try {
        w = std::stoi(arg.substr(0, xPos));
        h = std::stoi(arg.substr(xPos + 1));
    } catch (...) {
        return false;
    }
    return (w > 0 && h > 0);
}

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <video_path> [WIDTHxHEIGHT]" << std::endl;
        return 1;
    }
    std::string videoPath = argv[1];


    int maxCols = 0, maxRows = 0;
    if (getTerminalSize(maxCols, maxRows) != 0) {
        std::perror("ioctl");
        return 1;
    }
    std::cout << "Terminal maximum size: " << maxCols << " cols x " << maxRows << " rows\n";


    int cols = maxCols;
    int rows = maxRows;


    if (argc >= 3) {
        if (!parseResolution(argv[2], cols, rows)) {
            std::cerr << "Invalid resolution argument. Expected format WIDTHxHEIGHT (e.g., 80x24)." << std::endl;
            return 1;
        }
    } else {

        std::string input;
        std::cout << "Enter desired resolution (WIDTHxHEIGHT), or press Enter to use max: ";
        std::getline(std::cin, input);
        if (!input.empty()) {
            if (!parseResolution(input, cols, rows)) {
                std::cerr << "Invalid input. Using maximum resolution." << std::endl;
                cols = maxCols;
                rows = maxRows;
            }
        }
    }

    cols = std::min(cols, maxCols);
    rows = std::min(rows, maxRows);

    std::cout << "Using resolution: " << cols << " cols x " << rows << " rows\n";


    play_video(videoPath, cols, rows);
    return 0;
}