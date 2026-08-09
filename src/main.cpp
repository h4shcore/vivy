#include "app.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    std::string imagePath = (argc > 1) ? argv[1] : "";

    App app(imagePath);
    if (!app.init()) {
        std::cerr << "Initialization failed.\n";
        return 1;
    }

    app.run();
    return 0;
}
