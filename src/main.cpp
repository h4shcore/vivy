#include "app.hpp"
#include <iostream>
#include <string_view>

constexpr std::string_view VERSION = "1.0.0";

void printUsage(std::string_view progName) {
    std::cout << "vivy v" << VERSION << " - Fast, minimalist GPU image viewer\n\n"
              << "Usage:\n"
              << "  " << progName << " <image_path>\n"
              << "  " << progName << " [options]\n\n"
              << "Options:\n"
              << "  -h, --help     Show this help message and exit\n"
              << "  -v, --version  Display version information\n\n"
              << "Controls:\n"
              << "  Scroll Wheel      Zoom in / out relative to cursor\n"
              << "  Left Click + Drag Pan image\n"
              << "  r                 Reset zoom & position\n"
              << "  f                 Toggle fullscreen\n"
              << "  q / Esc           Exit\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage(argv[0]);
        return 0;
    }

    std::string_view arg = argv[1];

    if (arg == "-h" || arg == "--help") {
        printUsage(argv[0]);
        return 0;
    }

    if (arg == "-v" || arg == "--version") {
        std::cout << "vivy v" << VERSION << "\n";
        return 0;
    }

    std::string imagePath = argv[1];

    App app(imagePath);
    if (!app.init()) {
        std::cerr << "Initialization failed.\n";
        return 1;
    }

    app.run();
    return 0;
}
