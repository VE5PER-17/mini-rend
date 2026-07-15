#pragma once

#include <glad/glad.h>
#include <string>

// Shader —— 管理一个 OpenGL 着色器程序(顶点+片段着色器链接后的整体)
//
// RAII:构造时编译+链接着色器,析构时删除程序。
// 用法:Shader shader("path/vertex.glsl", "path/fragment.glsl");
//       shader.use();  // 激活这个着色器程序
//
// 着色器源码从文件读,运行时编译成 GPU 机器码。
class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    // 激活这个着色器程序(后续 draw call 用它)
    void use() const;

    // 着色器是否编译链接成功
    bool isValid() const { return program_ != 0; }

    GLuint program() const { return program_; }

private:
    GLuint program_ = 0;  // OpenGL 程序对象的句柄(号码牌)
};
