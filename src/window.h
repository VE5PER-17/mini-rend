#pragma once

#include <GLFW/glfw3.h>

// Window —— 用 RAII 包装 GLFW 窗口
//
// 核心思想(RAII):把资源的获取绑到构造函数,释放绑到析构函数。
// 对象一创建就开窗,一离开作用域就自动关窗,永远不会忘记清理。
//
// 注意:这个类管理的是"窗口",不管理"GLFW 库本身"。
// GLFW 的 init/terminate 由 main 负责,因为一个程序只 init 一次,
// 而窗口可能创建多个。职责要分清。
class Window {
public:
    // 构造:创建窗口。参数:宽、高、标题。
    // 用 explicit 防止编译器偷偷把别的东西隐式转成 Window。
    Window(int width, int height, const char* title);

    // 析构:销毁窗口。这是 RAII 的关键——对象死时自动调用。
    ~Window();

    // ---- 禁用拷贝(三/五法则:管理资源的类要管好拷贝)----
    // 如果允许拷贝,两个 Window 对象会指向同一个 GLFWwindow*,
    // 析构时同一个窗口会被销毁两次 -> 崩溃。所以删掉拷贝构造和拷贝赋值。
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    // 判断窗口是否创建成功(构造可能失败,比如显示模式不支持)
    bool isValid() const;

    // 窗口是否应该关闭(用户点了关闭按钮)
    bool shouldClose() const;

    // 交换前后缓冲(把渲染好的画面显示到屏幕)
    void swapBuffers();

    // 处理待处理的输入事件(键盘、鼠标)
    void pollEvents();

    // 获取底层 GLFW 句柄(以后渲染代码要用,先用 const 暴露)
    GLFWwindow* handle() const { return window_; }

private:
    GLFWwindow* window_ = nullptr;  // 不透明句柄(号码牌!)
};

// GLFW 库的 RAII 包装:构造时 init,析构时 terminate。
// 放在 main 作用域里,保证程序退出时一定 terminate。
class GlfwContext {
public:
    GlfwContext();   // 调 glfwInit
    ~GlfwContext();  // 调 glfwTerminate
    GlfwContext(const GlfwContext&) = delete;
    GlfwContext& operator=(const GlfwContext&) = delete;
    bool isValid() const { return valid_; }
private:
    bool valid_ = false;
};
