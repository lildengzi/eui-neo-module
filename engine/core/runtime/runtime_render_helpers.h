#pragma once

#include "core/runtime/runtime_geometry.h"
#include "core/render/render_backend.h"

#include <vector>

namespace core::dsl {

inline void applyOptionalScissor(core::render::RenderBackend& renderBackend, bool enabled, const Rect& rect, int windowHeight) {
    renderBackend.setScissor(enabled, rect, windowHeight);
}

inline std::vector<Vec2> scaledPolygonPoints(const std::vector<Vec2>& points, float dpiScale) {
    std::vector<Vec2> result;
    result.reserve(points.size());
    for (const Vec2& point : points) {
        result.push_back({toPixels(point.x, dpiScale), toPixels(point.y, dpiScale)});
    }
    return result;
}

} // namespace core::dsl
