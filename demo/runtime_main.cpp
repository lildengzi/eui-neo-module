#include <cassert>
#include <cstdio>
#include "core/window/window_backend.h"

import eui.types;
import eui.dsl;

int main() {
    core::dsl::Runtime rt;

    core::window::Handle window = nullptr;
    {
        core::window::WindowCreateRequest req{};
        req.width = 320;
        req.height = 240;
        req.title = "runtime-smoke";
        window = core::window::createWindow(req);
    }

    const bool initialized = window != nullptr ? rt.initialize(window) : rt.initialize();
    assert(initialized);

    rt.compose("runtime.smoke", 800.0f, 600.0f,
        [](core::dsl::Ui& ui, const core::dsl::Screen& screen) {
            ui.rect("bg").size(screen.width, screen.height)
              .color({0.12f, 0.12f, 0.15f, 1.0f}).build();
            ui.rect("accent").size(320.0f, 48.0f)
              .color({0.85f, 0.42f, 0.25f, 1.0f}).radius(8.0f).build();
        });
    assert(rt.paintRequested());

    if (window != nullptr) {
        rt.update(window, 0.016f, 1.0f, 1.0f, false);
        rt.update(window, 0.016f, 1.0f, 1.0f, false);
        assert(!rt.isAnimating());
    }

    rt.requestFullPaint();
    assert(rt.paintRequested());

    rt.shutdown();

    if (window != nullptr) {
        core::window::destroyWindow(window);
    }

    std::puts("PASS: eui.dsl Runtime smoke (initialize/compose/update/shutdown)");
    return 0;
}
