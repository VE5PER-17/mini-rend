#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

int main() {
    // 初始化 GLFW(窗口库)
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return 1;
    }

    // 创建一个 800x600 的窗口,标题 "mini-rend"
    GLFWwindow* window = glfwCreateWindow(800, 600, "mini-rend", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    // 用一下 glm,验证它链接上了(算两个向量的点积)
    glm::vec3 a(1.0f, 2.0f, 3.0f);
    glm::vec3 b(4.0f, 5.0f, 6.0f);
    float dot = glm::dot(a, b);
    std::cout << "glm dot product: " << dot << "\n";

    // 主循环:窗口没关就一直转
    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);    //交换前后缓冲
        glfwPollEvents();           //处理键盘鼠标事件
    }

    // 清理
    glfwDestroyWindow(window); //顺序很重要
    glfwTerminate();
    return 0;
}
