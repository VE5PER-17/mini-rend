cmake_minimum_required(VERSION 3.20)

# 导出 compile_commands.json,供 VS Code IntelliSense 使用(消除编辑器红线)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(mini-rend LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---- 依赖 ----
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

# ---- 可执行文件 ----
add_executable(mini-rend
    src/main.cpp
    src/window.cpp
    src/shader.cpp
)

target_link_libraries(mini-rend PRIVATE glfw glm::glm glad::glad)

# 着色器文件要能被 exe 找到:把 shaders/ 目录的路径传给代码
target_compile_definitions(mini-rend PRIVATE SHADER_DIR="${CMAKE_SOURCE_DIR}/shaders")

# MSVC: 用 UTF-8 源码编码,避免中文注释导致编译警告/错误;/EHsc 启用 C++ 异常展开
if(MSVC)
    target_compile_options(mini-rend PRIVATE /utf-8 /W4 /EHsc)
endif()
