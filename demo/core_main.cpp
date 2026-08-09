#include <cstdio>

#include "core/dsl.h"

import eui.core;

int main() {
    eui::Color accent{0.85f, 0.42f, 0.25f, 1.0f};
    (void)accent;

    eui::app::AppConfig config;
    config.title = "core-smoke";
    config.pageId = "core.smoke";
    config.clearColor = {0.10f, 0.11f, 0.13f, 1.0f};

    eui::app::App app;
    app.configure(config);

    core::dsl::Ui ui;
    ui.begin("p");
    const core::dsl::Screen screen{800.0f, 600.0f};

    components::mouseArea(ui, "core.m")
        .size(120.0f, 60.0f)
        .onTap([] {})
        .build();

    ui.end();

    std::puts("PASS: eui.core umbrella (import eui.core -> types/dsl/app/components in one TU)");
    return 0;
}
