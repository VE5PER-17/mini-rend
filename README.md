# mini-rend

一个以**学习现代引擎渲染技术**为目的的 3D 渲染引擎。追求高质量与高性能。

## 目标

学习并实现现代渲染引擎的核心技术:PBR 材质、光照、Forward+ / 延迟渲染、阴影。
范围严格限定在渲染 + 最基本的场景创建和摄像机移动。

## 技术栈

- **语言:** C++(17/20)
- **图形 API:** Vulkan(用 OpenGL 作为起步过渡,降低入门门槛)
- **编译器 / 编辑器:** MSVC(VS 2022)/ VS Code + CMake Tools
- **构建:** CMake + vcpkg
- **数学 / 窗口:** glm / GLFW
- **调试:** Vulkan 验证层 + RenderDoc

## 路线图

1. C++ 热身 + OpenGL 第一个三角形
2. 3D 立方体 + 摄像机移动
3. Vulkan 第一个三角形
4. 3D 场景 + 摄像机(Vulkan 版)
5. PBR 材质 + 基础光照
6. Forward+ / 延迟渲染 + 阴影

详见 [PROGRESS.md](PROGRESS.md)。

## 当前进度

**里程碑 1 · OpenGL 第一个三角形** — ✅ 第一个三角形成功渲染!整条 OpenGL 渲染管线跑通。开发机 B 待装工具链。
**下一步:** 配 OpenGL 错误检查(验证层等价物)+ VBO/VAO 的 RAII 包装,收尾里程碑 1。

> _更新于 2026-07-14。每次同步进度时本段会随之刷新,详细进度见 [PROGRESS.md](PROGRESS.md)。_

## 给协作者的说明

- 读 [CLAUDE.md](CLAUDE.md) 了解项目目标、工作流和约定
- 读 [PROGRESS.md](PROGRESS.md) 了解当前进度和下一步
- 学习笔记在 [NOTES.md](NOTES.md)
