#include <cassert>
#include <cstdio>

import eui.types;

int main() {
    eui::Color color{0.25f, 0.5f, 0.75f, 1.0f};
    assert(color.r == 0.25f);
    assert(color.g == 0.5f);
    assert(color.b == 0.75f);
    assert(color.a == 1.0f);

    eui::Vec2 v2{1.0f, 2.0f};
    assert(v2.x == 1.0f && v2.y == 2.0f);

    eui::Rect rect{0.0f, 0.0f, 100.0f, 50.0f};
    assert(rect.contains(50.0, 25.0));
    assert(!rect.contains(150.0, 25.0));

    eui::SizeValue size = eui::SizeValue::fixed(32.0f);
    assert(size.mode == eui::SizeMode::Fixed);
    assert(size.value == 32.0f);

    eui::Transition transition = eui::Transition::make(0.2f);
    assert(transition.enabled);
    assert(transition.durationSeconds == 0.2f);
    assert(transition.ease == eui::Ease::OutCubic);
    assert(transition.properties == eui::AnimProperty::All);

    std::puts("PASS: eui.types module smoke (Color/Vec2/Rect/SizeValue/Transition)");
    return 0;
}
