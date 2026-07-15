# 进度跟踪

> **跨设备接力文件。** 每次会话结束更新本文件,记录当前进度和下一步。
> 新设备上 Claude 读这个文件就知道接着干什么。

## 里程碑清单

- [ ] **里程碑 1:** C++ 热身 + OpenGL 第一个三角形
  - [ ] 搭工具链(CMake + vcpkg + 编译器 + GLFW + glm)
  - [ ] 窗口程序(练 RAII / 智能指针)
  - [ ] 顶点 + 片段着色器(学管线概念)
  - [ ] 画出三角形(练指针 / 引用传顶点数据)
- [ ] **里程碑 2:** 3D 立方体 + 摄像机移动
  - [ ] 深度测试 + 旋转立方体
  - [ ] WASD + 鼠标第一人称摄像机
  - [ ] 值语义坑:矩阵传值 vs 传引用
- [ ] **里程碑 3:** Vulkan 第一个三角形
  - [ ] 实例 + 物理设备 + 逻辑设备 + 队列
  - [ ] 交换链
  - [ ] 图像视图 + 渲染通道 + 帧缓冲
  - [ ] 图形管线
  - [ ] 命令缓冲 + 同步
  - [ ] 画三角形
- [ ] **里程碑 4:** 3D 场景 + 摄像机(Vulkan 版)
  - [ ] 顶点缓冲 + 索引缓冲
  - [ ] uniform buffer + 描述符
  - [ ] 纹理采样
  - [ ] 深度测试 + 第一人称摄像机
- [ ] **里程碑 5:** PBR 材质 + 基础光照
  - [ ] 方向光 + 漫反射 / 镜面
  - [ ] PBR(金属度-粗糙度,Cook-Torrance BRDF)
  - [ ] 多光源
  - [ ] ImGui 调试面板
- [ ] **里程碑 6:** Forward+ / 延迟渲染 + 阴影
  - [ ] 选路线(Forward+ vs 延迟)
  - [ ] 光源剔除
  - [ ] 阴影映射

## 当前状态

**当前里程碑:** 里程碑 1(C++ 热身 + OpenGL 第一个三角形)

**当前步骤:** 第三步 —— 画三角形(待用户验证画面)

**进度:** 工具链 + 冒烟测试 + RAII 窗口 + 第一个三角形代码完成。代码已编译零警告、运行不崩溃。**待用户肉眼确认窗口里出现橙色三角形**(命令行无法看图形输出)。开发机 B 仍未装工具链。

## 冒烟测试结果(2026-07-14 通过 ✅)

- 工程:CMakeLists.txt + src/main.cpp + CMakePresets.json + scripts/smoke_build.bat
- 编译器:MSVC 19.51(VS 2026 v18.0 自带)
- 生成器:Ninja(VS BuildTools 自带,路径见下"坑")
- 验证:窗口弹出 + `glm dot product: 32` 正确 + 零编译警告

## 开发机 A 环境关键事实(给下一个 Claude)

**重要:本机 VS 是 "Visual Studio 2026 v18.0"(不是 2022),内部版本号 18,装在 `C:\Program Files\Microsoft Visual Studio\18\Professional`。**

已知坑 + 解法:
1. **CMake 找不到 VS 实例** —— CMake 的 "Visual Studio 17 2022" 生成器对本机 VS 2026 失效(报 "could not find any instance of Visual Studio")。
   - 解法:用 **Ninja 生成器**,在激活 MSVC 环境后配置。见 `scripts/smoke_build.bat`。
2. **MSVC 环境激活** —— 命令行必须先调 vcvarsall,否则 cl.exe 不在 PATH:
   - `C:\Program Files\Microsoft Visual Studio\18\Professional\VC\Auxiliary\Build\vcvarsall.bat x64`
   - 注意:激活时会报 `'vswhere.exe' is not recognized`,但实际仍能成功初始化,无害。
3. **Ninja 位置** —— 不在 Professional 目录,在 BuildTools 目录:
   - `C:\Program Files (x86)\Microsoft Visual Studio\18\BuildTools\Common7\IDE\CommonExtensions\Microsoft\CMake\Ninja\ninja.exe`
   - 用前要把它加到 PATH(脚本里已做)。
4. **.bat 脚本不能用中文** —— 中文 Windows 的 cmd 用 GBK 解码,.bat 里写中文注释/echo 会让整个脚本解析崩溃。脚本一律纯英文。(见全局 CLAUDE.md 第 7 条)
5. **VS Code 红线(IntelliSense)** —— C/C++ 插件不知道 vcpkg 头文件路径。
   - 解法:CMakeLists.txt 开 `CMAKE_EXPORT_COMPILE_COMMANDS ON` 生成 `build/compile_commands.json`,在 `.vscode/c_cpp_properties.json` 里设 `"compileCommands"` 指向它 + `"configurationProvider": "ms-vscode.cmake-tools"`。
6. **`/EHsc` 必加** —— 用 `<iostream>` 等会触发 C++ 异常,MSVC 不加 `/EHsc` 会警告 C4530。已在 CMakeLists.txt 里加。

构建方法:在项目根目录跑 `scripts\smoke_build.bat`(纯英文,激活 MSVC + 配置 + 编译一条龙)。

## 工具链现状

### 开发机 A(本机,2026-07-13)— 工具链完整 ✅

已装:
- VS 2022 Professional(含 MSVC 编译器)
- VS Build Tools
- CMake 4.3.4
- Git 2.54.0
- vcpkg(`C:\dev\vcpkg`,版本 2026-05-27)
- GLFW 3.4(via vcpkg,glfw3:x64-windows)
- glm 1.0.3(via vcpkg,glm:x64-windows)
- VS Code 插件:C/C++、CMake Tools、CMake ✅

里程碑 3 才装:Vulkan SDK、RenderDoc

### 开发机 B(另一台 Windows)— 尚未开始

接手前必须先装好整套工具链(下一个 Claude 带用户做):
1. Visual Studio 2022(Community 免费版即可,装时勾选"使用 C++ 的桌面开发"工作负载)—— 提供 MSVC
2. CMake(cmake.org 下载,或 VS 安装器里勾选)
3. Git
4. vcpkg:`git clone https://github.com/microsoft/vcpkg.git C:\dev\vcpkg` → `cd C:\dev\vcpkg && .\bootstrap-vcpkg.bat`
5. 用 vcpkg 装库:`C:\dev\vcpkg\vcpkg.exe install glfw3 glm`
6. VS Code + 三个插件:C/C++、CMake Tools、CMake
7. clone 本仓库:`git clone git@github.com:VE5PER-17/mini-rend.git`(那台机器也要配 SSH 密钥,见 CLAUDE.md 跨设备机制)

> vcpkg 路径固定用 `C:\dev\vcpkg`,这样 CMake 配置里的 toolchain 路径两台机器一致,不用改代码。

## 下一步(细化)

**当前:** 里程碑 1 第二步 —— 窗口程序(练 RAII / 智能指针)

目标:把当前 main.cpp 里 C 风格的 GLFW 调用(glfwInit/glfwTerminate 手动配对)包装成 C++ 的 RAII 类,让资源清理自动发生。这是 Java→C++ 的核心心智模型转换点。

子步骤:
1. 讲 RAII 原理(构造函数获取资源,析构函数释放)—— 类比 Java try-finally / try-with-resources
2. 写一个 `Window` 类,构造时 glfwCreateWindow,析构时 glfwDestroyWindow + glfwTerminate
3. 练智能指针:用 unique_ptr 管理 Window 生命周期(虽然这里栈对象就够,但学概念)
4. 验证:窗口仍能弹、关窗正常退出、无内存泄漏(概念上)

**之后:** 里程碑 1 第三步 —— 顶点 + 片段着色器(学管线概念),然后画三角形。

## 卡点 / 待决问题

(无)

## 会话记录

- 2026-07-13(会话 1):确定项目方向(C++ + Vulkan,OpenGL 过渡),确立工作流与严格验证标准,搭好项目骨架并推送到 GitHub。确认技术栈:VS Code + MSVC,NVIDIA GPU,双 Windows 跨设备,理论中等深度。
- 2026-07-13(会话 1):装好开发机 A 工具链(vcpkg + GLFW 3.4 + glm 1.0.3 + VS Code 插件)。下一步冒烟测试。开发机 B 待装。
- 2026-07-14(会话 2):冒烟测试通过。写 CMakeLists/main.cpp/CMakePresets,踩过 VS 2026 生成器坑、.bat 中文编码坑,用 Ninja+vcvars 解决。compile_commands.json 解决 VS Code 红线。关键事实已记入上方"开发机 A 环境关键事实"。下一步:RAII 包装窗口。
- 2026-07-14(会话 2 续):RAII 包装窗口完成(Window + GlfwContext 类,禁拷贝,nullptr 防垃圾值+垂悬指针,栈对象优先)。学到栈展开/析构必调/析构逆序/三五法则。CLAUDE.md 加代码约定。用户纠正"每步都要更新 NOTES+PROGRESS+README",已补 NOTES.md(沉淀工具链/C++/RAII/管线笔记)并写进 CLAUDE.md 工作流。下一步:里程碑 1 第三步,画三角形(渲染管线)。
