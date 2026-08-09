#include "core/window/window_backend.h"
int main() {
    core::window::WindowCreateRequest req{};
    req.width = 200; req.height = 200; req.title = "smoke";
    void* w = core::window::createWindow(req);
    if (w == nullptr) return 1;
    core::window::destroyWindow(w);
    return 0;
}