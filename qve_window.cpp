//
// Created by qvx on 27.10.2024.
//

#include <stdexcept>
#include "qve_window.h"

namespace qve {

    QveWindow::QveWindow(int w, int h, std::string name) : width{w}, height{h}, windowName{name}{
        initWindow();
    }
    QveWindow::~QveWindow() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void QveWindow::initWindow() {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(width,height,windowName.c_str(), nullptr, nullptr);
    }

    void QveWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface) {
        if(glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS){
            throw std::runtime_error("Failed to create window surface");
        }
    }

}
