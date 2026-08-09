module;

#include <string>
#include <utility>
#include "core/dsl.h"
#include "core/dsl_runtime.h"

export module eui.app;

import eui.types;
import eui.dsl;
import eui.platform;

export namespace eui::app {

struct Fonts {
    std::string text;
    std::string icon;
};

struct AppConfig {
    std::string title = "App";
    std::string pageId = "app";
    eui::Color clearColor{0.16f, 0.18f, 0.20f, 1.0f};
    int windowWidth = 800;
    int windowHeight = 600;
    double fps = 90.0;
    Fonts fonts;
};

class App {
public:
    App() = default;
    ~App() = default;

    App(const App&) = delete;
    App& operator=(const App&) = delete;

    void configure(const AppConfig& config) {
        config_ = config;
    }

    bool initialize(eui::window::Handle window) {
        return runtime_.initialize(window);
    }

    template <typename ComposeFn>
    bool update(eui::window::Handle window, float dt,
                int drawW, int drawH, float dpi, float pointer,
                ComposeFn&& composeFn) {
        if (drawW <= 0 || drawH <= 0 || dpi <= 0.0f) {
            return false;
        }
        const float logicalWidth = static_cast<float>(drawW) / dpi;
        const float logicalHeight = static_cast<float>(drawH) / dpi;
        auto&& compose = composeFn;
        runtime_.compose(config_.pageId, logicalWidth, logicalHeight, compose);
        const bool painted = runtime_.update(window, dt, pointer, dpi);
        if (runtime_.composeRequested()) {
            runtime_.requestFullPaint();
            runtime_.compose(config_.pageId, logicalWidth, logicalHeight, compose);
            runtime_.update(window, 0.0f, pointer, dpi);
        }
        return painted || runtime_.composeRequested() || runtime_.isAnimating();
    }

    bool isAnimating() const {
        return runtime_.isAnimating();
    }

    void requestFullPaint() {
        runtime_.requestFullPaint();
    }

    void render(int w, int h, float dpi) {
        if (w <= 0 || h <= 0 || dpi <= 0.0f) {
            return;
        }
        runtime_.render(w, h, dpi, config_.clearColor);
    }

    void shutdown() {
        runtime_.shutdown();
    }

private:
    core::dsl::Runtime runtime_;
    AppConfig config_;
};

} // namespace eui::app
