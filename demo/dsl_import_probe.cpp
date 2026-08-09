#include <cstdio>
#include <string>

import eui.types;
import eui.dsl;

int main() {
    core::dsl::Ui ui;
    ui.rect("bg").size(100.0f, 100.0f).color(eui::Color{0.12f, 0.12f, 0.15f, 1.0f}).build();

    const core::dsl::Screen screen{800.0f, 600.0f};
    const core::dsl::ElementKind kind = core::dsl::ElementKind::Rect;
    const core::dsl::LoaderMode mode = core::dsl::LoaderMode::KeepAlive;
    const std::string heart = core::dsl::utf8(0x2665);

    core::dsl::AnimProperty anim = core::dsl::AnimProperty::All;
    core::dsl::Ease ease = core::dsl::Ease::OutCubic;
    core::dsl::Transition transition = core::dsl::Transition::make(0.2f);
    core::dsl::HitTestMode hit = core::dsl::HitTestMode::Transformed;
    core::dsl::DragEvent drag;
    core::dsl::Element el;
    core::dsl::LoaderBuilder lb = ui.loader("ldr");
    core::dsl::StateStore store;
    core::dsl::LayoutBuilder row = ui.row("row");
    core::dsl::RectBuilder rect = ui.rect("rect");
    core::dsl::ShadertoyBuilder st = ui.shadertoy("st");
    core::dsl::PolygonBuilder poly = ui.polygon("poly");
    core::dsl::TextBuilder text = ui.text("text");
    core::dsl::ImageBuilder img = ui.image("img");
    core::dsl::SvgBuilder svg = ui.svg("svg");

    core::dsl::Runtime* runtime = nullptr;
    (void)runtime;
    core::dsl::BuilderBase<core::dsl::LayoutBuilder>* bb = nullptr;
    core::dsl::ShapeBuilderBase<core::dsl::RectBuilder>* sb = nullptr;
    (void)bb;
    (void)sb;

    if (screen.width != 800.0f || screen.height != 600.0f) return 1;
    if (kind != core::dsl::ElementKind::Rect) return 1;
    if (mode != core::dsl::LoaderMode::KeepAlive) return 1;
    if (heart != "\xE2\x99\xA5") return 1;
    if (anim != core::dsl::AnimProperty::All) return 1;
    if (ease != core::dsl::Ease::OutCubic) return 1;
    if (!transition.enabled) return 1;
    if (hit != core::dsl::HitTestMode::Transformed) return 1;
    (void)drag;
    (void)el;
    (void)lb;
    (void)store;
    (void)row;
    (void)rect;
    (void)st;
    (void)poly;
    (void)text;
    (void)img;
    (void)svg;

    std::puts("PASS: eui.dsl pure import probe (import-only, no engine/dsl includes)");
    return 0;
}
