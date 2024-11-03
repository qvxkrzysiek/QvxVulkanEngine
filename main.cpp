#include "first_app.h"
#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main() {
    qve::FirstApp app{};

    try{
        app.run();
    } catch (const std::exception &exception) {
        std::cerr << exception.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
