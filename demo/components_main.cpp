#include <cstdio>

#include "core/dsl.h"
#include <string>
#include <vector>

import eui.types;
import eui.dsl;
import eui.components;

static void smoke(core::dsl::Ui& ui, const core::dsl::Screen& screen) {
    components::mouseArea(ui, "smoke.m")
        .size(120.0f, 60.0f)
        .onTap([] {})
        .onDrag([](const components::MouseDragEvent&) {})
        .onScroll([](const components::MouseScrollEvent&) {})
        .build();

    components::button(ui, "smoke.b")
        .text("Go")
        .style(components::ButtonStyle(components::theme::dark()))
        .onClick([] {})
        .build();

    components::checkbox(ui, "smoke.cb")
        .text("Enable")
        .checked(true)
        .build();

    components::input(ui, "smoke.in")
        .value("hello")
        .placeholder("type…")
        .build();

    components::scrollView(ui, "smoke.sv")
        .size(screen.width, screen.height)
        .content([](core::dsl::Ui& child, float, float) {
            child.text("sv.row").text("row").fontSize(14.0f).build();
        })
        .build();

    components::virtualList(ui, "smoke.vl")
        .size(300.0f, 200.0f)
        .itemCount(50)
        .rowHeight(36.0f)
        .row([](core::dsl::Ui& child, const std::string&, std::int64_t, float, float) {
            child.text("row").text("item").fontSize(14.0f).build();
        })
        .build();

    components::virtualMasonry(ui, "smoke.vm")
        .size(300.0f, 200.0f)
        .columns(2)
        .gap(8.0f)
        .itemCount(20)
        .itemHeight([](std::int64_t, float) { return 80.0f; })
        .item([](core::dsl::Ui& child, const std::string&, std::int64_t, float, float) {
            child.text("tile").text("t").fontSize(14.0f).build();
        })
        .build();

    components::dropdown(ui, "smoke.dd")
        .items({"A", "B", "C"})
        .selected(0)
        .build();

    components::progress(ui, "smoke.pg")
        .size(240.0f, 8.0f)
        .value(0.6f)
        .build();

    std::vector<components::workshop::CardSliderItem> items;
    items.push_back({"assets/x.png", "Title", "Subtitle", "Description"});
    components::workshop::cardSlider(ui, "smoke.cs")
        .items(items)
        .currentIndex(0)
        .autoPlay(false)
        .onChange([](int) {})
        .build();
}

int main() {
    components::theme::ThemeColorTokens tokens = components::theme::dark();
    components::theme::ThemeColorTokens light = components::theme::light();
    if (!tokens.dark) {
        std::puts("FAIL: dark() must set dark=true");
        return 1;
    }
    if (light.dark) {
        std::puts("FAIL: light() must set dark=false");
        return 1;
    }

    auto primary = tokens.primary;
    auto bg = tokens.background;
    (void)primary;
    (void)bg;

    core::dsl::Ui ui;
    ui.begin("p");
    const core::dsl::Screen screen{800.0f, 600.0f};
    smoke(ui, screen);
    ui.end();

    std::puts("PASS: eui.components module smoke (theme/mouseArea/button/checkbox/input/scrollView/virtualList/virtualMasonry/dropdown/progress/cardSlider surface)");
    return 0;
}
