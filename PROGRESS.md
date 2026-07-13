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

**当前步骤:** 搭工具链 —— 手动逐个装,每装一个验证一个

**进度:** 工具链在开发机 A 已装完;开发机 B(另一台 Windows)尚未装。下一步是冒烟测试。

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

**当前:** 做整条工具链的冒烟测试(在开发机 A 上)

**冒烟测试:** 写一个最小 CMake 工程,用 MSVC 编译,链接 GLFW + glm,跑出一个窗口。
验证:VS Code → CMake → MSVC → vcpkg 库 整条链路都通,地基扎实再写渲染代码。

**冒烟测试要点(给下一个 Claude):**
- CMake 配置要用 vcpkg toolchain 文件:`C:\dev\vcpkg\scripts\buildsystems\vcpkg.cmake`
- 在 CMakeLists.txt 里:`find_package(glfw3 CONFIG REQUIRED)` + `target_link_libraries(... PRIVATE glfw)`
- glm:`find_package(glm CONFIG REQUIRED)` + `target_link_libraries(... PRIVATE glm::glm)`
- 用 MSVC 编译器(x64),CMake Tools 插件会自动检测
- 验收:能弹出 GLFW 窗口,关闭窗口正常退出,无编译警告/错误

**通过后:** 进入里程碑 1 第二步 —— 窗口程序(练 RAII / 智能指针),再学管线概念画三角形。

## 卡点 / 待决问题

(无)

## 会话记录

- 2026-07-13(会话 1):确定项目方向(C++ + Vulkan,OpenGL 过渡),确立工作流与严格验证标准,搭好项目骨架并推送到 GitHub。确认技术栈:VS Code + MSVC,NVIDIA GPU,双 Windows 跨设备,理论中等深度。
- 2026-07-13(会话 1):装好开发机 A 工具链(vcpkg + GLFW 3.4 + glm 1.0.3 + VS Code 插件)。下一步冒烟测试。开发机 B 待装。
