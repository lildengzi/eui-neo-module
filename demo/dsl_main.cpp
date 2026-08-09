#include <cassert>
#include <cstdio>
#include <string>
#include "core/dsl.h"

import eui.types;
import eui.dsl;

static void smoke(core::dsl::Ui& ui, const core::dsl::Screen& s) {
    ui.rect("demo.bg").size(s.width, s.height).color({0.1f, 0.1f, 0.1f, 1.0f}).build();
    ui.row("header").size(320.0f, 64.0f).build();
    ui.column("page").size(320.0f, 480.0f).build();
    ui.stack("root").size(320.0f, 480.0f).build();
    ui.text("label").text("hi").fontSize(16.0f).color({1.0f, 1.0f, 1.0f, 1.0f}).build();
    ui.image("img").source("assets/x.png").cover().build();
    ui.svg("svg").source("<svg/>").build();
    ui.polygon("poly").point(0.0f, 0.0f).point(1.0f, 1.0f).build();
    ui.loader("ldr").active(true).mode(core::dsl::LoaderMode::KeepAlive).build();
    ui.shadertoy("st").resolutionScale(1.0f).timeScale(1.0f).paused().build();
}

int main() {
    const std::string heart = core::dsl::utf8(0x2665);
    assert(heart == "\xE2\x99\xA5");

    const core::dsl::ElementKind kind = core::dsl::ElementKind::Rect;
    const core::dsl::HitTestMode hit = core::dsl::HitTestMode::Transformed;
    const core::dsl::LoaderMode mode = core::dsl::LoaderMode::KeepAlive;
    assert(kind == core::dsl::ElementKind::Rect);
    assert(hit == core::dsl::HitTestMode::Transformed);
    assert(mode == core::dsl::LoaderMode::KeepAlive);

    core::dsl::StateStore store;
    int& counter = store.get<int>("counter");
    counter = 42;
    assert(store.get<int>("counter") == 42);
    store.releasePrefix("counter");

    core::dsl::Screen screen{800.0f, 600.0f};
    assert(screen.width == 800.0f && screen.height == 600.0f);

    core::dsl::Element el;
    el.kind = core::dsl::ElementKind::Column;
    assert(el.layoutType() == eui::LayoutType::Column);

    using LayoutSizeFn = core::dsl::LayoutBuilder& (core::dsl::LayoutBuilder::*)(float, float);
    LayoutSizeFn layoutSize = static_cast<LayoutSizeFn>(&core::dsl::LayoutBuilder::size);
    (void)layoutSize;

    auto rectColor = &core::dsl::RectBuilder::color;
    (void)rectColor;

    auto textText = &core::dsl::TextBuilder::text;
    (void)textText;

    auto imageSource = &core::dsl::ImageBuilder::source;
    (void)imageSource;

    auto svgSource = &core::dsl::SvgBuilder::source;
    (void)svgSource;

    auto shadertoyGraph = &core::dsl::ShadertoyBuilder::graph;
    (void)shadertoyGraph;

    auto polygonPoint = &core::dsl::PolygonBuilder::point;
    (void)polygonPoint;

    auto loaderActive = &core::dsl::LoaderBuilder::active;
    (void)loaderActive;

    auto loaderBuild = &core::dsl::LoaderBuilder::build;
    (void)loaderBuild;

    auto compose = [](core::dsl::RectBuilder& b) {
        b.size(100.0f, 50.0f).color({1.0f, 0.0f, 0.0f, 1.0f}).build();
    };
    (void)compose;

    std::puts("PASS: eui.dsl module smoke (utf8/enums/StateStore/Screen/Element/Builder surface)");
    return 0;
}
