#include <cassert>
#include <cstdio>
#include <string>

import eui.platform;
import eui.types;

int main() {
    const double boot = eui::platform::timeSeconds();
    assert(boot >= 0.0);

    eui::window::Handle window = eui::platform::createWindow(320, 240, "platform-smoke");
    if (window != nullptr) {
        eui::window::NativeWindowInfo info = eui::platform::nativeWindowInfo(window);
        assert(info.handle == window);

        eui::platform::queueTextInput(window, "hello");
        eui::platform::queueTextEditing(window, "hel");
        eui::platform::queueKeyInput(window, eui::input::InputKey::Enter);
        eui::platform::queueKeyInput(window, eui::input::InputKey::A, true);
        eui::platform::queueScrollInput(window, 0.0, 10.0);

        const bool pending = eui::platform::hasPendingPointerInput(window);
        eui::input::PointerEvent pointer = eui::platform::readPointerEvent(window);

        double px = 0.0;
        double py = 0.0;
        eui::platform::getCursorPosition(window, px, py);
        assert(pointer.x == px);
        assert(pointer.y == py);
        assert(pointer.down == eui::platform::isMouseButtonDown(window, 0));
        (void)pending;

        eui::platform::setClipboardText("clip");
        const std::string clip = eui::platform::clipboardText(window);

        eui::window::CursorHandle cursor = eui::platform::createStandardCursor(eui::window::CursorType::Arrow);
        eui::platform::setCursor(window, cursor);
        eui::platform::destroyCursor(cursor);
        eui::platform::setImeCursorRect(window, 0.0f, 0.0f, 100.0f, 24.0f);
        eui::platform::setWindowIcon(window, 1, 1, nullptr);

        eui::platform::releaseInputQueue(window);

        void* backend = eui::platform::createRenderBackend(window);
        if (backend != nullptr) {
            assert(eui::platform::activeRenderBackend() != nullptr);
            eui::platform::destroyRenderBackend(backend);
        }

        eui::platform::destroyWindow(window);
    }

    eui::Color color{0.1f, 0.2f, 0.3f, 1.0f};
    assert(color.b == 0.3f);

    std::puts("PASS: eui.platform smoke (window/input/render-backend bridge)");
    return 0;
}
