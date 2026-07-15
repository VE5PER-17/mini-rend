#version 330 core

// 顶点着色器:逐顶点运行
// 输入:一个顶点的坐标(从 VAO 的 0 号位置读)
layout (location = 0) in vec3 aPos;

void main() {
    // gl_Position 是内置输出变量,表示顶点的最终位置
    // aPos 是 vec3,补成 vec4(齐次坐标,w=1.0 表示点是"位置"而非"方向")
    gl_Position = vec4(aPos, 1.0);
}
