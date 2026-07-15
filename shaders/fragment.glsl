#version 330 core

// 片段着色器:逐像素运行(更准确:逐片段)
// 输出:这个像素的颜色
out vec4 FragColor;

void main() {
    // 所有像素都输出橙色:R=1.0(满红) G=0.5(半绿) B=0.2(少许蓝) A=1.0(不透明)
    FragColor = vec4(1.0, 0.5, 0.2, 1.0);
}
