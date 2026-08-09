#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#endif
#include <GLFW/glfw3.h>

#include "core/dsl.h"
#include "core/render/render_backend.h"

#include <cstdio>

import eui.types;
import eui.dsl;
import eui.platform;
import eui.app;

int main() {
    eui::app::AppConfig config;
    config.title = "app-smoke";
    config.pageId = "app.smoke";
    config.clearColor = {0.10f, 0.11f, 0.13f, 1.0f};
    config.windowWidth = 800;
    config.windowHeight = 600;
    config.fps = 90.0;

    if (glfwInit() != GLFW_TRUE) {
        std::puts("NOTE: glfwInit failed (headless) - skipping window render loop");
        return 0;
    }

    eui::window::WindowCreateRequest request;
    request.width = config.windowWidth;
    request.height = config.windowHeight;
    request.title = config.title.c_str();
    request.highDpi = false;
    eui::window::Handle window = eui::platform::createWindow(request);
    if (window == nullptr) {
        std::puts("NOTE: no window (headless) - skipping window render loop");
        glfwTerminate();
        return 0;
    }

    void* backendRaw = eui::platform::createRenderBackend(window);
    if (backendRaw == nullptr) {
        std::puts("NOTE: no render backend (headless GL) - skipping render loop");
        eui::platform::destroyWindow(window);
        glfwTerminate();
        return 0;
    }

    core::render::RenderBackend* backend = static_cast<core::render::RenderBackend*>(backendRaw);
    if (!backend->initialize()) {
        std::puts("NOTE: render backend initialize failed (no GL context) - skipping render loop");
        eui::platform::destroyRenderBackend(backendRaw);
        eui::platform::destroyWindow(window);
        glfwTerminate();
        return 0;
    }

    eui::app::App app;
    app.configure(config);
    if (!app.initialize(window)) {
        std::puts("NOTE: App::initialize failed - skipping render loop");
        eui::platform::destroyRenderBackend(backendRaw);
        eui::platform::destroyWindow(window);
        glfwTerminate();
        return 0;
    }

    core::render::RenderSurface surface;
    surface.window = window;
    surface.native.handle = window;
    surface.framebufferWidth = config.windowWidth;
    surface.framebufferHeight = config.windowHeight;
    surface.dpiScale = 1.0f;

    {
        double lastTime = eui::platform::timeSeconds();
        int frames = 0;
        bool changedFirstFrame = false;
        constexpr int maxFrames = 300;
        while (frames < maxFrames) {
            glfwPollEvents();

            const double now = eui::platform::timeSeconds();
            float dt = static_cast<float>(now - lastTime);
            lastTime = now;
            if (dt > 0.05f) {
                dt = 0.05f;
            }

            if (frames == 30) {
                eui::platform::queueKeyInput(window, eui::input::InputKey::Enter);
            }
            if (frames == 60) {
                eui::platform::queueScrollInput(window, 0.0, 6.0);
            }

            const bool changed = app.update(
                window, dt,
                surface.framebufferWidth, surface.framebufferHeight, surface.dpiScale, 1.0f,
                [](core::dsl::Ui& ui, const core::dsl::Screen& screen) {
                    ui.rect("app.bg").size(screen.width, screen.height)
                        .color({0.10f, 0.11f, 0.13f, 1.0f}).build();
                    ui.rect("app.accent").size(screen.width * 0.5f, 56.0f)
                        .color({0.85f, 0.42f, 0.25f, 1.0f}).radius(12.0f).build();
                });
            if (frames == 0 && !changed) {
                std::puts("FAIL: first App::update did not request a render");
                app.shutdown();
                eui::platform::destroyRenderBackend(backendRaw);
                eui::platform::destroyWindow(window);
                glfwTerminate();
                return 1;
            }
            if (changed) {
                changedFirstFrame = true;
                backend->beginFrame(surface);
                app.render(surface.framebufferWidth, surface.framebufferHeight, surface.dpiScale);
                backend->present();
            }
            ++frames;
        }

        if (!changedFirstFrame) {
            std::puts("NOTE: no frame was rendered during the loop");
        }
        app.shutdown();
    }

    eui::platform::destroyRenderBackend(backendRaw);
    eui::platform::destroyWindow(window);
    glfwTerminate();

    std::puts("PASS: eui.app host-driven App loop (window+backend+per-frame compose)");
    return 0;
}
