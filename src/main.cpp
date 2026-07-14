#include "window.h"
#include <glm/glm.hpp>
#include <iostream>

int main() {
    // RAII:GlfwContext 构造时 init GLFW,离开作用域时自动 terminate。
    // 即使下面任何一步出错提前 return,GlfwContext 的析构也保证清理。
    GlfwContext ctx;
    if (!ctx.isValid()) {
        return 1;
    }

    // RAII:Window 构造时创建窗口,析构时自动销毁。
    // 不再需要手动配对 glfwCreateWindow / glfwDestroyWindow。
    Window window(800, 600, "mini-rend");
    if (!window.isValid()) {
        return 1;
    }

    // 验证 glm 链接(冒烟测试遗留,确认数学库可用)
    glm::vec3 a(1.0f, 2.0f, 3.0f);
    glm::vec3 b(4.0f, 5.0f, 6.0f);
    std::cout << "glm dot product: " << glm::dot(a, b) << "\n";

    // 主循环:窗口没关就一直转
    while (!window.shouldClose()) {
        window.swapBuffers();
        window.pollEvents();
    }

    // 不需要手动清理!Window 和 GlfwContext 离开作用域时自动析构。
    // 对比之前的版本:这里少了两行 glfwDestroyWindow + glfwTerminate。
    return 0;
}
