# mini-rend — 项目指令

本文件是给 Claude(a helpful coding assistant)读的项目指令,每次会话开始时自动加载。
跨设备协作时,这是新设备上 Claude 了解项目的第一份文件。

## 项目目标

构建一个 3D 渲染引擎,**以学习现代引擎渲染技术为目的**,追求高质量与高性能。

## 范围(严格边界)

**只做渲染。** 不做以下任何一项:
- 物理、碰撞
- 音频
- 网络
- 游戏逻辑、脚本系统
- UI 框架(除调试用的 ImGui 面板外)
- 资源管线 / 资产打包(用最简方式加载即可)

**必需的最小非渲染功能:**
- 场景创建(能放几个物体)
- 第一人称摄像机移动(WASD + 鼠标视角)

任何超出上述范围的请求,先和用户确认,不要自行扩展。

## 技术栈

| 项 | 选择 | 理由 |
|---|---|---|
| 语言 | C++(现代,17/20) | 引擎主流语言,贴近硬件 |
| 主图形 API | Vulkan | 现代显式 API,跨平台,验证层强 |
| 起步过渡 API | OpenGL | 样板少(~200 行画三角形),用来练 C++ 和学管线概念,再转 Vulkan |
| 数学库 | glm | 图形标准库 |
| 窗口库 | GLFW | 轻量跨平台 |
| 构建系统 | CMake + vcpkg | C++ 事实标准 |
| 调试 | Vulkan 验证层 + RenderDoc | 见下"调试工具" |
| 编辑器 | VS Code + CMake Tools 插件 | 轻、适合逐行读代码的工作流 |
| 编译器 | MSVC(VS 2022 自带) | Windows 上 Vulkan 生态支持最好 |

**用户开发机:** NVIDIA GeForce/RTX(Vulkan 支持最好,RenderDoc 兼容)。
**跨设备:** 另一台也是 Windows,工具链完全一致,无平台障碍。

**已装工具(本机,2026-07-14 检测):**
- Visual Studio 2026 v18.0 Professional(`C:\Program Files\Microsoft Visual Studio\18\Professional`)—— 含 MSVC 19.51
- VS Build Tools(`C:\Program Files (x86)\Microsoft Visual Studio\18\BuildTools`,自带 Ninja)
- CMake 4.3.4
- Git 2.54.0
- vcpkg(`C:\dev\vcpkg`,版本 2026-05-27)+ GLFW 3.4 + glm 1.0.3
- VS Code 插件:C/C++、CMake Tools、CMake
- 未装:Vulkan SDK、RenderDoc(里程碑 3 装)

**⚠️ 本机环境关键事实(新设备 Claude 必读,详见 PROGRESS.md):**
- 本机 VS 是 **2026 v18.0**(不是 2022)。CMake 的 "Visual Studio 17 2022" 生成器对本机失效,必须用 **Ninja 生成器**。
- 命令行编译必须先激活 MSVC:`C:\Program Files\Microsoft Visual Studio\18\Professional\VC\Auxiliary\Build\vcvarsall.bat x64`(激活时报 `'vswhere.exe' is not recognized` 是正常的,不影响)。
- 一键构建脚本:`scripts\smoke_build.bat`(纯英文,因中文 Windows 的 cmd 用 GBK,.bat 含中文会让脚本解析崩溃——全局 CLAUDE.md 第 7 条)。
- 构建方式:`scripts\smoke_build.bat`(激活 MSVC + Ninja + 配置 + 编译)

**理论深度:中等。** 用户会自己补充原理,Claude 在相关步骤提示"这里需要补 XX 原理"即可,不展开推导。

**用户背景:** 有 Java 基础,C++ 几乎新学,图形新手。重点防 Java→C++ 的心智模型坑:指针 / 手动内存、栈 vs 堆 / RAII、未定义行为、值语义。

## 工作流约定(最重要)

### 代码约定(C++ 风格,所有代码遵守)

- **RAII 优先:** 所有资源(GLFW 窗口、以后 Vulkan 的 device/buffer 等)用类包装,构造获取、析构释放。不用手动配对的 init/destroy。
- **栈对象优先,智能指针按需:** 能用栈对象就别堆。`unique_ptr` 留给"需要堆 / 共享 / 多态"的场景(Vulkan 资源里会自然出现)。这是防 Java→C++ 残留(Java 对象默认堆)。
- **指针成员一律类内初始化为 nullptr:** 防未初始化垃圾值。
- **析构后置 nullptr:** 防垂悬指针。
- **管理资源的类禁用拷贝:** `= delete` 拷贝构造 + 拷贝赋值(三/五法则)。
- **头文件 `#pragma once`**;声明放 .h,实现放 .cpp。
- **成员变量下划线后缀**(`window_`),区分局部变量。
- **const 成员函数:** 不改对象的成员函数加 const。
- **MSVC 编译选项:** `/utf-8`(中文注释不警告)+ `/W4`(高警告)+ `/EHsc`(C++ 异常)。已在 CMakeLists.txt 配好。

### 协作模式:手把手辅导

每个子步骤的节奏:
1. Claude 先讲原理(大白话 + 类比),用户确认懂了再写代码
2. Claude 给最小代码,**分小块,每块能独立编译**
3. 用户逐行读,用自己的话复述这段在干嘛——讲不出来说明没懂,停下问
4. 用户跑代码,贴验证层输出 + RenderDoc 截图给 Claude
5. 有 bug Claude 帮定位,没 bug 进下一步
6. 会话结束更新 PROGRESS.md

### 验证标准(严格)

每个里程碑必须三条全过才能进下一步:
1. 能运行
2. **Vulkan / OpenGL 验证层零报错**
3. RenderDoc 检查过管线状态 / 资源绑定

不达标绝不开始下一个里程碑。图形 bug 80% 是地基没打牢的连锁反应。

### 防止 AI 生成错误代码的硬规则

- 代码里若出现 `// TODO: 关闭验证层` 之类注释,立即喊停
- 不一次写完整个子系统(如"把光照全写了")——拆成最小可验证单元
- 每个里程碑不达标,绝不开始下一个
- 每次提交只做一件事,小步提交,便于二分定位

## 调试工具用法

### Vulkan 验证层
- 默认开启(`VK_LAYER_KHRONOS_validation`)
- 任何报错必须清零,不允许"先忽略"
- 启用方式:实例创建时 `enabledLayerCount` 包含验证层,或用 `VK_INSTANCE_LAYERS` 环境变量

### RenderDoc
- 图形调试"显微镜":逐帧抓图,看每个 draw call 的管线状态、绑定的资源、纹理内容
- 抓 Vulkan 应用:启动 RenderDoc → 配置可执行文件路径 → Launch
- 抓 OpenGL 应用:同样,但需在 RenderDoc 设置里启用 GL 注入

## 跨设备机制

用户会在另一台设备上用 a helpful coding assistant 继续。机制:
- **Claude 的记忆是设备本地的,不会自动同步。** 跨设备靠项目仓库里的文件。
- 三个"接力棒"文件(随代码同步):
  - `CLAUDE.md`(本文件)——项目目标、技术栈、工作流。每完成一个里程碑更新。
  - `PROGRESS.md`——里程碑清单 + 当前进度 + 下一步。**每次会话结束必须更新。**
  - `NOTES.md`——学习笔记,每个概念一段。
- 新设备流程:`git clone` → 装相同工具链 → 启动 Claude → Claude 读 CLAUDE.md + PROGRESS.md → 接着干

### README 更新约定

每次同步进度到 GitHub 时,**顺手更新 README.md 里的"当前进度"小节**。
- README 是仓库首页门面,给用户扫一眼看概览用,保持简短(几行即可)。
- 详细进度、子步骤、卡点都放 `PROGRESS.md`,不要堆进 README。
- 更新内容:当前里程碑 + 一句话进度 + 下一步。

## 里程碑路线图

详见 `PROGRESS.md`。概览:

1. **里程碑 1:** C++ 热身 + OpenGL 第一个三角形(练 C++ 难点 + 学管线概念)
2. **里程碑 2:** 3D 立方体 + 摄像机移动(MVP 矩阵,第一人称摄像机)
3. **里程碑 3:** Vulkan 第一个三角形(样板代码爆炸,验证层救场)
4. **里程碑 4:** 3D 场景 + 摄像机(Vulkan 版,顶点 / 索引 / uniform / 纹理 / 深度)
5. **里程碑 5:** PBR 材质 + 基础光照(高质量核心)
6. **里程碑 6:** Forward+ / 延迟渲染 + 阴影(现代核心)

每个里程碑验收:能运行 + 验证层零报错 + RenderDoc 检查过。
