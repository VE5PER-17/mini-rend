#include "window.h"
#include <iostream>

// ============ GlfwContext ============

GlfwContext::GlfwContext() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return;
    }
    valid_ = true;
}

GlfwContext::~GlfwContext() {
    if (valid_) {
        glfwTerminate();
    }
}

// ============ Window ============

Window::Window(int width, int height, const char* title) {
    window_ = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window_) {
        std::cerr << "Failed to create GLFW window\n";
        return;  // window_ 保持 nullptr,isValid() 会返回 false
    }
    glfwMakeContextCurrent(window_);
}

Window::~Window() {
    if (window_) {
        glfwDestroyWindow(window_);
        window_ = nullptr;  // 防御性:析构后置空,避免悬垂指针
    }
}

bool Window::isValid() const {
    return window_ != nullptr;
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(window_) != 0;
}

void Window::swapBuffers() {
    glfwSwapBuffers(window_);
}

void Window::pollEvents() {
    glfwPollEvents();
}
