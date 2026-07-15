#include "shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

// 辅助:从文件读全部内容到 string
static std::string readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        std::cerr << "ERROR: 无法打开着色器文件: " << path << "\n";
        return "";
    }
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

// 辅助:编译一个着色器(顶点或片段),返回着色器对象 ID。失败返回 0。
static GLuint compileShader(GLenum type, const std::string& source, const std::string& name) {
    GLuint shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    // 检查编译错误(着色器编译失败不会自动报错,必须主动查)
    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[1024];
        glGetShaderInfoLog(shader, sizeof(log), nullptr, log);
        std::cerr << "ERROR: 着色器编译失败 [" << name << "]:\n" << log << "\n";
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    std::string vSrc = readFile(vertexPath);
    std::string fSrc = readFile(fragmentPath);
    if (vSrc.empty() || fSrc.empty()) return;

    GLuint vs = compileShader(GL_VERTEX_SHADER, vSrc, vertexPath);
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fSrc, fragmentPath);
    if (!vs || !fs) {
        glDeleteShader(vs);
        glDeleteShader(fs);
        return;
    }

    // 链接:把顶点+片段着色器组装成一个"程序"
    program_ = glCreateProgram();
    glAttachShader(program_, vs);
    glAttachShader(program_, fs);
    glLinkProgram(program_);

    // 检查链接错误
    GLint success = 0;
    glGetProgramiv(program_, GL_LINK_STATUS, &success);
    if (!success) {
        char log[1024];
        glGetProgramInfoLog(program_, sizeof(log), nullptr, log);
        std::cerr << "ERROR: 着色器链接失败:\n" << log << "\n";
        glDeleteProgram(program_);
        program_ = 0;
    }

    // 着色器对象链接完后就没用了,删掉(程序已保留链接结果)
    glDeleteShader(vs);
    glDeleteShader(fs);
}

Shader::~Shader() {
    if (program_) {
        glDeleteProgram(program_);
        program_ = 0;
    }
}

void Shader::use() const {
    glUseProgram(program_);
}
