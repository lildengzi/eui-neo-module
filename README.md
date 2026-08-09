# eui-neo-module

EUI-NEO 的 C++23 模块化 fork。引擎层（`engine/`）保持 C++17 原样编译；`mod/` 为 C++23 模块层。

## 模块

| 模块 | 内容 |
|---|---|
| `eui.types` | 值类型：Color/Align/Rect/SizeValue/AnimProperty/Transition/Ease |
| `eui.dsl` | Ui/Element/Builder/Screen/StateStore + Runtime（含 `runtime_*` 实现） |
| `eui.platform` | opaque hosting bridge：createWindow/createRenderBackend/input 队列/timeSeconds |
| `eui.app` | `eui::app::App` 宿主驱动对象 + `AppConfig`（依赖倒置） |
| `eui.components` | Miuzy 用到的组件子集（mouseArea/cardSlider/button/checkbox/input/scrollView/virtualList/virtualMasonry/theme） |
| `eui.core` | umbrella re-export（不含 platform，platform 由 host 用） |

`import eui.core;` 单行即得全部公共 API。

## 使用

```cpp
import eui.core;   // 或窄 import: import eui.types; import eui.dsl;

void compose(::core::dsl::Ui& ui, const ::core::dsl::Screen& screen) {
    ui.rect("bg").size(screen.width, screen.height).color({0.1f,0.1f,0.1f,1}).build();
}
```

App 依赖倒置（替代上游全局 `app::dslAppConfig/compose`）：

```cpp
import eui.core;
eui::app::App app;
app.configure(cfg);
app.initialize(window);
// 每帧:
bool changed = app.update(window, dt, w, h, dpi, pointer,
                          [](::core::dsl::Ui& ui, const ::core::dsl::Screen& s){ compose(ui, s); });
if (changed || app.isAnimating()) { app.render(w, h, dpi); }
```

## 已知问题（clang 22 编译器 bug）

**症状**：纯 `import eui.dsl; import eui.components;`（或 `import eui.core;`）且**不带任何引擎/dsl 头 include** 的 TU 中实例化 `core::dsl::Ui` 时，clang 22.1.8 崩溃（exit 139，栈顶 `EmitBuiltinNewDeleteCall` / `std::__libcpp_allocate`）。

**根因**：`eui.dsl` 的 Ui/Element 定义在全局模块片段（GMF include `core/dsl.h`），经 `export namespace core::dsl { using X = ::core::dsl::X; }` 别名导出。`eui.components` 同样 GMF 引入 dsl.h 全局实体。消费者同时加载两个 PCM 时，clang 对"多模块 PCM 携带同一 GMF 全局实体 + 别名导出"的合并有 CodeGen bug。非我们代码的语义错误（代码加 include 兜底后完全正常）。

**规避（必需）**：消费 TU 中凡实例化/使用 `core::dsl::Ui`，请在全局模块片段保留一个文本 include 兜底：

```cpp
module;                     // 或普通 TU 顶部
#include <components/components.h>   // 内含 core/dsl.h，统一全局实体身份
// 或: #include <eui/dsl.h>
export module my.module;    // 或省略（普通 TU）
import eui.dsl;
import eui.components;
```

**影响面**：Miuzy_Way 每个用 Ui 的 TU 都已 include `<components/components.h>` 或引擎头，天然规避。fork 自带 demo 同理。仅"纯 import、零 include"的新消费者需注意。

**可选替代**：彻底把 Ui/Element 搬进模块可消除该 bug，但 Element 含引擎值类型（`core::render::ShaderToyGraph`）会违反"引擎类型不出现在导出签名"的硬规则，且破坏与经典头兼容。故维持现状。

## 构建

```bash
MCPP_INDEX_FLOOR=ignore ~/.mcpp/bin/mcpp build
MCPP_INDEX_FLOOR=ignore ~/.mcpp/bin/mcpp run app-smoke   # 真开窗（需 DISPLAY）
```

后端选择：`--features sdl2,vulkan,network`（sdl2 门控 `EUI_WINDOW_BACKEND_SDL2`）。

## 许可

Apache-2.0（引擎来自 EUI-NEO 0.5.5，上游 Apache-2.0）。
