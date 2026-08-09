module;

#include "core/window/window_backend.h"
#include "core/render/render_backend.h"
#include "core/input/input_state.h"

#include <memory>
#include <string>
#include <unordered_map>

export module eui.platform;

namespace eui::platform::detail {

inline std::unordered_map<void*, std::unique_ptr<core::render::RenderBackend>>& ownedBackends() {
    static std::unordered_map<void*, std::unique_ptr<core::render::RenderBackend>> backends;
    return backends;
}

} // namespace eui::platform::detail

export namespace eui::window {

using Handle = core::window::Handle;
using CursorHandle = core::window::CursorHandle;
using CursorType = core::window::CursorType;
using RenderApi = core::window::RenderApi;

struct WindowCreateRequest {
    int width = 0;
    int height = 0;
    const char* title = "";
    bool resizable = true;
    bool highDpi = true;
    bool modal = false;
    Handle parent = nullptr;
    RenderApi renderApi = RenderApi::OpenGL;
};

struct NativeWindowInfo {
    Handle handle = nullptr;
    void* platformWindow = nullptr;
    void* platformDisplay = nullptr;
    void* platformView = nullptr;
};

} // namespace eui::window

export namespace eui::input {

using InputKey = core::InputKey;
using PointerEvent = core::PointerEvent;

} // namespace eui::input

export namespace eui::platform {

eui::window::Handle createWindow(int width, int height, const char* title);
eui::window::Handle createWindow(const eui::window::WindowCreateRequest& request);
void destroyWindow(eui::window::Handle window);
eui::window::NativeWindowInfo nativeWindowInfo(eui::window::Handle window);

void* createRenderBackend(eui::window::Handle window);
void destroyRenderBackend(void* backend);
void* activeRenderBackend();

double timeSeconds();
void postEmptyEvent();

void queueTextInput(eui::window::Handle window, const char* text);
void queueTextEditing(eui::window::Handle window, const char* text);
void queueScrollInput(eui::window::Handle window, double x, double y);
void queueKeyInput(eui::window::Handle window, eui::input::InputKey key, bool ctrl = false, bool shift = false);
eui::input::PointerEvent readPointerEvent(eui::window::Handle window, float dpiScale = 1.0f);
bool hasPendingPointerInput(eui::window::Handle window, float dpiScale = 1.0f);
void releaseInputQueue(eui::window::Handle window);

eui::window::CursorHandle createStandardCursor(eui::window::CursorType type);
void setCursor(eui::window::Handle window, eui::window::CursorHandle cursor);
void destroyCursor(eui::window::CursorHandle cursor);
void getCursorPosition(eui::window::Handle window, double& x, double& y);
bool isMouseButtonDown(eui::window::Handle window, int button);
std::string clipboardText(eui::window::Handle window);
void setClipboardText(const char* text);
void setWindowIcon(eui::window::Handle window, int width, int height, unsigned char* pixels);
void setImeCursorRect(eui::window::Handle window, float x, float y, float width, float height);

} // namespace eui::platform

namespace eui::platform {

eui::window::Handle createWindow(int width, int height, const char* title) {
    core::window::WindowCreateRequest request{};
    request.width = width;
    request.height = height;
    request.title = title != nullptr ? title : "";
    return core::window::createWindow(request);
}

eui::window::Handle createWindow(const eui::window::WindowCreateRequest& request) {
    core::window::WindowCreateRequest engineRequest{};
    engineRequest.width = request.width;
    engineRequest.height = request.height;
    engineRequest.title = request.title;
    engineRequest.resizable = request.resizable;
    engineRequest.highDpi = request.highDpi;
    engineRequest.modal = request.modal;
    engineRequest.parent = request.parent;
    engineRequest.renderApi = request.renderApi;
    return core::window::createWindow(engineRequest);
}

void destroyWindow(eui::window::Handle window) {
    core::window::destroyWindow(window);
}

eui::window::NativeWindowInfo nativeWindowInfo(eui::window::Handle window) {
    const core::window::NativeWindowInfo info = core::window::nativeWindowInfo(window);
    eui::window::NativeWindowInfo result{};
    result.handle = info.handle;
    result.platformWindow = info.platformWindow;
    result.platformDisplay = info.platformDisplay;
    result.platformView = info.platformView;
    return result;
}

void* createRenderBackend(eui::window::Handle window) {
    std::unique_ptr<core::render::RenderBackend> backend = core::render::createRenderBackend(window);
    void* raw = backend.get();
    if (raw == nullptr) {
        return nullptr;
    }
    core::render::activeRenderBackendSlot() = backend.get();
    detail::ownedBackends()[raw] = std::move(backend);
    return raw;
}

void destroyRenderBackend(void* backend) {
    if (backend == nullptr) {
        return;
    }
    if (core::render::activeRenderBackend() == backend) {
        core::render::activeRenderBackendSlot() = nullptr;
    }
    detail::ownedBackends().erase(backend);
}

void* activeRenderBackend() {
    return core::render::activeRenderBackend();
}

double timeSeconds() {
    return core::window::timeSeconds();
}

void postEmptyEvent() {
    core::window::postEmptyEvent();
}

void queueTextInput(eui::window::Handle window, const char* text) {
    core::queueTextInput(window, text != nullptr ? text : "");
}

void queueTextEditing(eui::window::Handle window, const char* text) {
    core::queueTextEditing(window, text != nullptr ? text : "");
}

void queueScrollInput(eui::window::Handle window, double x, double y) {
    core::queueScrollInput(window, x, y);
}

void queueKeyInput(eui::window::Handle window, eui::input::InputKey key, bool ctrl, bool shift) {
    core::queueKeyInput(window, key, ctrl, shift);
}

eui::input::PointerEvent readPointerEvent(eui::window::Handle window, float dpiScale) {
    return core::readPointerEvent(window, dpiScale);
}

bool hasPendingPointerInput(eui::window::Handle window, float dpiScale) {
    return core::hasPendingPointerInput(window, dpiScale);
}

void releaseInputQueue(eui::window::Handle window) {
    core::releaseInputQueue(window);
}

eui::window::CursorHandle createStandardCursor(eui::window::CursorType type) {
    return core::window::createStandardCursor(type);
}

void setCursor(eui::window::Handle window, eui::window::CursorHandle cursor) {
    core::window::setCursor(window, cursor);
}

void destroyCursor(eui::window::CursorHandle cursor) {
    core::window::destroyCursor(cursor);
}

void getCursorPosition(eui::window::Handle window, double& x, double& y) {
    core::window::getCursorPosition(window, x, y);
}

bool isMouseButtonDown(eui::window::Handle window, int button) {
    return core::window::isMouseButtonDown(window, button);
}

std::string clipboardText(eui::window::Handle window) {
    return core::window::clipboardText(window);
}

void setClipboardText(const char* text) {
    core::window::setClipboardText(text != nullptr ? text : "");
}

void setWindowIcon(eui::window::Handle window, int width, int height, unsigned char* pixels) {
    core::window::setWindowIcon(window, width, height, pixels);
}

void setImeCursorRect(eui::window::Handle window, float x, float y, float width, float height) {
    core::window::setImeCursorRect(window, x, y, width, height);
}

} // namespace eui::platform
