#include "window.h"
#include "shader.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>

// 顶点数据:3 个顶点,每个 3 个 float(x,y,z),NDC 坐标,屏幕正中央
static const float vertices[] = {
    -0.5f, -0.5f, 0.0f,   // 左下
     0.5f, -0.5f, 0.0f,   // 右下
     0.0f,  0.5f, 0.0f    // 正上
};

int main() {
    GlfwContext ctx;
    if (!ctx.isValid()) return 1;

    Window window(800, 600, "mini-rend");
    if (!window.isValid()) return 1;

    // glad:加载所有 OpenGL 函数指针(必须在创建 OpenGL 上下文之后!)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return 1;
    }

    // 设置视口:OpenGL 画到窗口的哪个区域(这里整个窗口)
    glViewport(0, 0, 800, 600);

    // ---- 创建 VAO 和 VBO ----
    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    // 1. 绑定 VAO(接下来的规则都会记到这个 VAO)
    glBindVertexArray(vao);

    // 2. 绑定 VBO 并装数据
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 3. 设解读规则:0 号位置,每 3 个 float 一组,float 类型
    //    glVertexAttribPointer 隐式引用"当前绑定的 VBO"
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // ---- 加载着色器 ----
    Shader shader(SHADER_DIR "/vertex.glsl", SHADER_DIR "/fragment.glsl");
    if (!shader.isValid()) {
        std::cerr << "Failed to load shader\n";
        return 1;
    }

    // ---- 渲染循环 ----
    while (!window.shouldClose()) {
        // 清屏:用深灰色 (0.1, 0.1, 0.1) 清除颜色缓冲
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 画三角形
        shader.use();              // 激活着色器
        glBindVertexArray(vao);    // 绑定 VAO(含 VBO 数据 + 读法规则)
        glDrawArrays(GL_TRIANGLES, 0, 3);  // 画 3 个顶点组成的三角形

        window.swapBuffers();
        window.pollEvents();
    }

    // RAII:Window/GlfwContext/Shader 自动析构。
    // VBO/VAO 暂时手动删(下一步会用 RAII 包装)
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    return 0;
}
