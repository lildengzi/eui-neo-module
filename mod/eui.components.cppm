module;

#include "core/render/render_types.h"
#include "core/render/text.h"
#include "core/render/text_types.h"
#include "core/layout.h"
#include "core/animation.h"
#include "core/input/input_types.h"
#include "core/window/window_backend.h"
#include "core/platform/platform.h"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

export module eui.components;

import eui.types;
import eui.dsl;

export {

#include "eui/signal.h"

namespace components::theme {

struct TypographyTokens {
    float micro = 11.0f;
    float caption = 12.0f;
    float hint = 13.0f;
    float label = 14.0f;
    float option = 15.0f;
    float body = 16.0f;
    float input = 17.0f;
    float control = 18.0f;
    float cardTitle = 19.0f;
    float subtitle = 20.0f;
    float title = 22.0f;
    float heading = 24.0f;
    float headline = 27.0f;
    float displayCompact = 30.0f;
    float display = 31.0f;
    float hero = 42.0f;
    float lineGapTight = 3.0f;
    float lineGap = 4.0f;
    float lineGapRelaxed = 5.0f;
    float lineGapLoose = 6.0f;
    float lineGapComfortable = 7.0f;
    float lineGapWide = 8.0f;
};

struct SpacingTokens {
    float hairline = 1.0f;
    float micro = 2.0f;
    float tiny = 4.0f;
    float small = 6.0f;
    float compact = 8.0f;
    float control = 10.0f;
    float content = 12.0f;
    float section = 16.0f;
    float large = 20.0f;
    float panel = 24.0f;
    float header = 30.0f;
    float page = 40.0f;
    float overlay = 48.0f;
};

struct RadiusTokens {
    float micro = 2.0f;
    float tiny = 4.0f;
    float small = 6.0f;
    float control = 8.0f;
    float tooltip = 9.0f;
    float popup = 10.0f;
    float card = 12.0f;
    float elevated = 14.0f;
    float overlay = 16.0f;
    float section = 18.0f;
    float feature = 22.0f;
    float full = 999.0f;
};

struct ControlSizeTokens {
    float progress = 14.0f;
    float indicator = 22.0f;
    float switchHeight = 24.0f;
    float compact = 28.0f;
    float menuItem = 34.0f;
    float field = 35.0f;
    float segmented = 36.0f;
    float input = 40.0f;
    float control = 44.0f;
    float large = 44.0f;
    float switchWidth = 46.0f;
    float navigation = 50.0f;
    float scrollbar = 8.0f;
};

struct ThemeMetricTokens {
    TypographyTokens typography;
    SpacingTokens spacing;
    RadiusTokens radius;
    ControlSizeTokens control;
};

struct ThemeColorTokens {
    core::Color background;
    core::Color primary;
    core::Color surface;
    core::Color surfaceHover;
    core::Color surfaceActive;
    core::Color text;
    core::Color border;
    bool dark = false;
    ThemeMetricTokens metrics;
};

struct PageVisualTokens {
    core::Color titleColor;
    core::Color subtitleColor;
    core::Color bodyColor;
    core::Color cardColor;
    core::Color mutedCardColor;
    core::Color softAccentColor;
    float headerTopInset = 24.0f;
    float headerTitleGap = 30.0f;
    float headerContentGap = 40.0f;
    float headerTitleSize = 31.0f;
    float headerSubtitleSize = 20.0f;
    float sectionGap = 16.0f;
    float sectionInset = 20.0f;
    float sectionRounding = 18.0f;
    float labelSize = 17.0f;
    float fieldHeight = 35.0f;
};

struct FieldVisualTokens {
    float rounding = 6.0f;
    float horizontalInset = 10.0f;
    float focusLineHeight = 2.0f;
    float borderLineHeight = 1.0f;
    float popupRounding = 10.0f;
    float popupOverlap = 1.0f;
    core::Color popupShadowColor;
    float popupShadowBlur = 0.0f;
    float popupShadowOffsetY = 0.0f;
};

struct PageHeaderLayout {
    float titleY = 0.0f;
    float subtitleY = 0.0f;
    float contentY = 0.0f;
};

inline core::Color color(float r, float g, float b, float a = 1.0f) {
    return {r, g, b, a};
}

inline core::Color defaultPrimary(float a = 1.0f) {
    return color(56.0f / 255.0f, 113.0f / 255.0f, 224.0f / 255.0f, a);
}

inline core::Color withAlpha(core::Color value, float alpha) {
    value.a = std::clamp(alpha, 0.0f, 1.0f);
    return value;
}

inline core::Color withOpacity(core::Color value, float opacity) {
    value.a *= std::clamp(opacity, 0.0f, 1.0f);
    return value;
}

inline ThemeColorTokens light() {
    return {
        color(0.95f, 0.95f, 0.97f),
        defaultPrimary(),
        color(1.00f, 1.00f, 1.00f),
        color(0.90f, 0.90f, 0.90f),
        color(0.80f, 0.80f, 0.80f),
        color(0.00f, 0.00f, 0.00f),
        color(0.80f, 0.80f, 0.80f),
        false
    };
}

inline ThemeColorTokens dark() {
    return {
        color(0.10f, 0.10f, 0.12f),
        defaultPrimary(),
        color(0.15f, 0.15f, 0.18f),
        color(0.25f, 0.25f, 0.28f),
        color(0.35f, 0.35f, 0.38f),
        color(1.00f, 1.00f, 1.00f),
        color(0.30f, 0.30f, 0.30f),
        true
    };
}

inline PageVisualTokens pageVisuals(const ThemeColorTokens& tokens) {
    const ThemeMetricTokens& metrics = tokens.metrics;
    return {
        withAlpha(tokens.text, 0.98f),
        withAlpha(tokens.text, 0.72f),
        withAlpha(tokens.text, 0.68f),
        tokens.surface,
        tokens.surfaceHover,
        withAlpha(tokens.primary, 0.16f),
        metrics.spacing.panel,
        metrics.spacing.header,
        metrics.spacing.page,
        metrics.typography.display,
        metrics.typography.subtitle,
        metrics.spacing.section,
        metrics.spacing.large,
        metrics.radius.section,
        metrics.typography.input,
        metrics.control.field
    };
}

inline FieldVisualTokens fieldVisuals(const ThemeColorTokens& tokens) {
    FieldVisualTokens result;
    result.rounding = tokens.metrics.radius.small;
    result.horizontalInset = tokens.metrics.spacing.control;
    result.focusLineHeight = tokens.metrics.spacing.micro;
    result.borderLineHeight = tokens.metrics.spacing.hairline;
    result.popupRounding = tokens.metrics.radius.popup;
    result.popupOverlap = tokens.metrics.spacing.hairline;
    result.popupShadowColor = tokens.dark
        ? color(0.0f, 0.0f, 0.0f, 0.28f)
        : color(0.10f, 0.14f, 0.22f, 0.14f);
    result.popupShadowBlur = tokens.dark ? 18.0f : 12.0f;
    result.popupShadowOffsetY = tokens.dark ? 8.0f : 5.0f;
    return result;
}

inline core::Color resolveFieldFill(const ThemeColorTokens& tokens,
                                    core::Color baseColor,
                                    float hoverAmount,
                                    float activeAmount) {
    const float hover = std::clamp(hoverAmount, 0.0f, 1.0f);
    const float active = std::clamp(activeAmount, 0.0f, 1.0f);
    const core::Color base = baseColor.a > 0.0f ? baseColor : tokens.surface;
    const core::Color hoverColor = baseColor.a > 0.0f
        ? core::mixColor(base, tokens.surfaceHover, 0.65f)
        : tokens.surfaceHover;
    return core::mixColor(core::mixColor(base, tokens.surfaceActive, active), hoverColor, hover);
}

inline core::Color buttonHover(const ThemeColorTokens& tokens, core::Color base) {
    return core::mixColor(base, tokens.dark ? color(1.0f, 1.0f, 1.0f, base.a) : tokens.primary, tokens.dark ? 0.16f : 0.10f);
}

inline core::Color buttonPressed(const ThemeColorTokens& tokens, core::Color base) {
    return core::mixColor(base, tokens.dark ? color(0.0f, 0.0f, 0.0f, base.a) : tokens.surfaceActive, tokens.dark ? 0.34f : 0.22f);
}

inline core::Border border(const ThemeColorTokens& tokens, float width = 1.0f, float opacity = 1.0f) {
    return {width, withOpacity(tokens.border, opacity)};
}

inline core::Border buttonBorder(const ThemeColorTokens& tokens, bool primary = true) {
    return {1.0f, primary ? withAlpha(tokens.primary, 0.58f) : withOpacity(tokens.border, 0.70f)};
}

inline core::Shadow shadow(const ThemeColorTokens& tokens,
                           float blur,
                           float offsetY,
                           float darkAlpha,
                           float lightAlpha) {
    return {
        true,
        {0.0f, offsetY},
        blur,
        0.0f,
        tokens.dark ? color(0.0f, 0.0f, 0.0f, darkAlpha) : color(0.10f, 0.14f, 0.22f, lightAlpha)
    };
}

inline core::Shadow buttonShadow(const ThemeColorTokens& tokens) {
    return shadow(tokens, 14.0f, 4.0f, 0.22f, 0.10f);
}

inline core::Shadow panelShadow(const ThemeColorTokens& tokens) {
    return shadow(tokens, 24.0f, 8.0f, 0.28f, 0.12f);
}

inline core::Shadow popupShadow(const ThemeColorTokens& tokens) {
    const FieldVisualTokens field = fieldVisuals(tokens);
    return {true, {0.0f, field.popupShadowOffsetY}, field.popupShadowBlur, 0.0f, field.popupShadowColor};
}

} // namespace components::theme



namespace components {

struct MouseEvent {
    float x = 0.0f;
    float y = 0.0f;
    float globalX = 0.0f;
    float globalY = 0.0f;
    float deltaX = 0.0f;
    float deltaY = 0.0f;
    core::Rect bounds;
    bool down = false;
    bool rightDown = false;
    bool inside = false;
};

struct MouseDragEvent : MouseEvent {
    float totalX = 0.0f;
    float totalY = 0.0f;
};

struct MouseScrollEvent {
    float deltaX = 0.0f;
    float deltaY = 0.0f;
    float stepX = 0.0f;
    float stepY = 0.0f;
};

class MouseAreaBuilder {
public:
    MouseAreaBuilder(core::dsl::Ui& ui, std::string id)
        : ui_(ui), id_(std::move(id)) {}

    MouseAreaBuilder& x(float value) { x_ = value; hasX_ = true; return *this; }
    MouseAreaBuilder& y(float value) { y_ = value; hasY_ = true; return *this; }
    MouseAreaBuilder& position(float xValue, float yValue) { return x(xValue).y(yValue); }
    MouseAreaBuilder& size(float width, float height) { width_ = width; height_ = height; return *this; }
    MouseAreaBuilder& width(float value) { width_ = value; return *this; }
    MouseAreaBuilder& height(float value) { height_ = value; return *this; }
    MouseAreaBuilder& zIndex(int value) { zIndex_ = value; hasZIndex_ = true; return *this; }
    MouseAreaBuilder& radius(float value) { radius_ = std::max(0.0f, value); return *this; }
    MouseAreaBuilder& color(const core::Color& value) { color_ = value; return *this; }
    MouseAreaBuilder& cursor(core::CursorShape value) { cursor_ = value; return *this; }
    MouseAreaBuilder& disabled(bool value = true) { disabled_ = value; return *this; }
    MouseAreaBuilder& preserveFocusOnPress(bool value = true) { preserveFocusOnPress_ = value; return *this; }
    MouseAreaBuilder& scrollStep(float value) { scrollStep_ = std::max(0.0f, value); return *this; }
    MouseAreaBuilder& maxScrollStep(float value) { maxScrollStep_ = std::max(0.0f, value); return *this; }
    MouseAreaBuilder& dragThreshold(float value) { dragThreshold_ = std::max(0.0f, value); return *this; }
    MouseAreaBuilder& suppressClickAfterDrag(bool value = true) { suppressClickAfterDrag_ = value; return *this; }

    MouseAreaBuilder& onTap(std::function<void()> callback) { onClick_ = std::move(callback); return *this; }
    MouseAreaBuilder& onTap(std::function<void(const MouseEvent&)> callback) { onClickAt_ = std::move(callback); return *this; }
    MouseAreaBuilder& onPress(std::function<void(const MouseEvent&)> callback) { onPress_ = std::move(callback); return *this; }
    MouseAreaBuilder& onRelease(std::function<void(const MouseEvent&)> callback) { onRelease_ = std::move(callback); return *this; }
    MouseAreaBuilder& onHover(std::function<void(bool)> callback) { onHover_ = std::move(callback); return *this; }
    MouseAreaBuilder& onEnter(std::function<void()> callback) { onEnter_ = std::move(callback); return *this; }
    MouseAreaBuilder& onLeave(std::function<void()> callback) { onLeave_ = std::move(callback); return *this; }
    MouseAreaBuilder& onMove(std::function<bool(const MouseEvent&)> callback) { onMove_ = std::move(callback); return *this; }
    template <typename Callback,
              typename = std::enable_if_t<!std::is_convertible_v<Callback, std::function<bool(const MouseEvent&)>>>>
    MouseAreaBuilder& onMove(Callback callback) {
        onMove_ = [callback = std::move(callback)](const MouseEvent& event) mutable {
            callback(event);
            return true;
        };
        return *this;
    }
    MouseAreaBuilder& onDragStart(std::function<void(const MouseEvent&)> callback) { onDragStart_ = std::move(callback); return *this; }
    MouseAreaBuilder& onDrag(std::function<void(const MouseDragEvent&)> callback) { onDrag_ = std::move(callback); return *this; }
    MouseAreaBuilder& onDragEnd(std::function<void(const MouseDragEvent&)> callback) { onDragEnd_ = std::move(callback); return *this; }
    MouseAreaBuilder& onScroll(std::function<void(const MouseScrollEvent&)> callback) { onScroll_ = std::move(callback); return *this; }
    MouseAreaBuilder& onContextMenu(std::function<void(const MouseEvent&)> callback) { onContextMenu_ = std::move(callback); return *this; }

    void build() {
        MouseAreaState* state = &ui_.state<MouseAreaState>(id_);
        const float safeWidth = std::max(1.0f, width_);
        const float safeHeight = std::max(1.0f, height_);
        const float scrollStep = scrollStep_;
        const float maxScrollStep = maxScrollStep_;
        const float dragThreshold = dragThreshold_;
        const bool suppressClickAfterDrag = suppressClickAfterDrag_;
        const std::function<void()> onClick = onClick_;
        const std::function<void(const MouseEvent&)> onClickAt = onClickAt_;
        const std::function<void(const MouseEvent&)> onPress = onPress_;
        const std::function<void(const MouseEvent&)> onRelease = onRelease_;
        const std::function<void(bool)> onHover = onHover_;
        const std::function<void()> onEnter = onEnter_;
        const std::function<void()> onLeave = onLeave_;
        const std::function<bool(const MouseEvent&)> onMove = onMove_;
        const std::function<void(const MouseEvent&)> onDragStart = onDragStart_;
        const std::function<void(const MouseDragEvent&)> onDrag = onDrag_;
        const std::function<void(const MouseDragEvent&)> onDragEnd = onDragEnd_;
        const std::function<void(const MouseScrollEvent&)> onScroll = onScroll_;
        const std::function<void(const MouseEvent&)> onContextMenu = onContextMenu_;

        auto area = ui_.rect(id_);
        if (hasX_) {
            area.x(x_);
        }
        if (hasY_) {
            area.y(y_);
        }
        if (hasZIndex_) {
            area.zIndex(zIndex_);
        }

        area.size(safeWidth, safeHeight)
            .color(color_)
            .radius(radius_)
            .disabled(disabled_)
            .preserveFocusOnPress(preserveFocusOnPress_)
            .interactive()
            .cursor(cursor_);

        if (onClick || onClickAt || onPress || onDragStart || onDrag || onDragEnd || onRelease) {
            area.onPress([state, safeWidth, safeHeight, onPress](const core::PointerEvent& event, const core::Rect& bounds) {
                state->bounds = bounds;
                state->width = safeWidth;
                state->height = safeHeight;
                state->pressed = true;
                state->dragging = false;
                state->dragged = false;
                state->lastDrag = {};
                state->lastEvent = makeMouseEvent(event, bounds, safeWidth, safeHeight);
                state->pressEvent = state->lastEvent;
                if (onPress) {
                    onPress(state->lastEvent);
                }
            });
        }

        if (onClick || onClickAt || onRelease || onDragEnd) {
            area.onRelease([state, onClick, onClickAt, onRelease, onDragEnd, suppressClickAfterDrag](const core::PointerEvent& event, const core::Rect& bounds) {
                state->lastEvent = makeMouseEvent(event, bounds, state->width, state->height);
                if (state->lastEvent.inside && (!suppressClickAfterDrag || !state->dragged)) {
                    if (onClick) {
                        onClick();
                    }
                    if (onClickAt) {
                        onClickAt(state->lastEvent);
                    }
                }
                if (onRelease) {
                    onRelease(state->lastEvent);
                }
                if (onDragEnd && state->dragging) {
                    MouseDragEvent drag = makeMouseDragEvent(event, state->bounds, state->width, state->height, 0.0, 0.0);
                    drag.totalX = state->lastDrag.totalX;
                    drag.totalY = state->lastDrag.totalY;
                    onDragEnd(drag);
                }
                state->pressed = false;
                state->dragging = false;
            });
        }

        if (onHover || onEnter || onLeave) {
            area.onHover([onHover, onEnter, onLeave](bool hover) {
                if (onHover) {
                    onHover(hover);
                }
                if (hover && onEnter) {
                    onEnter();
                }
                if (!hover && onLeave) {
                    onLeave();
                }
            });
        }

        if (onMove) {
            area.onMove([safeWidth, safeHeight, onMove](const core::PointerEvent& event, const core::Rect& bounds) {
                return onMove(makeMouseEvent(event, bounds, safeWidth, safeHeight));
            });
        }

        if (onDrag || onDragStart || onDragEnd) {
            area.onDrag([state, safeWidth, safeHeight, onDrag, onDragStart, dragThreshold](const core::dsl::DragEvent& event) {
                if (state->bounds.width <= 0.0f || state->bounds.height <= 0.0f) {
                    state->bounds = {0.0f, 0.0f, safeWidth, safeHeight};
                    state->width = safeWidth;
                    state->height = safeHeight;
                }
                MouseDragEvent drag = makeMouseDragEvent(event, state->bounds, state->width, state->height);
                if (!state->dragged && (std::fabs(drag.totalX) >= dragThreshold || std::fabs(drag.totalY) >= dragThreshold)) {
                    state->dragged = true;
                }
                if (!state->dragged) {
                    return;
                }
                if (!state->dragging) {
                    if (onDragStart) {
                        onDragStart(state->pressEvent);
                    }
                    state->dragging = true;
                }
                state->lastEvent = drag;
                state->lastDrag = drag;
                if (onDrag) {
                    onDrag(drag);
                }
            });
        }

        if (onScroll) {
            area.onScroll([onScroll, scrollStep, maxScrollStep](const core::ScrollEvent& event) {
                MouseScrollEvent scroll;
                scroll.deltaX = static_cast<float>(event.x);
                scroll.deltaY = static_cast<float>(event.y);
                scroll.stepX = std::clamp(scroll.deltaX, -maxScrollStep, maxScrollStep) * scrollStep;
                scroll.stepY = std::clamp(scroll.deltaY, -maxScrollStep, maxScrollStep) * scrollStep;
                onScroll(scroll);
            });
        }

        if (onContextMenu) {
            area.onContextMenu([safeWidth, safeHeight, onContextMenu](const core::PointerEvent& event, const core::Rect& bounds) {
                onContextMenu(makeMouseEvent(event, bounds, safeWidth, safeHeight));
            });
        }

        area.build();
    }

private:
    struct MouseAreaState {
        core::Rect bounds;
        float width = 1.0f;
        float height = 1.0f;
        bool pressed = false;
        bool dragging = false;
        bool dragged = false;
        MouseEvent pressEvent;
        MouseEvent lastEvent;
        MouseDragEvent lastDrag;
    };

    static float scaleFor(float actual, float expected) {
        return actual > 0.0f && expected > 0.0f ? actual / expected : 1.0f;
    }

    static MouseEvent makeMouseEvent(const core::PointerEvent& event, const core::Rect& bounds, float width, float height) {
        const float scaleX = scaleFor(bounds.width, width);
        const float scaleY = scaleFor(bounds.height, height);
        MouseEvent result;
        result.x = static_cast<float>((event.x - bounds.x) / std::max(0.001f, scaleX));
        result.y = static_cast<float>((event.y - bounds.y) / std::max(0.001f, scaleY));
        result.globalX = static_cast<float>(event.x / std::max(0.001f, scaleX));
        result.globalY = static_cast<float>(event.y / std::max(0.001f, scaleY));
        result.deltaX = static_cast<float>(event.deltaX / std::max(0.001f, scaleX));
        result.deltaY = static_cast<float>(event.deltaY / std::max(0.001f, scaleY));
        result.bounds = {
            static_cast<float>(bounds.x / std::max(0.001f, scaleX)),
            static_cast<float>(bounds.y / std::max(0.001f, scaleY)),
            width,
            height
        };
        result.down = event.down;
        result.rightDown = event.rightDown;
        result.inside = result.x >= 0.0f && result.y >= 0.0f && result.x <= width && result.y <= height;
        return result;
    }

    static MouseDragEvent makeMouseDragEvent(const core::dsl::DragEvent& event, const core::Rect& bounds, float width, float height) {
        const float scaleX = scaleFor(bounds.width, width);
        const float scaleY = scaleFor(bounds.height, height);
        MouseDragEvent result;
        result.x = static_cast<float>((event.x - bounds.x) / std::max(0.001f, scaleX));
        result.y = static_cast<float>((event.y - bounds.y) / std::max(0.001f, scaleY));
        result.globalX = static_cast<float>(event.x / std::max(0.001f, scaleX));
        result.globalY = static_cast<float>(event.y / std::max(0.001f, scaleY));
        result.deltaX = static_cast<float>(event.deltaX / std::max(0.001f, scaleX));
        result.deltaY = static_cast<float>(event.deltaY / std::max(0.001f, scaleY));
        result.totalX = static_cast<float>(event.totalX / std::max(0.001f, scaleX));
        result.totalY = static_cast<float>(event.totalY / std::max(0.001f, scaleY));
        result.bounds = {
            static_cast<float>(bounds.x / std::max(0.001f, scaleX)),
            static_cast<float>(bounds.y / std::max(0.001f, scaleY)),
            width,
            height
        };
        result.down = true;
        result.inside = result.x >= 0.0f && result.y >= 0.0f && result.x <= width && result.y <= height;
        return result;
    }

    static MouseDragEvent makeMouseDragEvent(const core::PointerEvent& event,
                                             const core::Rect& bounds,
                                             float width,
                                             float height,
                                             double totalX,
                                             double totalY) {
        MouseDragEvent result;
        static_cast<MouseEvent&>(result) = makeMouseEvent(event, bounds, width, height);
        const float scaleX = scaleFor(bounds.width, width);
        const float scaleY = scaleFor(bounds.height, height);
        result.totalX = static_cast<float>(totalX / std::max(0.001f, scaleX));
        result.totalY = static_cast<float>(totalY / std::max(0.001f, scaleY));
        return result;
    }

    core::dsl::Ui& ui_;
    std::string id_;
    core::Color color_ = {0.0f, 0.0f, 0.0f, 0.0f};
    core::CursorShape cursor_ = core::CursorShape::Hand;
    std::function<void()> onClick_;
    std::function<void(const MouseEvent&)> onClickAt_;
    std::function<void(const MouseEvent&)> onPress_;
    std::function<void(const MouseEvent&)> onRelease_;
    std::function<void(bool)> onHover_;
    std::function<void()> onEnter_;
    std::function<void()> onLeave_;
    std::function<bool(const MouseEvent&)> onMove_;
    std::function<void(const MouseEvent&)> onDragStart_;
    std::function<void(const MouseDragEvent&)> onDrag_;
    std::function<void(const MouseDragEvent&)> onDragEnd_;
    std::function<void(const MouseScrollEvent&)> onScroll_;
    std::function<void(const MouseEvent&)> onContextMenu_;
    float x_ = 0.0f;
    float y_ = 0.0f;
    float width_ = 1.0f;
    float height_ = 1.0f;
    float radius_ = 0.0f;
    float scrollStep_ = 1.0f;
    float maxScrollStep_ = 1.0f;
    float dragThreshold_ = 2.0f;
    int zIndex_ = 0;
    bool hasX_ = false;
    bool hasY_ = false;
    bool hasZIndex_ = false;
    bool disabled_ = false;
    bool preserveFocusOnPress_ = false;
    bool suppressClickAfterDrag_ = true;
};

inline MouseAreaBuilder mouseArea(core::dsl::Ui& ui, const std::string& id) {
    return MouseAreaBuilder(ui, id);
}

} // namespace components



namespace components {

struct ButtonStyle {
    ButtonStyle() : ButtonStyle(theme::dark()) {}

    explicit ButtonStyle(const theme::ThemeColorTokens& tokens, bool primary = true) {
        const core::Color base = primary ? tokens.primary : tokens.surface;
        normal = base;
        hover = theme::buttonHover(tokens, base);
        pressed = theme::buttonPressed(tokens, base);
        text = primary || tokens.dark ? core::Color{0.94f, 0.97f, 1.0f, 1.0f} : tokens.text;
        icon = text;
        border = theme::buttonBorder(tokens, primary);
        shadow = theme::buttonShadow(tokens);
        radius = tokens.metrics.radius.overlay;
    }

    core::Color normal;
    core::Color hover;
    core::Color pressed;
    core::Color text;
    core::Color icon;
    core::Border border;
    core::Shadow shadow;
    float radius = 16.0f;
    float opacity = 1.0f;
    float pressScale = 0.965f;
};

class ButtonBuilder {
public:
    ButtonBuilder(core::dsl::Ui& ui, std::string id)
        : ui_(ui), id_(std::move(id)) {}

    ButtonBuilder& x(float value) { x_ = value; hasX_ = true; return *this; }
    ButtonBuilder& y(float value) { y_ = value; hasY_ = true; return *this; }
    ButtonBuilder& position(float xValue, float yValue) { return x(xValue).y(yValue); }
    ButtonBuilder& size(float width, float height) { width_ = width; height_ = height; return *this; }
    ButtonBuilder& scale(float value) { scale_ = value; return *this; }
    ButtonBuilder& text(const std::string& value) { text_ = value; return *this; }
    ButtonBuilder& icon(unsigned int codepoint) { icon_ = core::dsl::utf8(codepoint); return *this; }
    ButtonBuilder& icon(const std::string& value) { icon_ = value; return *this; }
    ButtonBuilder& fontSize(float value) { fontSize_ = value; return *this; }
    ButtonBuilder& iconSize(float value) { iconSize_ = value; return *this; }
    ButtonBuilder& textColor(const core::Color& value) { style_.text = value; return *this; }
    ButtonBuilder& iconColor(const core::Color& value) { style_.icon = value; return *this; }
    ButtonBuilder& style(const ButtonStyle& value) { style_ = value; return *this; }
    ButtonBuilder& theme(const theme::ThemeColorTokens& tokens, bool primary = true) {
        style_ = ButtonStyle(tokens, primary);
        metrics_ = tokens.metrics;
        return *this;
    }
    ButtonBuilder& radius(float value) { style_.radius = value; return *this; }
    ButtonBuilder& opacity(float value) { style_.opacity = std::clamp(value, 0.0f, 1.0f); return *this; }
    ButtonBuilder& disabled(bool value = true) { disabled_ = value; return *this; }
    ButtonBuilder& preserveFocusOnPress(bool value = true) { preserveFocusOnPress_ = value; return *this; }
    ButtonBuilder& translate(float x, float y) { translateX_ = x; translateY_ = y; return *this; }
    ButtonBuilder& translateX(float value) { translateX_ = value; return *this; }
    ButtonBuilder& translateY(float value) { translateY_ = value; return *this; }
    ButtonBuilder& pressScale(float value) { style_.pressScale = std::clamp(value, 0.80f, 1.0f); return *this; }
    ButtonBuilder& border(float width, const core::Color& color) { style_.border = {width, color}; return *this; }
    ButtonBuilder& shadow(float blur, float offsetX, float offsetY, const core::Color& color) {
        style_.shadow = {true, {offsetX, offsetY}, blur, 0.0f, color};
        return *this;
    }
    ButtonBuilder& colors(const core::Color& normal, const core::Color& hover, const core::Color& pressed) {
        style_.normal = normal;
        style_.hover = hover;
        style_.pressed = pressed;
        return *this;
    }
    ButtonBuilder& transition(const core::Transition& value) { transition_ = value; return *this; }
    ButtonBuilder& transition(float duration, core::Ease ease = core::Ease::OutCubic) {
        transition_ = core::Transition::make(duration, ease);
        return *this;
    }
    ButtonBuilder& onClick(std::function<void()> callback) { onClick_ = std::move(callback); return *this; }
    ButtonBuilder& onPress(std::function<void()> callback) { onPress_ = std::move(callback); return *this; }
    ButtonBuilder& onRelease(std::function<void()> callback) { onRelease_ = std::move(callback); return *this; }
    ButtonBuilder& onFrame(std::function<void(float)> callback) { onFrame_ = std::move(callback); return *this; }
    ButtonBuilder& onContextMenu(std::function<void(const core::PointerEvent&, const core::Rect&)> callback) {
        onContextMenu_ = std::move(callback);
        return *this;
    }

    void build() {
        const float w = width_ * scale_;
        const float h = height_ * scale_;
        const float font = fontSize_ > 0.0f ? fontSize_ * scale_ : h * 0.46f;
        const float iconFont = iconSize_ > 0.0f ? iconSize_ * scale_ : font * 0.92f;
        const bool hasIcon = !icon_.empty();
        const bool hasText = !text_.empty();
        const float iconWidth = hasIcon ? iconFont * 1.15f : 0.0f;
        const float gap = hasIcon && hasText ? std::max(metrics_.spacing.small * scale_, h * 0.12f) : 0.0f;
        const float labelWidth = hasIcon && hasText
            ? std::max(0.0f, w - iconWidth - gap - metrics_.spacing.section * 2.0f * scale_)
            : w;
        core::Border border = style_.border;
        border.width *= scale_;

        core::Shadow shadow = style_.shadow;
        shadow.offset.x *= scale_;
        shadow.offset.y *= scale_;
        shadow.blur *= scale_;
        shadow.spread *= scale_;
        core::Color textColor = style_.text;
        core::Color iconColor = style_.icon;
        textColor.a *= style_.opacity;
        iconColor.a *= style_.opacity;
        const std::function<void()> onPress = onPress_;
        const std::function<void()> onRelease = onRelease_;

        auto root = ui_.stack(id_)
            .size(w, h)
            .visualStateFrom(id_ + ".bg", style_.pressScale);
        if (hasX_) {
            root.x(x_);
        }
        if (hasY_) {
            root.y(y_);
        }
        root.content([&] {
                auto bg = ui_.rect(id_ + ".bg")
                    .size(w, h)
                    .states(style_.normal, style_.hover, style_.pressed)
                    .radius(style_.radius * scale_)
                    .opacity(style_.opacity)
                    .border(border)
                    .shadow(shadow)
                    .translate(translateX_, translateY_)
                    .transition(transition_)
                    .disabled(disabled_)
                    .preserveFocusOnPress(preserveFocusOnPress_)
                    .onClick(onClick_)
                    .onContextMenu(onContextMenu_);
                if (onPress) {
                    bg.onPress([onPress](const core::PointerEvent&, const core::Rect&) { onPress(); });
                }
                if (onRelease) {
                    bg.onRelease([onRelease](const core::PointerEvent&, const core::Rect&) { onRelease(); });
                }
                if (onFrame_) {
                    bg.onFrame(onFrame_);
                }
                bg.build();

                ui_.row(id_ + ".content")
                    .size(w, h)
                    .gap(gap)
                    .justifyContent(core::Align::CENTER)
                    .alignItems(core::Align::CENTER)
                    .content([&] {
                        if (hasIcon) {
                            ui_.text(id_ + ".icon")
                                .size(iconWidth, h)
                                .icon(icon_)
                                .fontSize(iconFont)
                                .lineHeight(iconFont)
                                .color(iconColor)
                                .horizontalAlign(core::HorizontalAlign::Center)
                                .verticalAlign(core::VerticalAlign::Center)
                                .transition(transition_)
                                .build();
                        }

                        if (hasText) {
                            ui_.text(id_ + ".text")
                                .size(labelWidth, h)
                                .text(text_)
                                .fontSize(font)
                                .lineHeight(font)
                                .color(textColor)
                                .horizontalAlign(hasIcon ? core::HorizontalAlign::Left : core::HorizontalAlign::Center)
                                .verticalAlign(core::VerticalAlign::Center)
                                .transition(transition_)
                                .build();
                        }
                    })
                    .build();
            })
            .build();
    }

private:
    core::dsl::Ui& ui_;
    std::string id_;
    std::string text_ = "Button";
    std::string icon_;
    ButtonStyle style_;
    theme::ThemeMetricTokens metrics_;
    core::Transition transition_;
    std::function<void()> onClick_;
    std::function<void()> onPress_;
    std::function<void()> onRelease_;
    std::function<void(float)> onFrame_;
    std::function<void(const core::PointerEvent&, const core::Rect&)> onContextMenu_;
    float width_ = 200.0f;
    float height_ = 54.0f;
    float scale_ = 1.0f;
    float fontSize_ = 0.0f;
    float iconSize_ = 0.0f;
    float translateX_ = 0.0f;
    float translateY_ = 0.0f;
    float x_ = 0.0f;
    float y_ = 0.0f;
    bool disabled_ = false;
    bool preserveFocusOnPress_ = false;
    bool hasX_ = false;
    bool hasY_ = false;
};

inline ButtonBuilder button(core::dsl::Ui& ui, const std::string& id) {
    return ButtonBuilder(ui, id);
}

} // namespace components



namespace components {

struct CheckboxStyle {
    CheckboxStyle() : CheckboxStyle(theme::dark()) {}

    explicit CheckboxStyle(const theme::ThemeColorTokens& tokens) {
        box = tokens.surface;
        boxHover = tokens.surfaceHover;
        checked = tokens.primary;
        checkedHover = theme::buttonHover(tokens, checked);
        checkedPressed = theme::buttonPressed(tokens, checked);
        boxPressed = theme::buttonPressed(tokens, boxHover);
        border = tokens.border;
        mark = theme::color(1.0f, 1.0f, 1.0f, 1.0f);
        text = tokens.text;
        rowHover = theme::withAlpha(tokens.text, tokens.dark ? 0.06f : 0.05f);
        rowPressed = theme::withAlpha(tokens.text, tokens.dark ? 0.10f : 0.08f);
        radius = tokens.metrics.radius.small;
    }

    core::Color box;
    core::Color boxHover;
    core::Color boxPressed;
    core::Color checked;
    core::Color checkedHover;
    core::Color checkedPressed;
    core::Color border;
    core::Color mark;
    core::Color text;
    core::Color rowHover;
    core::Color rowPressed;
    float radius = 6.0f;
};

class CheckboxBuilder {
public:
    CheckboxBuilder(core::dsl::Ui& ui, std::string id)
        : ui_(ui), id_(std::move(id)) {}

    CheckboxBuilder& size(float width, float height) { width_ = width; height_ = height; return *this; }
    CheckboxBuilder& checked(bool value) { checked_ = value; return *this; }
    CheckboxBuilder& bind(eui::Signal<bool>& signal) {
        checked(signal.get());
        onChange([&signal](bool value) { signal.set(value); });
        return *this;
    }
    CheckboxBuilder& text(std::string value) { text_ = std::move(value); return *this; }
    CheckboxBuilder& fontSize(float value) { fontSize_ = std::max(1.0f, value); return *this; }
    CheckboxBuilder& boxSize(float value) { boxSize_ = std::max(10.0f, value); return *this; }
    CheckboxBuilder& style(const CheckboxStyle& value) { style_ = value; return *this; }
    CheckboxBuilder& theme(const theme::ThemeColorTokens& tokens) {
        style_ = CheckboxStyle(tokens);
        metrics_ = tokens.metrics;
        return *this;
    }
    CheckboxBuilder& transition(const core::Transition& value) { transition_ = value; return *this; }
    CheckboxBuilder& transition(float duration, core::Ease ease = core::Ease::OutCubic) {
        transition_ = core::Transition::make(duration, ease);
        return *this;
    }
    CheckboxBuilder& onChange(std::function<void(bool)> callback) { onChange_ = std::move(callback); return *this; }

    void build() {
        const float fontSize = fontSize_ > 0.0f ? fontSize_ : metrics_.typography.control;
        const float boxSize = boxSize_ > 0.0f ? boxSize_ : metrics_.control.indicator;
        const float gap = gap_ > 0.0f ? gap_ : metrics_.spacing.control;
        const float box = std::min(boxSize, height_);
        const float boxY = (height_ - box) * 0.5f;
        const float labelX = box + gap;
        const float horizontalInset = metrics_.spacing.control;
        const float contentX = horizontalInset;
        const float labelWidth = std::max(0.0f, width_ - labelX - horizontalInset);
        const float labelLineHeight = fontSize;
        const float labelY = std::max(0.0f, (height_ - labelLineHeight) * 0.5f);
        const float markThickness = std::max(2.0f, box * 0.12f);
        const float markAngleCos = 0.7109f;
        const float markAngleSin = 0.7033f;
        const float markShort = box * 0.28f;
        const float markLong = box * 0.46f;
        const float markHalf = markThickness * 0.5f;
        const float markStartX = box * 0.26f;
        const float markStartY = box * 0.55f;
        const float markCornerX = markStartX + markShort * markAngleCos;
        const float markCornerY = markStartY + markShort * markAngleSin;
        const float markEndX = markCornerX + markLong * markAngleCos;
        const float markEndY = markCornerY - markLong * markAngleSin;
        const core::Vec2 shortNormal{-markAngleSin * markHalf, markAngleCos * markHalf};
        const core::Vec2 longNormal{markAngleSin * markHalf, markAngleCos * markHalf};
        const core::Vec2 outerCorner{markCornerX, markCornerY + markHalf / markAngleCos};
        const core::Vec2 innerCorner{markCornerX, markCornerY - markHalf / markAngleCos};
        const core::Vec2 markStart{markStartX, markStartY};
        const core::Vec2 markEnd{markEndX, markEndY};
        const std::vector<core::Vec2> markShortPoints{
            {markStart.x + shortNormal.x, markStart.y + shortNormal.y},
            outerCorner,
            innerCorner,
            {markStart.x - shortNormal.x, markStart.y - shortNormal.y}
        };
        const std::vector<core::Vec2> markLongPoints{
            outerCorner,
            {markEnd.x + longNormal.x, markEnd.y + longNormal.y},
            {markEnd.x - longNormal.x, markEnd.y - longNormal.y},
            innerCorner
        };
        core::Transition markTransition = transition_;
        markTransition.durationSeconds = 0.12f;
        markTransition.ease = core::Ease::OutCubic;
        const float hitWidth = text_.empty()
            ? box + horizontalInset * 2.0f
            : std::min(width_, labelX + textWidth(text_, fontSize) + horizontalInset * 2.0f);
        const core::Color idle = checked_ ? style_.checked : style_.box;
        const core::Color hover = checked_ ? style_.checkedHover : style_.boxHover;
        const core::Color pressed = checked_ ? style_.checkedPressed : style_.boxPressed;
        const bool nextChecked = !checked_;
        const std::function<void(bool)> onChange = onChange_;

        ui_.stack(id_)
            .size(width_, height_)
            .content([&] {
                ui_.rect(id_ + ".hit")
                    .size(hitWidth, height_)
                    .states(theme::color(0.0f, 0.0f, 0.0f, 0.0f), style_.rowHover, style_.rowPressed)
                    .radius(std::max(metrics_.radius.small, height_ * 0.20f))
                    .transition(transition_)
                    .onClick([onChange, nextChecked] {
                        if (onChange) {
                            onChange(nextChecked);
                        }
                    })
                    .build();

                ui_.rect(id_ + ".box")
                    .x(contentX)
                    .y(boxY)
                    .size(box, box)
                    .color(idle)
                    .radius(style_.radius)
                    .border(1.5f, checked_ ? style_.checked : style_.border)
                    .transition(transition_)
                    .animate(core::AnimProperty::Color | core::AnimProperty::Border)
                    .build();

                ui_.stack(id_ + ".mark.clip")
                    .x(contentX)
                    .y(boxY)
                    .size(box, box)
                    .clip()
                    .content([&] {
                        ui_.polygon(id_ + ".mark.short")
                            .size(box, box)
                            .points(markShortPoints)
                            .color(style_.mark)
                            .opacity(checked_ ? 1.0f : 0.0f)
                            .transition(markTransition)
                            .animate(core::AnimProperty::Opacity)
                            .build();

                        ui_.polygon(id_ + ".mark.long")
                            .size(box, box)
                            .points(markLongPoints)
                            .color(style_.mark)
                            .opacity(checked_ ? 1.0f : 0.0f)
                            .transition(markTransition)
                            .animate(core::AnimProperty::Opacity)
                            .build();
                    })
                    .build();

                if (!text_.empty()) {
                    ui_.text(id_ + ".label")
                        .x(contentX + labelX)
                        .y(labelY)
                        .size(labelWidth, labelLineHeight)
                        .text(text_)
                        .fontSize(fontSize)
                        .lineHeight(labelLineHeight)
                        .color(style_.text)
                        .verticalAlign(core::VerticalAlign::Top)
                        .build();
                }
            })
            .build();
    }

private:
    static float textWidth(const std::string& value, float fontSize) {
        return core::TextPrimitive::measureTextWidth(value, {}, fontSize, 400);
    }

    core::dsl::Ui& ui_;
    std::string id_;
    CheckboxStyle style_;
    theme::ThemeMetricTokens metrics_;
    core::Transition transition_ = core::Transition::make(0.16f, core::Ease::OutCubic);
    std::function<void(bool)> onChange_;
    std::string text_;
    bool checked_ = false;
    float width_ = 180.0f;
    float height_ = 30.0f;
    float boxSize_ = 0.0f;
    float gap_ = 0.0f;
    float fontSize_ = 0.0f;
};

inline CheckboxBuilder checkbox(core::dsl::Ui& ui, const std::string& id) {
    return CheckboxBuilder(ui, id);
}

} // namespace components



namespace components::input_detail {

struct InputModel {
    struct TextLine {
        int start = 0;
        int end = 0;
        bool hardBreakAfter = false;
        core::TextPrimitive::TextMetrics metrics;
    };

    struct TextSelectionRect {
        float x = 0.0f;
        float y = 0.0f;
        float width = 0.0f;
        float height = 0.0f;
    };

    struct EditSnapshot {
        std::string text;
        int cursor = 0;
        int selectionStart = 0;
        int selectionEnd = 0;
    };

    struct InputState {
        std::string text;
        std::string compositionText;
        int cursor = 0;
        int selectionStart = 0;
        int selectionEnd = 0;
        int dragAnchor = 0;
        bool selecting = false;
        bool hasPreferredCursorX = false;
        bool followCaret = true;
        float preferredCursorX = 0.0f;
        float horizontalScroll = 0.0f;
        float verticalScroll = 0.0f;
        unsigned long long textRevision = 0;
        unsigned long long compositionRevision = 0;
        core::Rect lastBounds;
        unsigned long long cachedTextRevision = static_cast<unsigned long long>(-1);
        std::string cachedFontFamily;
        float cachedFontSize = 0.0f;
        float cachedViewportWidth = -1.0f;
        bool cachedMultiline = false;
        core::TextPrimitive::TextMetrics cachedMetrics;
        std::vector<TextLine> cachedLines;
        float cachedTextWidth = 0.0f;
        bool layoutCacheValid = false;
        std::vector<EditSnapshot> undoStack;
        std::vector<EditSnapshot> redoStack;
    };

    struct InputLayout {
        using Line = TextLine;
        using SelectionRect = TextSelectionRect;

        core::TextPrimitive::TextMetrics metrics;
        const std::vector<Line>* lines = nullptr;
        std::vector<SelectionRect> selectionRects;
        float viewportWidth = 0.0f;
        float viewportHeight = 0.0f;
        float controlWidth = 0.0f;
        float inset = 0.0f;
        float textTop = 0.0f;
        float lineHeight = 0.0f;
        float scroll = 0.0f;
        float textWidth = 0.0f;
        float contentHeight = 0.0f;
        float cursorPixel = 0.0f;
        float cursorX = 0.0f;
        float cursorY = 0.0f;
        float visibleTextWidth = 0.0f;
        float maxVerticalScroll = 0.0f;
        int selectionStart = 0;
        int selectionEnd = 0;
        int cursorLine = 0;
        bool multiline = false;
        float clippedSelectionX = 0.0f;
        float clippedSelectionWidth = 0.0f;

        static InputLayout build(InputState& state,
                                 float viewportWidth,
                                 float viewportHeight,
                                 float controlWidth,
                                 float inset,
                                 float textTop,
                                 float lineHeight,
                                 const std::string& fontFamily,
                                 float fontSize,
                                 bool multiline) {
            InputLayout layout;
            layout.viewportWidth = viewportWidth;
            layout.viewportHeight = viewportHeight;
            layout.controlWidth = controlWidth;
            layout.inset = inset;
            layout.textTop = textTop;
            layout.lineHeight = lineHeight;
            layout.multiline = multiline;
            ensureLayoutCache(state, fontFamily, fontSize, viewportWidth, multiline);
            layout.lines = &state.cachedLines;

            if (multiline) {
                layout.cursorLine = layout.lineIndexFor(state.cursor);
                const Line& cursorLine = layout.lineList()[static_cast<size_t>(layout.cursorLine)];
                layout.metrics = cursorLine.metrics;
                state.horizontalScroll = 0.0f;
                layout.scroll = 0.0f;
                layout.textWidth = state.cachedTextWidth;
                layout.contentHeight = static_cast<float>(layout.lineList().size()) * lineHeight;
                layout.cursorPixel = caretX(cursorLine.metrics, state.cursor - cursorLine.start);
                layout.cursorX = inset + layout.cursorPixel;
                layout.maxVerticalScroll = std::max(0.0f, layout.contentHeight - viewportHeight);
                state.verticalScroll = std::clamp(state.verticalScroll, 0.0f, layout.maxVerticalScroll);
                if (state.followCaret) {
                    syncVerticalScroll(state, layout.cursorLine, lineHeight, viewportHeight);
                }
                state.verticalScroll = std::clamp(state.verticalScroll, 0.0f, layout.maxVerticalScroll);
                layout.currentVerticalScroll = state.verticalScroll;
                layout.cursorY = textTop + static_cast<float>(layout.cursorLine) * lineHeight - state.verticalScroll;
                layout.visibleTextWidth = viewportWidth;
            } else {
                layout.metrics = state.cachedMetrics;
                syncScroll(state, viewportWidth, layout.metrics, fontSize);
                state.verticalScroll = 0.0f;
                layout.cursorLine = 0;
                layout.scroll = state.horizontalScroll;
                layout.textWidth = layout.metrics.width;
                layout.contentHeight = lineHeight;
                layout.cursorPixel = caretX(layout.metrics, state.cursor);
                layout.cursorX = inset + layout.cursorPixel - layout.scroll;
                layout.cursorY = textTop;
                layout.currentVerticalScroll = 0.0f;
                layout.visibleTextWidth = std::max(viewportWidth, layout.textWidth + 24.0f);
            }

            const auto selection = selectionRange(state);
            layout.selectionStart = selection.first;
            layout.selectionEnd = selection.second;
            layout.buildSelectionRects(selection.first, selection.second);
            return layout;
        }

        const std::vector<Line>& lineList() const {
            static const std::vector<Line> emptyLines;
            return lines ? *lines : emptyLines;
        }

        float xFor(int byteIndex) const {
            const int lineIndex = lineIndexFor(byteIndex);
            const Line& line = lineList()[static_cast<size_t>(lineIndex)];
            return caretX(line.metrics, byteIndex - line.start);
        }

        float clampedCursorX() const {
            return std::clamp(cursorX, inset, std::max(inset, controlWidth - inset));
        }

        int cursorFromPointer(double pointerX, double pointerY, const core::Rect& bounds, float width, float inputInset) const {
            const float scale = width > 0.0f ? bounds.width / width : 1.0f;
            const float localX = static_cast<float>((pointerX - bounds.x) / std::max(0.001f, scale));
            const float localY = static_cast<float>((pointerY - bounds.y) / std::max(0.001f, scale));
            const int lineIndex = multiline ? lineIndexFromY(localY + currentVerticalScroll) : 0;
            return closestCaret(lineIndex, localX - inputInset + scroll);
        }

        int closestCaret(int lineIndex, float targetX) const {
            const std::vector<Line>& lineListRef = lineList();
            if (lineListRef.empty()) {
                return 0;
            }
            const Line& line = lineListRef[static_cast<size_t>(std::clamp(lineIndex, 0, static_cast<int>(lineListRef.size()) - 1))];
            if (line.metrics.byteIndices.empty() || line.metrics.caretX.empty()) {
                return line.start;
            }
            const size_t count = std::min(line.metrics.byteIndices.size(), line.metrics.caretX.size());
            int bestIndex = line.metrics.byteIndices.front();
            float bestDistance = std::fabs(targetX - line.metrics.caretX.front());
            for (size_t i = 1; i < count; ++i) {
                const float distance = std::fabs(targetX - line.metrics.caretX[i]);
                if (distance < bestDistance) {
                    bestDistance = distance;
                    bestIndex = line.metrics.byteIndices[i];
                }
            }
            return line.start + bestIndex;
        }

        int lineIndexFor(int byteIndex) const {
            const std::vector<Line>& lineListRef = lineList();
            if (lineListRef.empty()) {
                return 0;
            }
            const auto it = std::upper_bound(
                lineListRef.begin(),
                lineListRef.end(),
                byteIndex,
                [](int value, const Line& line) {
                    return value < line.start;
                });
            int index = it == lineListRef.begin()
                ? 0
                : static_cast<int>(std::distance(lineListRef.begin(), it)) - 1;
            index = std::clamp(index, 0, static_cast<int>(lineListRef.size()) - 1);
            if (index + 1 < static_cast<int>(lineListRef.size()) &&
                !lineListRef[static_cast<size_t>(index)].hardBreakAfter &&
                byteIndex >= lineListRef[static_cast<size_t>(index)].end) {
                ++index;
            }
            return std::clamp(index, 0, static_cast<int>(lineListRef.size()) - 1);
        }

        int lineIndexFromY(float localY) const {
            const std::vector<Line>& lineListRef = lineList();
            if (lineListRef.empty() || lineHeight <= 0.0f) {
                return 0;
            }
            const int line = static_cast<int>(std::floor((localY - textTop) / lineHeight));
            return std::clamp(line, 0, static_cast<int>(lineListRef.size()) - 1);
        }

        float currentVerticalScroll = 0.0f;

        void buildSelectionRects(int startIndex, int endIndex) {
            const std::vector<Line>& lineListRef = lineList();
            if (startIndex == endIndex || lineListRef.empty()) {
                return;
            }
            if (startIndex > endIndex) {
                std::swap(startIndex, endIndex);
            }

            const float clipLeft = inset;
            const float clipRight = std::max(inset, controlWidth - inset);
            const int firstSelectedLine = lineIndexFor(startIndex);
            const int lastSelectedLine = lineIndexFor(std::max(startIndex, endIndex - 1));
            const int firstVisibleLine = lineIndexFromY(textTop + currentVerticalScroll - lineHeight);
            const int lastVisibleLine = lineIndexFromY(textTop + currentVerticalScroll + viewportHeight + lineHeight);
            const int firstLine = std::max(firstSelectedLine, firstVisibleLine);
            const int lastLine = std::min(lastSelectedLine, lastVisibleLine);
            for (int lineIndex = firstLine; lineIndex <= lastLine; ++lineIndex) {
                const size_t i = static_cast<size_t>(lineIndex);
                const Line& line = lineListRef[i];
                const int selectableEnd = line.end + (line.hardBreakAfter ? 1 : 0);

                const int lineStart = std::clamp(startIndex, line.start, line.end);
                const int lineEnd = std::clamp(endIndex, line.start, line.end);
                const bool selectionContinuesPastLine = endIndex > line.end && startIndex <= line.end;
                if (lineStart == lineEnd && !selectionContinuesPastLine) {
                    continue;
                }

                const bool coversWholeLine = startIndex <= line.start && endIndex >= selectableEnd;
                const float startX = coversWholeLine ? 0.0f : caretX(line.metrics, lineStart - line.start);
                const float endX = selectionContinuesPastLine
                    ? (line.hardBreakAfter || coversWholeLine ? viewportWidth : std::max(line.metrics.width, startX + 1.0f))
                    : caretX(line.metrics, lineEnd - line.start);
                const float rawX = inset + startX - scroll;
                const float rawRight = inset + endX - scroll;
                const float clippedX = std::clamp(rawX, clipLeft, clipRight);
                const float clippedRight = std::clamp(rawRight, clipLeft, clipRight);
                const float width = std::max(1.0f, clippedRight - clippedX);
                const float y = textTop + static_cast<float>(i) * lineHeight - currentVerticalScroll;
                const float height = i + 1 < lineListRef.size() ? lineHeight + 1.0f : lineHeight;
                if (y + height < textTop || y > textTop + viewportHeight) {
                    continue;
                }
                selectionRects.push_back({clippedX, y, width, height});
            }
        }
    };

    static std::string filteredText(const std::string& input, bool multiline) {
        std::string output;
        for (char ch : input) {
            if (ch == '\r' || (!multiline && ch == '\n')) {
                continue;
            }
            output.push_back(ch);
        }
        return output;
    }

    static int clampUtf8Boundary(const std::string& value, int index) {
        int out = std::clamp(index, 0, static_cast<int>(value.size()));
        while (out > 0 && out < static_cast<int>(value.size()) &&
               (static_cast<unsigned char>(value[static_cast<std::size_t>(out)]) & 0xC0) == 0x80) {
            --out;
        }
        return out;
    }

    static std::pair<int, int> selectionRange(const InputState& state) {
        return {std::min(state.selectionStart, state.selectionEnd), std::max(state.selectionStart, state.selectionEnd)};
    }

    static bool hasTextSelection(const InputState& state) {
        return state.selectionStart != state.selectionEnd;
    }

    static void clearSelection(InputState& state) {
        state.selectionStart = state.cursor;
        state.selectionEnd = state.cursor;
        state.dragAnchor = state.cursor;
    }

    static EditSnapshot snapshotFor(const InputState& state) {
        return {state.text, state.cursor, state.selectionStart, state.selectionEnd};
    }

    static bool sameSnapshot(const EditSnapshot& snapshot, const InputState& state) {
        return snapshot.text == state.text &&
               snapshot.cursor == state.cursor &&
               snapshot.selectionStart == state.selectionStart &&
               snapshot.selectionEnd == state.selectionEnd;
    }

    static void restoreSnapshot(InputState& state, const EditSnapshot& snapshot) {
        state.text = snapshot.text;
        state.cursor = clampUtf8Boundary(state.text, snapshot.cursor);
        state.selectionStart = clampUtf8Boundary(state.text, snapshot.selectionStart);
        state.selectionEnd = clampUtf8Boundary(state.text, snapshot.selectionEnd);
        state.dragAnchor = state.cursor;
        state.hasPreferredCursorX = false;
        ++state.textRevision;
    }

    static void pushUndoState(InputState& state) {
        if (!state.undoStack.empty() && sameSnapshot(state.undoStack.back(), state)) {
            state.redoStack.clear();
            return;
        }
        constexpr size_t kMaxUndoDepth = 128;
        state.undoStack.push_back(snapshotFor(state));
        if (state.undoStack.size() > kMaxUndoDepth) {
            state.undoStack.erase(state.undoStack.begin());
        }
        state.redoStack.clear();
    }

    static bool undoEdit(InputState& state) {
        if (state.undoStack.empty()) {
            return false;
        }
        state.redoStack.push_back(snapshotFor(state));
        const EditSnapshot snapshot = state.undoStack.back();
        state.undoStack.pop_back();
        restoreSnapshot(state, snapshot);
        return true;
    }

    static bool redoEdit(InputState& state) {
        if (state.redoStack.empty()) {
            return false;
        }
        state.undoStack.push_back(snapshotFor(state));
        const EditSnapshot snapshot = state.redoStack.back();
        state.redoStack.pop_back();
        restoreSnapshot(state, snapshot);
        return true;
    }

    static void eraseSelection(InputState& state) {
        const auto range = selectionRange(state);
        if (range.first == range.second) {
            return;
        }
        state.text.erase(static_cast<std::size_t>(range.first), static_cast<std::size_t>(range.second - range.first));
        ++state.textRevision;
        state.cursor = range.first;
        clearSelection(state);
    }

    static void insertAtCursor(InputState& state, const std::string& value) {
        if (value.empty()) {
            return;
        }
        if (hasTextSelection(state)) {
            eraseSelection(state);
        }
        state.text.insert(static_cast<std::size_t>(state.cursor), value);
        ++state.textRevision;
        state.cursor += static_cast<int>(value.size());
        state.hasPreferredCursorX = false;
        clearSelection(state);
    }

    static void moveCursor(InputState& state,
                           int direction,
                           bool keepSelection,
                           const std::string& fontFamily,
                           float fontSize,
                           bool multiline,
                           float viewportWidth) {
        const int previous = state.cursor;
        if (!keepSelection && hasTextSelection(state)) {
            const auto range = selectionRange(state);
            state.cursor = direction < 0 ? range.first : range.second;
            state.hasPreferredCursorX = false;
            clearSelection(state);
            return;
        }
        state.cursor = direction < 0
            ? prevCursorIndex(state, fontFamily, fontSize, multiline, viewportWidth)
            : nextCursorIndex(state, fontFamily, fontSize, multiline, viewportWidth);
        state.hasPreferredCursorX = false;
        if (keepSelection) {
            if (!hasTextSelection(state)) {
                state.selectionStart = previous;
            }
            state.selectionEnd = state.cursor;
        } else {
            clearSelection(state);
        }
    }

    static void moveCursorToLineEdge(InputState& state,
                                     bool toEnd,
                                     bool keepSelection,
                                     const std::string& fontFamily,
                                     float fontSize,
                                     float viewportWidth) {
        const std::vector<InputLayout::Line>& lines = cachedLines(state, fontFamily, fontSize, viewportWidth, true);
        if (lines.empty()) {
            moveCursorTo(state, toEnd ? static_cast<int>(state.text.size()) : 0, keepSelection);
            return;
        }

        const int lineIndex = lineIndexFor(lines, state.cursor);
        const InputLayout::Line& line = lines[static_cast<size_t>(lineIndex)];
        moveCursorTo(state, toEnd ? line.end : line.start, keepSelection);
    }

    static void moveCursorVertical(InputState& state,
                                   int direction,
                                   bool keepSelection,
                                   const std::string& fontFamily,
                                   float fontSize,
                                   float viewportWidth,
                                   float viewportHeight) {
        const std::vector<InputLayout::Line>& lines = cachedLines(state, fontFamily, fontSize, viewportWidth, true);
        if (lines.empty()) {
            return;
        }

        auto xFor = [&](int byteIndex) {
            const int lineIndex = lineIndexFor(lines, byteIndex);
            const InputLayout::Line& line = lines[static_cast<size_t>(lineIndex)];
            return caretX(line.metrics, byteIndex - line.start);
        };

        auto closestOnLine = [&](int lineIndex, float targetX) {
            const InputLayout::Line& line = lines[static_cast<size_t>(std::clamp(lineIndex, 0, static_cast<int>(lines.size()) - 1))];
            if (line.metrics.byteIndices.empty() || line.metrics.caretX.empty()) {
                return line.start;
            }
            const size_t count = std::min(line.metrics.byteIndices.size(), line.metrics.caretX.size());
            int bestIndex = line.metrics.byteIndices.front();
            float bestDistance = std::fabs(targetX - line.metrics.caretX.front());
            for (size_t i = 1; i < count; ++i) {
                const float distance = std::fabs(targetX - line.metrics.caretX[i]);
                if (distance < bestDistance) {
                    bestDistance = distance;
                    bestIndex = line.metrics.byteIndices[i];
                }
            }
            return line.start + bestIndex;
        };

        const int previous = state.cursor;
        const int currentLine = lineIndexFor(lines, state.cursor);
        const int nextLine = std::clamp(currentLine + direction, 0, static_cast<int>(lines.size()) - 1);
        if (nextLine == currentLine) {
            return;
        }

        if (!state.hasPreferredCursorX) {
            state.preferredCursorX = xFor(state.cursor);
            state.hasPreferredCursorX = true;
        }
        state.cursor = clampUtf8Boundary(state.text, closestOnLine(nextLine, state.preferredCursorX));
        syncVerticalScroll(state, nextLine, fontSize, viewportHeight);

        if (keepSelection) {
            if (!hasTextSelection(state)) {
                state.selectionStart = previous;
            }
            state.selectionEnd = state.cursor;
        } else {
            clearSelection(state);
        }
    }

    static void moveCursorTo(InputState& state, int position, bool keepSelection) {
        const int previous = state.cursor;
        state.cursor = clampUtf8Boundary(state.text, position);
        state.hasPreferredCursorX = false;
        if (keepSelection) {
            if (!hasTextSelection(state)) {
                state.selectionStart = previous;
            }
            state.selectionEnd = state.cursor;
        } else {
            clearSelection(state);
        }
    }

    static void copySelection(const InputState& state) {
        if (!hasTextSelection(state)) {
            return;
        }
        const auto range = selectionRange(state);
        const std::string selected = state.text.substr(static_cast<std::size_t>(range.first), static_cast<std::size_t>(range.second - range.first));
        core::window::setClipboardText(selected);
    }

    static core::TextPrimitive::TextMetrics measureMetrics(const std::string& value, const std::string& fontFamily, float fontSize) {
        return core::TextPrimitive::measureTextMetrics(value, fontFamily, fontSize, 400);
    }

    static bool sameLayoutCacheKey(const InputState& state,
                                   const std::string& fontFamily,
                                   float fontSize,
                                   float viewportWidth,
                                   bool multiline) {
        return state.layoutCacheValid &&
               state.cachedTextRevision == state.textRevision &&
               state.cachedFontFamily == fontFamily &&
               std::fabs(state.cachedFontSize - fontSize) < 0.001f &&
               std::fabs(state.cachedViewportWidth - viewportWidth) < 0.001f &&
               state.cachedMultiline == multiline;
    }

    static void ensureLayoutCache(InputState& state,
                                  const std::string& fontFamily,
                                  float fontSize,
                                  float viewportWidth,
                                  bool multiline) {
        if (sameLayoutCacheKey(state, fontFamily, fontSize, viewportWidth, multiline)) {
            return;
        }

        state.cachedTextRevision = state.textRevision;
        state.cachedFontFamily = fontFamily;
        state.cachedFontSize = fontSize;
        state.cachedViewportWidth = viewportWidth;
        state.cachedMultiline = multiline;
        state.cachedMetrics = measureMetrics(state.text, fontFamily, fontSize);
        if (multiline) {
            state.cachedLines = measureLines(state.text, fontFamily, fontSize, viewportWidth);
            state.cachedTextWidth = 0.0f;
            for (const TextLine& line : state.cachedLines) {
                state.cachedTextWidth = std::max(state.cachedTextWidth, line.metrics.width);
            }
        } else {
            state.cachedLines = {{0, static_cast<int>(state.text.size()), false, state.cachedMetrics}};
            state.cachedTextWidth = state.cachedMetrics.width;
        }
        state.layoutCacheValid = true;
    }

    static const std::vector<InputLayout::Line>& cachedLines(InputState& state,
                                                            const std::string& fontFamily,
                                                            float fontSize,
                                                            float viewportWidth,
                                                            bool multiline) {
        ensureLayoutCache(state, fontFamily, fontSize, viewportWidth, multiline);
        return state.cachedLines;
    }

    static const core::TextPrimitive::TextMetrics& cachedMetrics(InputState& state,
                                                                 const std::string& fontFamily,
                                                                 float fontSize,
                                                                 float viewportWidth) {
        ensureLayoutCache(state, fontFamily, fontSize, viewportWidth, false);
        return state.cachedMetrics;
    }

    static std::vector<InputLayout::Line> measureLines(const std::string& value,
                                                       const std::string& fontFamily,
                                                       float fontSize,
                                                       float viewportWidth) {
        std::vector<InputLayout::Line> lines;
        int start = 0;
        while (start <= static_cast<int>(value.size())) {
            const size_t newline = value.find('\n', static_cast<size_t>(start));
            const int end = newline == std::string::npos
                ? static_cast<int>(value.size())
                : static_cast<int>(newline);
            const std::string lineText = value.substr(static_cast<size_t>(start), static_cast<size_t>(end - start));
            const core::TextPrimitive::TextMetrics metrics = measureMetrics(lineText, fontFamily, fontSize);
            if (viewportWidth <= 1.0f || metrics.byteIndices.size() <= 2 || metrics.width <= viewportWidth) {
                lines.push_back({start, end, newline != std::string::npos, metrics});
            } else {
                int segmentStart = 0;
                float segmentStartX = 0.0f;
                int previousStop = 0;
                const size_t count = std::min(metrics.byteIndices.size(), metrics.caretX.size());
                for (size_t i = 1; i < count; ++i) {
                    const int stop = metrics.byteIndices[i];
                    const float x = metrics.caretX[i];
                    if (previousStop > segmentStart && x - segmentStartX > viewportWidth) {
                        const int segmentEnd = previousStop;
                        const std::string segmentText = lineText.substr(static_cast<size_t>(segmentStart),
                                                                        static_cast<size_t>(segmentEnd - segmentStart));
                        lines.push_back({start + segmentStart, start + segmentEnd, false, measureMetrics(segmentText, fontFamily, fontSize)});
                        segmentStart = segmentEnd;
                        segmentStartX = caretX(metrics, segmentStart);
                    }
                    previousStop = stop;
                }
                if (segmentStart < static_cast<int>(lineText.size()) || lineText.empty()) {
                    const std::string segmentText = lineText.substr(static_cast<size_t>(segmentStart));
                    lines.push_back({start + segmentStart, end, newline != std::string::npos, measureMetrics(segmentText, fontFamily, fontSize)});
                }
            }
            if (newline == std::string::npos) {
                break;
            }
            start = static_cast<int>(newline) + 1;
        }
        if (lines.empty()) {
            lines.push_back({0, 0, false, measureMetrics({}, fontFamily, fontSize)});
        }
        return lines;
    }

    static int lineIndexFor(const std::vector<InputLayout::Line>& lines, int byteIndex) {
        if (lines.empty()) {
            return 0;
        }
        const auto it = std::upper_bound(
            lines.begin(),
            lines.end(),
            byteIndex,
            [](int value, const InputLayout::Line& line) {
                return value < line.start;
            });
        int index = it == lines.begin()
            ? 0
            : static_cast<int>(std::distance(lines.begin(), it)) - 1;
        index = std::clamp(index, 0, static_cast<int>(lines.size()) - 1);
        if (index + 1 < static_cast<int>(lines.size()) &&
            !lines[static_cast<size_t>(index)].hardBreakAfter &&
            byteIndex >= lines[static_cast<size_t>(index)].end) {
            ++index;
        }
        return std::clamp(index, 0, static_cast<int>(lines.size()) - 1);
    }

    static void syncVerticalScroll(InputState& state, int cursorLine, float lineHeight, float viewportHeight) {
        if (lineHeight <= 0.0f || viewportHeight <= 0.0f) {
            state.verticalScroll = 0.0f;
            return;
        }
        const float cursorTop = static_cast<float>(std::max(0, cursorLine)) * lineHeight;
        const float cursorBottom = cursorTop + lineHeight;
        if (cursorTop - state.verticalScroll < 0.0f) {
            state.verticalScroll = cursorTop;
        } else if (cursorBottom - state.verticalScroll > viewportHeight) {
            state.verticalScroll = cursorBottom - viewportHeight;
        }
        state.verticalScroll = std::max(0.0f, state.verticalScroll);
    }

    static void syncVerticalScroll(InputState& state, const InputLayout& layout, float viewportHeight) {
        syncVerticalScroll(state, layout.lineIndexFor(state.cursor), layout.lineHeight, viewportHeight);
    }

    static float caretX(const core::TextPrimitive::TextMetrics& metrics, int byteIndex) {
        if (metrics.byteIndices.empty() || metrics.caretX.empty()) {
            return 0.0f;
        }
        const auto it = std::lower_bound(metrics.byteIndices.begin(), metrics.byteIndices.end(), byteIndex);
        const size_t slot = it == metrics.byteIndices.end()
            ? metrics.caretX.size() - 1
            : static_cast<size_t>(std::distance(metrics.byteIndices.begin(), it));
        return metrics.caretX[std::min(slot, metrics.caretX.size() - 1)];
    }

    static int previousCaretIndex(const core::TextPrimitive::TextMetrics& metrics, int byteIndex) {
        if (metrics.byteIndices.empty()) {
            return 0;
        }
        const auto it = std::lower_bound(metrics.byteIndices.begin(), metrics.byteIndices.end(), byteIndex);
        if (it == metrics.byteIndices.begin()) {
            return metrics.byteIndices.front();
        }
        return *(it - 1);
    }

    static int nextCaretIndex(const core::TextPrimitive::TextMetrics& metrics, int byteIndex) {
        if (metrics.byteIndices.empty()) {
            return 0;
        }
        const auto it = std::upper_bound(metrics.byteIndices.begin(), metrics.byteIndices.end(), byteIndex);
        if (it == metrics.byteIndices.end()) {
            return metrics.byteIndices.back();
        }
        return *it;
    }

    static int previousCaretIndex(const std::vector<InputLayout::Line>& lines, int byteIndex) {
        if (lines.empty()) {
            return 0;
        }
        const int lineIndex = lineIndexFor(lines, byteIndex);
        const InputLayout::Line& line = lines[static_cast<size_t>(lineIndex)];
        if (line.hardBreakAfter && byteIndex == line.end + 1) {
            return line.end;
        }
        if (byteIndex > line.start) {
            return line.start + previousCaretIndex(line.metrics, byteIndex - line.start);
        }
        if (lineIndex <= 0) {
            return line.start;
        }
        const InputLayout::Line& previousLine = lines[static_cast<size_t>(lineIndex - 1)];
        return previousLine.end;
    }

    static int nextCaretIndex(const std::vector<InputLayout::Line>& lines, const std::string& text, int byteIndex) {
        if (lines.empty()) {
            return 0;
        }
        const int lineIndex = lineIndexFor(lines, byteIndex);
        const InputLayout::Line& line = lines[static_cast<size_t>(lineIndex)];
        if (line.hardBreakAfter && byteIndex == line.end) {
            return std::min(static_cast<int>(text.size()), line.end + 1);
        }
        if (byteIndex < line.end) {
            return line.start + nextCaretIndex(line.metrics, byteIndex - line.start);
        }
        if (lineIndex + 1 >= static_cast<int>(lines.size())) {
            return line.end;
        }
        const InputLayout::Line& nextLine = lines[static_cast<size_t>(lineIndex + 1)];
        return nextLine.start;
    }

    static int prevCursorIndex(InputState& state,
                               const std::string& fontFamily,
                               float fontSize,
                               bool multiline = false,
                               float viewportWidth = 0.0f) {
        if (multiline) {
            return clampUtf8Boundary(state.text, previousCaretIndex(cachedLines(state, fontFamily, fontSize, viewportWidth, true), state.cursor));
        }
        return clampUtf8Boundary(state.text, previousCaretIndex(cachedMetrics(state, fontFamily, fontSize, viewportWidth), state.cursor));
    }

    static int nextCursorIndex(InputState& state,
                               const std::string& fontFamily,
                               float fontSize,
                               bool multiline = false,
                               float viewportWidth = 0.0f) {
        if (multiline) {
            return clampUtf8Boundary(state.text, nextCaretIndex(cachedLines(state, fontFamily, fontSize, viewportWidth, true), state.text, state.cursor));
        }
        return clampUtf8Boundary(state.text, nextCaretIndex(cachedMetrics(state, fontFamily, fontSize, viewportWidth), state.cursor));
    }

    static void syncScroll(InputState& state, float viewportWidth, const std::string& fontFamily, float fontSize) {
        syncScroll(state, viewportWidth, cachedMetrics(state, fontFamily, fontSize, viewportWidth), fontSize);
    }

    static void syncScroll(InputState& state,
                           float viewportWidth,
                           const core::TextPrimitive::TextMetrics& metrics,
                           float fontSize) {
        const float textWidth = metrics.width;
        const float cursorPixel = caretX(metrics, state.cursor);
        if (textWidth <= viewportWidth) {
            state.horizontalScroll = 0.0f;
            return;
        }
        const float trailingPadding = std::max(6.0f, fontSize * 0.35f);
        const float rightSafe = std::max(1.0f, viewportWidth - trailingPadding);
        if (cursorPixel - state.horizontalScroll < 0.0f) {
            state.horizontalScroll = cursorPixel;
        } else if (cursorPixel - state.horizontalScroll > rightSafe) {
            state.horizontalScroll = cursorPixel - rightSafe;
        }
        state.horizontalScroll = std::clamp(state.horizontalScroll, 0.0f, std::max(0.0f, textWidth - viewportWidth + trailingPadding));
    }

    static std::string makeDirtyKey(const InputState& state, bool focused, const InputLayout& layout) {
        std::string key = focused ? "f|" : "b|";
        key += std::to_string(state.cursor);
        key += '|';
        key += std::to_string(state.selectionStart);
        key += '|';
        key += std::to_string(state.selectionEnd);
        key += '|';
        key += std::to_string(static_cast<int>(std::lround(layout.scroll * 64.0f)));
        key += '|';
        key += std::to_string(static_cast<int>(std::lround(state.verticalScroll * 64.0f)));
        key += '|';
        key += std::to_string(state.textRevision);
        key += '|';
        key += std::to_string(state.compositionRevision);
        return key;
    }

};

} // namespace components::input_detail



namespace components {

struct InputStyle {
    InputStyle() : InputStyle(theme::dark()) {}

    explicit InputStyle(const theme::ThemeColorTokens& tokens) {
        background = tokens.surface;
        focused = theme::resolveFieldFill(tokens, tokens.surface, 0.20f, 0.70f);
        border = theme::withOpacity(tokens.border, 0.78f);
        focusBorder = theme::withAlpha(tokens.primary, 0.86f);
        text = tokens.text;
        placeholder = theme::withOpacity(tokens.text, 0.45f);
        cursor = tokens.primary;
        shadow = theme::popupShadow(tokens);
        radius = tokens.metrics.radius.popup;
    }

    core::Color background;
    core::Color focused;
    core::Color border;
    core::Color focusBorder;
    core::Color text;
    core::Color placeholder;
    core::Color cursor;
    core::Shadow shadow;
    float radius = 10.0f;
};

class InputBuilder {
public:
    InputBuilder(core::dsl::Ui& ui, std::string id)
        : ui_(ui), id_(std::move(id)) {}

    InputBuilder& x(float value) { x_ = value; hasX_ = true; return *this; }
    InputBuilder& y(float value) { y_ = value; hasY_ = true; return *this; }
    InputBuilder& position(float xValue, float yValue) { return x(xValue).y(yValue); }
    InputBuilder& size(float width, float height) { width_ = width; height_ = height; return *this; }
    InputBuilder& value(std::string value) { text_ = std::move(value); return *this; }
    InputBuilder& bind(eui::Signal<std::string>& signal) {
        value(signal.get());
        onChange([&signal](const std::string& value) { signal.set(value); });
        return *this;
    }
    InputBuilder& placeholder(std::string value) { placeholder_ = std::move(value); return *this; }
    InputBuilder& multiline(bool value = true) { multiline_ = value; return *this; }
    InputBuilder& fontSize(float value) { fontSize_ = std::max(1.0f, value); return *this; }
    InputBuilder& fontFamily(std::string value) { fontFamily_ = std::move(value); return *this; }
    InputBuilder& inset(float value) { inset_ = std::max(0.0f, value); return *this; }
    InputBuilder& style(const InputStyle& value) { style_ = value; return *this; }
    InputBuilder& theme(const theme::ThemeColorTokens& tokens) {
        style_ = InputStyle(tokens);
        metrics_ = tokens.metrics;
        return *this;
    }
    InputBuilder& transition(const core::Transition& value) { transition_ = value; return *this; }
    InputBuilder& transition(float duration, core::Ease ease = core::Ease::OutCubic) {
        transition_ = core::Transition::make(duration, ease);
        return *this;
    }
    InputBuilder& onChange(std::function<void(const std::string&)> callback) {
        onChange_ = std::move(callback);
        return *this;
    }
    InputBuilder& onEnter(std::function<void()> callback) {
        onEnter_ = std::move(callback);
        return *this;
    }
    InputBuilder& onFocus(std::function<void(bool)> callback) {
        onFocus_ = std::move(callback);
        return *this;
    }

    void build() {
        const std::string hitId = id_ + ".hit";
        const bool focused = ui_.isFocused(hitId);
        const float inset = inset_ >= 0.0f ? inset_ : metrics_.spacing.content;
        const float fontSize = fontSize_ > 0.0f ? fontSize_ : metrics_.typography.input;
        const float textWidth = std::max(0.0f, width_ - inset * 2.0f);
        const bool allowMultiline = multiline_;
        const std::function<void(const std::string&)> onChange = onChange_;
        const std::function<void()> onEnter = onEnter_;
        const std::function<void(bool)> onFocus = onFocus_;
        const float textLineHeight = multiline_ ? fontSize * 1.2f : fontSize;
        const float textY = multiline_ ? inset : std::max(0.0f, (height_ - textLineHeight) * 0.5f);
        const float textHeight = multiline_ ? std::max(0.0f, height_ - inset * 2.0f) : textLineHeight;
        const float width = width_;
        const std::string fontFamily = fontFamily_;
        InputState& state = ui_.state<InputState>(id_);
        if (state.text != text_) {
            const bool wasFocused = focused;
            state.text = text_;
            ++state.textRevision;
            state.cursor = InputModel::clampUtf8Boundary(state.text, static_cast<int>(state.text.size()));
            state.selectionStart = state.cursor;
            state.selectionEnd = state.cursor;
            if (!wasFocused) {
                state.horizontalScroll = 0.0f;
                state.verticalScroll = 0.0f;
                state.undoStack.clear();
                state.redoStack.clear();
            }
        }
        state.cursor = InputModel::clampUtf8Boundary(state.text, state.cursor);
        state.selectionStart = InputModel::clampUtf8Boundary(state.text, state.selectionStart);
        state.selectionEnd = InputModel::clampUtf8Boundary(state.text, state.selectionEnd);
        const InputLayout layout = InputLayout::build(state, textWidth, textHeight, width_, inset, textY, textLineHeight, fontFamily_, fontSize, multiline_);
        const bool empty = state.text.empty();
        const bool hasComposition = focused && !state.compositionText.empty();
        const bool hasSelection = !layout.selectionRects.empty();
        const std::string textDirtyKey = id_ + ".text|" + std::to_string(state.textRevision) +
            "|" + std::to_string(static_cast<int>(std::lround(state.horizontalScroll * 64.0f))) +
            "|" + std::to_string(static_cast<int>(std::lround(state.verticalScroll * 64.0f))) +
            (empty ? "|p" : "|v");
        const std::string compositionDirtyKey = id_ + ".composition|" + std::to_string(state.compositionRevision);
        const float renderedTextHeight = multiline_ ? layout.contentHeight : textHeight;
        const float compositionPadding = metrics_.spacing.hairline;
        const float compositionTextLeft = inset;
        const float compositionTextRight = std::max(compositionTextLeft, width_ - inset);
        const float compositionAvailableWidth = std::max(4.0f, compositionTextRight - compositionTextLeft);
        const float compositionTextWidth = hasComposition
            ? InputModel::measureMetrics(state.compositionText, fontFamily_, fontSize).width
            : 0.0f;
        const float compositionWidth = hasComposition
            ? std::clamp(std::ceil(compositionTextWidth) + compositionPadding * 2.0f, 2.0f, compositionAvailableWidth)
            : 0.0f;
        const float compositionX = hasComposition
            ? std::clamp(layout.clampedCursorX(), compositionTextLeft, std::max(compositionTextLeft, compositionTextRight - compositionWidth))
            : layout.clampedCursorX();
        const float caretX = hasComposition
            ? std::clamp(compositionX + compositionWidth, inset, std::max(inset, width_ - inset))
            : layout.clampedCursorX();

        auto root = ui_.stack(id_)
            .size(width_, height_)
            .clip()
            .dirtyKey(InputModel::makeDirtyKey(state, focused, layout));
        if (hasX_) {
            root.x(x_);
        }
        if (hasY_) {
            root.y(y_);
        }
        root.content([&] {
                auto hit = ui_.rect(hitId)
                    .size(width_, height_)
                    .color(style_.background)
                    .radius(style_.radius)
                    .border(1.0f, focused ? style_.focusBorder : style_.border)
                    .shadow(focused ? style_.shadow : core::Shadow{})
                    .transition(transition_)
                    .focusable()
                    .imeRect(hasComposition ? compositionX : caretX, layout.cursorY, 1.5f, textLineHeight)
                    .onPress([&state, width, inset, layout](const core::PointerEvent& event, const core::Rect& bounds) {
                        state.lastBounds = bounds;
                        state.cursor = InputModel::clampUtf8Boundary(state.text, layout.cursorFromPointer(event.x, event.y, bounds, width, inset));
                        state.hasPreferredCursorX = false;
                        InputModel::clearSelection(state);
                        state.dragAnchor = state.cursor;
                        state.selecting = true;
                    })
                    .onFocusChanged(onFocus)
                    .onDrag([&state, width, inset, fontSize, fontFamily, allowMultiline, textHeight, layout](const core::dsl::DragEvent& event) {
                        state.cursor = InputModel::clampUtf8Boundary(state.text, layout.cursorFromPointer(event.x, event.y, state.lastBounds, width, inset));
                        state.hasPreferredCursorX = false;
                        state.selectionStart = state.dragAnchor;
                        state.selectionEnd = state.cursor;
                        if (allowMultiline) {
                            InputModel::syncVerticalScroll(state, layout, textHeight);
                        } else {
                            InputModel::syncScroll(state, std::max(0.0f, width - inset * 2.0f), fontFamily, fontSize);
                        }
                    });
                if (allowMultiline && layout.maxVerticalScroll > 0.0f) {
                    hit.onScroll([&state, layout, fontSize](const core::ScrollEvent& event) {
                        const float step = std::max(12.0f, fontSize * 2.2f);
                        state.followCaret = false;
                        state.verticalScroll = std::clamp(
                            state.verticalScroll - static_cast<float>(event.y) * step,
                            0.0f,
                            layout.maxVerticalScroll);
                    });
                }
                hit.onTextInput([&state, allowMultiline, onChange, onEnter, width, inset, fontSize, fontFamily, textHeight](const core::KeyboardEvent& event) {
                        state.followCaret = true;
                        bool changed = false;
                        const std::string nextComposition = event.composing ? InputModel::filteredText(event.compositionText, allowMultiline) : std::string{};
                        if (state.compositionText != nextComposition) {
                            state.compositionText = nextComposition;
                            ++state.compositionRevision;
                        }

                        if (event.undo || event.redo) {
                            if (!state.compositionText.empty()) {
                                state.compositionText.clear();
                                ++state.compositionRevision;
                            }
                            changed = event.undo ? InputModel::undoEdit(state) : InputModel::redoEdit(state);
                            if (allowMultiline) {
                                state.horizontalScroll = 0.0f;
                                const InputLayout nextLayout = InputLayout::build(
                                    state,
                                    std::max(0.0f, width - inset * 2.0f),
                                    textHeight,
                                    width,
                                    inset,
                                    0.0f,
                                    fontSize,
                                    fontFamily,
                                    fontSize,
                                    allowMultiline);
                                InputModel::syncVerticalScroll(state, nextLayout, textHeight);
                            } else {
                                InputModel::syncScroll(state, std::max(0.0f, width - inset * 2.0f), fontFamily, fontSize);
                            }
                            if (changed && onChange) {
                                onChange(state.text);
                            }
                            return;
                        }

                        if (event.selectAll) {
                            state.selectionStart = 0;
                            state.selectionEnd = static_cast<int>(state.text.size());
                            state.cursor = state.selectionEnd;
                        }
                        if (event.copy) {
                            InputModel::copySelection(state);
                        }
                        if (event.cut && InputModel::hasTextSelection(state)) {
                            InputModel::copySelection(state);
                            InputModel::pushUndoState(state);
                            InputModel::eraseSelection(state);
                            changed = true;
                        }
                        if (event.left) {
                            InputModel::moveCursor(state, -1, event.shift, fontFamily, fontSize, allowMultiline, std::max(0.0f, width - inset * 2.0f));
                        }
                        if (event.right) {
                            InputModel::moveCursor(state, 1, event.shift, fontFamily, fontSize, allowMultiline, std::max(0.0f, width - inset * 2.0f));
                        }
                        if (event.up && allowMultiline) {
                            InputModel::moveCursorVertical(state, -1, event.shift, fontFamily, fontSize, std::max(0.0f, width - inset * 2.0f), textHeight);
                        }
                        if (event.down && allowMultiline) {
                            InputModel::moveCursorVertical(state, 1, event.shift, fontFamily, fontSize, std::max(0.0f, width - inset * 2.0f), textHeight);
                        }
                        if (event.home) {
                            if (allowMultiline) {
                                InputModel::moveCursorToLineEdge(state, false, event.shift, fontFamily, fontSize, std::max(0.0f, width - inset * 2.0f));
                            } else {
                                InputModel::moveCursorTo(state, 0, event.shift);
                            }
                        }
                        if (event.end) {
                            if (allowMultiline) {
                                InputModel::moveCursorToLineEdge(state, true, event.shift, fontFamily, fontSize, std::max(0.0f, width - inset * 2.0f));
                            } else {
                                InputModel::moveCursorTo(state, static_cast<int>(state.text.size()), event.shift);
                            }
                        }
                        if (event.del) {
                            if (InputModel::hasTextSelection(state)) {
                                InputModel::pushUndoState(state);
                                InputModel::eraseSelection(state);
                                changed = true;
                            } else if (state.cursor < static_cast<int>(state.text.size())) {
                                const int next = InputModel::nextCursorIndex(state, fontFamily, fontSize, allowMultiline, std::max(0.0f, width - inset * 2.0f));
                                InputModel::pushUndoState(state);
                                state.text.erase(static_cast<std::size_t>(state.cursor), static_cast<std::size_t>(next - state.cursor));
                                ++state.textRevision;
                                changed = true;
                            }
                        }
                        if (event.backspace) {
                            if (InputModel::hasTextSelection(state)) {
                                InputModel::pushUndoState(state);
                                InputModel::eraseSelection(state);
                                changed = true;
                            } else if (state.cursor > 0) {
                                const int previous = InputModel::prevCursorIndex(state, fontFamily, fontSize, allowMultiline, std::max(0.0f, width - inset * 2.0f));
                                InputModel::pushUndoState(state);
                                state.text.erase(static_cast<std::size_t>(previous), static_cast<std::size_t>(state.cursor - previous));
                                ++state.textRevision;
                                state.cursor = previous;
                                InputModel::clearSelection(state);
                                changed = true;
                            }
                        }
                        if (!event.text.empty()) {
                            if (!state.compositionText.empty()) {
                                state.compositionText.clear();
                                ++state.compositionRevision;
                            }
                            InputModel::pushUndoState(state);
                            InputModel::insertAtCursor(state, InputModel::filteredText(event.text, allowMultiline));
                            changed = true;
                        }
                        if (!event.pasteText.empty()) {
                            if (!state.compositionText.empty()) {
                                state.compositionText.clear();
                                ++state.compositionRevision;
                            }
                            InputModel::pushUndoState(state);
                            InputModel::insertAtCursor(state, InputModel::filteredText(event.pasteText, allowMultiline));
                            changed = true;
                        }
                        if (event.enter) {
                            if (allowMultiline) {
                                InputModel::pushUndoState(state);
                                InputModel::insertAtCursor(state, "\n");
                                changed = true;
                            } else if (onEnter) {
                                onEnter();
                            }
                        }
                        if (event.escape && onEnter) {
                            onEnter();
                        }
                        if (allowMultiline) {
                            state.horizontalScroll = 0.0f;
                        } else {
                            InputModel::syncScroll(state, std::max(0.0f, width - inset * 2.0f), fontFamily, fontSize);
                        }
                        if (changed && onChange) {
                            onChange(state.text);
                        }
                    })
                    .build();

                ui_.stack(id_ + ".textViewport")
                    .position(inset, textY)
                    .size(textWidth, textHeight)
                    .clip()
                    .content([&] {
                        if (hasSelection) {
                            for (size_t index = 0; index < layout.selectionRects.size(); ++index) {
                                const auto& selectionRect = layout.selectionRects[index];
                                ui_.rect(id_ + ".selection." + std::to_string(index))
                                    .position(selectionRect.x - inset, selectionRect.y - textY)
                                    .size(selectionRect.width, selectionRect.height)
                                    .color(theme::withAlpha(style_.cursor, 0.24f))
                                    .radius(multiline_ ? 0.0f : 3.0f)
                                    .build();
                            }
                        }

                        if (multiline_ && !empty) {
                            const auto& lines = layout.lineList();
                            for (std::size_t index = 0; index < lines.size(); ++index) {
                                const auto& line = lines[index];
                                const float y = static_cast<float>(index) * textLineHeight - state.verticalScroll;
                                if (y + textLineHeight < 0.0f || y > textHeight) {
                                    continue;
                                }
                                ui_.text(id_ + ".text." + std::to_string(index))
                                    .position(0.0f, y)
                                    .size(layout.visibleTextWidth, textLineHeight)
                                    .dirtyKey(textDirtyKey + "|" + std::to_string(index))
                                    .text(state.text.substr(static_cast<std::size_t>(line.start),
                                                            static_cast<std::size_t>(std::max(0, line.end - line.start))))
                                    .fontSize(fontSize)
                                    .fontFamily(fontFamily_)
                                    .lineHeight(textLineHeight)
                                    .color(style_.text)
                                    .wrap(false)
                                    .verticalAlign(core::VerticalAlign::Top)
                                    .build();
                            }
                        } else {
                            ui_.text(id_ + ".text")
                                .position(-state.horizontalScroll, -state.verticalScroll)
                                .size(layout.visibleTextWidth, renderedTextHeight)
                                .dirtyKey(textDirtyKey)
                                .text(empty ? placeholder_ : state.text)
                                .fontSize(fontSize)
                                .fontFamily(fontFamily_)
                                .lineHeight(textLineHeight)
                                .color(empty ? style_.placeholder : style_.text)
                                .wrap(false)
                                .verticalAlign(core::VerticalAlign::Top)
                                .build();
                        }

                        if (hasComposition) {
                            ui_.rect(id_ + ".composition.bg")
                                .position(compositionX - inset, layout.cursorY - textY)
                                .size(compositionWidth, textLineHeight)
                                .color(theme::withAlpha(style_.focused, 0.82f))
                                .radius(2.0f)
                                .build();

                            ui_.text(id_ + ".composition")
                                .position(compositionX + compositionPadding - inset, layout.cursorY - textY)
                                .size(std::max(1.0f, compositionWidth - compositionPadding * 2.0f), textLineHeight)
                                .dirtyKey(compositionDirtyKey)
                                .text(state.compositionText)
                                .fontSize(fontSize)
                                .fontFamily(fontFamily_)
                                .lineHeight(textLineHeight)
                                .color(style_.text)
                                .wrap(false)
                                .verticalAlign(core::VerticalAlign::Top)
                                .build();
                        }

                        if (focused) {
                            ui_.rect(id_ + ".cursor")
                                .position(caretX - inset, layout.cursorY - textY)
                                .size(1.5f, fontSize * 1.18f)
                                .color(style_.cursor)
                                .radius(1.0f)
                                .build();
                        }
                    })
                    .build();
            })
            .build();
    }

private:
    using InputModel = input_detail::InputModel;
    using InputState = InputModel::InputState;
    using InputLayout = InputModel::InputLayout;

    core::dsl::Ui& ui_;
    std::string id_;
    InputStyle style_;
    theme::ThemeMetricTokens metrics_;
    core::Transition transition_ = core::Transition::make(0.16f, core::Ease::OutCubic);
    std::function<void(const std::string&)> onChange_;
    std::function<void()> onEnter_;
    std::function<void(bool)> onFocus_;
    std::string text_;
    std::string placeholder_ = "Hello EUI-NEO 😉";
    bool multiline_ = false;
    float width_ = 260.0f;
    float height_ = 44.0f;
    float x_ = 0.0f;
    float y_ = 0.0f;
    float inset_ = -1.0f;
    float fontSize_ = 0.0f;
    std::string fontFamily_ = "Microsoft YaHei";
    bool hasX_ = false;
    bool hasY_ = false;
};

inline InputBuilder input(core::dsl::Ui& ui, const std::string& id) {
    return InputBuilder(ui, id);
}

} // namespace components



namespace components {

struct ScrollStyle {
    ScrollStyle() : ScrollStyle(theme::dark()) {}

    explicit ScrollStyle(const theme::ThemeColorTokens& tokens) {
        track = theme::withOpacity(tokens.surfaceHover, tokens.dark ? 0.34f : 0.46f);
        thumb = theme::withOpacity(tokens.text, tokens.dark ? 0.34f : 0.28f);
        thumbHover = theme::withOpacity(tokens.text, tokens.dark ? 0.46f : 0.38f);
        thumbPressed = theme::withOpacity(tokens.primary, 0.76f);
        radius = tokens.metrics.radius.full;
    }

    core::Color track;
    core::Color thumb;
    core::Color thumbHover;
    core::Color thumbPressed;
    float radius = 999.0f;
};

class ScrollBuilder {
public:
    ScrollBuilder(core::dsl::Ui& ui, std::string id)
        : ui_(ui), id_(std::move(id)) {}

    ScrollBuilder& x(float value) { x_ = value; hasX_ = true; return *this; }
    ScrollBuilder& y(float value) { y_ = value; hasY_ = true; return *this; }
    ScrollBuilder& position(float xValue, float yValue) {
        x_ = xValue;
        y_ = yValue;
        hasX_ = true;
        hasY_ = true;
        return *this;
    }
    ScrollBuilder& size(float width, float height) { width_ = width; height_ = height; return *this; }
    ScrollBuilder& scrollStateId(const std::string& id) { stateId_ = id; return *this; }
    ScrollBuilder& offset(float value) { offset_ = std::max(0.0f, value); return *this; }
    ScrollBuilder& viewport(float value) { viewport_ = std::max(0.0f, value); return *this; }
    ScrollBuilder& content(float value) { content_ = std::max(0.0f, value); return *this; }
    ScrollBuilder& step(float value) { step_ = std::max(1.0f, value); return *this; }
    ScrollBuilder& zIndex(int value) { zIndex_ = value; return *this; }
    ScrollBuilder& style(const ScrollStyle& value) { style_ = value; return *this; }
    ScrollBuilder& theme(const theme::ThemeColorTokens& tokens) {
        style_ = ScrollStyle(tokens);
        metrics_ = tokens.metrics;
        return *this;
    }
    ScrollBuilder& transition(const core::Transition& value) { transition_ = value; return *this; }
    ScrollBuilder& transition(float duration, core::Ease ease = core::Ease::OutCubic) {
        transition_ = core::Transition::make(duration, ease);
        return *this;
    }

    void build() {
        const float width = width_ >= 0.0f ? width_ : metrics_.control.scrollbar;
        const float maxOffset = std::max(0.0f, content_ - viewport_);
        const bool scrollable = maxOffset > 0.0f && viewport_ > 0.0f && content_ > 0.0f;
        const float thumbHeight = scrollable
            ? std::clamp(height_ * (viewport_ / content_), std::min(height_, metrics_.control.switchHeight), height_)
            : height_;
        const float travel = std::max(0.0f, height_ - thumbHeight);
        const float currentOffset = std::clamp(offset_, 0.0f, maxOffset);
        const float scrollStep = step_ > 0.0f ? step_ : metrics_.control.control;
        const std::string runtimeStateId = stateId_.empty() ? id_ : stateId_;

        auto root = ui_.stack(id_)
            .size(width, height_)
            .zIndex(zIndex_)
            .scrollState(runtimeStateId, currentOffset, maxOffset, scrollStep);
        if (hasX_) {
            root.x(x_);
        }
        if (hasY_) {
            root.y(y_);
        }
        root.content([&] {
                ui_.rect(id_ + ".track")
                    .size(width, height_)
                    .color(style_.track)
                    .radius(style_.radius)
                    .scrollState(runtimeStateId, currentOffset, maxOffset, scrollStep)
                    .build();

                ui_.rect(id_ + ".thumb")
                    .size(width, thumbHeight)
                    .states(style_.thumb, style_.thumbHover, style_.thumbPressed)
                    .radius(style_.radius)
                    .cursor(core::CursorShape::Hand)
                    .transition(transition_)
                    .animate(core::AnimProperty::Color)
                    .scrollDragFrom(runtimeStateId, travel)
                    .scrollThumbFrom(runtimeStateId, travel)
                    .transformedHitTest()
                    .build();
            })
            .build();
    }

private:
    core::dsl::Ui& ui_;
    std::string id_;
    std::string stateId_;
    ScrollStyle style_;
    theme::ThemeMetricTokens metrics_;
    core::Transition transition_ = core::Transition::make(0.12f, core::Ease::OutCubic);
    float width_ = -1.0f;
    float height_ = 180.0f;
    float viewport_ = 180.0f;
    float content_ = 180.0f;
    float offset_ = 0.0f;
    float step_ = 0.0f;
    float x_ = 0.0f;
    float y_ = 0.0f;
    bool hasX_ = false;
    bool hasY_ = false;
    int zIndex_ = 0;
};

inline ScrollBuilder scroll(core::dsl::Ui& ui, const std::string& id) {
    return ScrollBuilder(ui, id);
}

} // namespace components



namespace components {

class ScrollViewBuilder {
public:
    ScrollViewBuilder(core::dsl::Ui& ui, std::string id)
        : ui_(ui), id_(std::move(id)) {}

    ScrollViewBuilder& x(float value) { x_ = value; hasX_ = true; return *this; }
    ScrollViewBuilder& y(float value) { y_ = value; hasY_ = true; return *this; }
    ScrollViewBuilder& position(float xValue, float yValue) {
        x_ = xValue;
        y_ = yValue;
        hasX_ = true;
        hasY_ = true;
        return *this;
    }
    ScrollViewBuilder& size(float width, float height) { width_ = width; height_ = height; return *this; }
    ScrollViewBuilder& offset(float value) { offset_ = std::max(0.0f, value); return *this; }
    ScrollViewBuilder& bind(eui::Signal<float>& signal) {
        offset(signal.get());
        onChange([&signal](float value) { signal.set(value); });
        return *this;
    }
    ScrollViewBuilder& gap(float value) { gap_ = std::max(0.0f, value); return *this; }
    ScrollViewBuilder& step(float value) { step_ = std::max(1.0f, value); return *this; }
    ScrollViewBuilder& scrollbarWidth(float value) { scrollbarWidth_ = std::max(0.0f, value); return *this; }
    ScrollViewBuilder& scrollbarGap(float value) { scrollbarGap_ = std::max(0.0f, value); return *this; }
    ScrollViewBuilder& zIndex(int value) { zIndex_ = value; return *this; }
    ScrollViewBuilder& style(const ScrollStyle& value) { scrollStyle_ = value; return *this; }
    ScrollViewBuilder& theme(const theme::ThemeColorTokens& tokens) {
        scrollStyle_ = ScrollStyle(tokens);
        metrics_ = tokens.metrics;
        tokens_ = tokens;
        return *this;
    }
    ScrollViewBuilder& contentKey(std::string value) { contentKey_ = std::move(value); return *this; }
    ScrollViewBuilder& transition(const core::Transition& value) { transition_ = value; return *this; }
    ScrollViewBuilder& transition(float duration, core::Ease ease = core::Ease::OutCubic) {
        transition_ = core::Transition::make(duration, ease);
        return *this;
    }
    ScrollViewBuilder& onChange(std::function<void(float)> callback) {
        onChange_ = std::move(callback);
        return *this;
    }

    template <typename ComposeFn>
    ScrollViewBuilder& content(ComposeFn&& compose) {
        content_ = std::forward<ComposeFn>(compose);
        return *this;
    }

    void build() {
        MeasureCache* cache = contentKey_.empty() ? nullptr : &ui_.state<MeasureCache>(id_ + ".measure");
        const float initialContentHeight = contentKey_.empty()
            ? measureContentHeight(width_, height_)
            : cachedContentHeight(*cache, width_, height_);
        const bool scrollable = initialContentHeight > height_;
        const float scrollbarWidth = scrollbarWidth_ >= 0.0f ? scrollbarWidth_ : metrics_.control.scrollbar;
        const float scrollbarGap = scrollbarGap_ >= 0.0f ? scrollbarGap_ : metrics_.spacing.section;
        const float scrollWidth = scrollable ? scrollbarWidth : 0.0f;
        const float scrollGap = scrollable ? scrollbarGap : 0.0f;
        const float contentWidth = std::max(0.0f, width_ - scrollWidth - scrollGap);
        const float contentHeight = scrollable
            ? (contentKey_.empty() ? measureContentHeight(contentWidth, height_) : cachedContentHeight(*cache, contentWidth, height_))
            : initialContentHeight;
        const float maxOffset = std::max(0.0f, contentHeight - height_);
        const float currentOffset = std::clamp(offset_, 0.0f, maxOffset);
        const std::function<void(float)> onChange = onChange_;
        const float scrollStep = step_ > 0.0f ? step_ : metrics_.spacing.overlay;

        auto root = ui_.stack(id_)
            .size(width_, height_)
            .zIndex(zIndex_)
            .clip()
            .scrollState(id_, currentOffset, maxOffset, scrollStep)
            .onScrollOffsetChanged(onChange);
        if (hasX_) {
            root.x(x_);
        }
        if (hasY_) {
            root.y(y_);
        }
        root.content([&] {
                ui_.column(id_ + ".content")
                    .width(contentWidth)
                    .height(core::SizeValue::wrapContent())
                    .gap(gap_)
                    .scrollContentFrom(id_)
                    .content([&] {
                        if (content_) {
                            content_(ui_, contentWidth, height_);
                        }
                    })
                    .build();

                if (scrollable) {
                    components::scroll(ui_, id_ + ".scroll")
                        .theme(tokens_)
                        .style(scrollStyle_)
                        .scrollStateId(id_)
                        .x(std::max(0.0f, width_ - scrollWidth))
                        .size(scrollWidth, height_)
                        .viewport(height_)
                        .content(contentHeight)
                        .offset(currentOffset)
                        .step(scrollStep)
                        .zIndex(zIndex_ + 1)
                        .transition(transition_)
                        .build();
                }
            })
            .build();
    }

private:
    struct MeasureCache {
        struct Entry {
            float width = -1.0f;
            float viewportHeight = -1.0f;
            float gap = -1.0f;
            float height = 0.0f;
            std::string contentKey;
        };

        std::vector<Entry> entries;
    };

    float cachedContentHeight(MeasureCache& cache, float contentWidth, float viewportHeight) const {
        for (const MeasureCache::Entry& entry : cache.entries) {
            if (closeEnough(entry.width, contentWidth) &&
                closeEnough(entry.viewportHeight, viewportHeight) &&
                closeEnough(entry.gap, gap_) &&
                entry.contentKey == contentKey_) {
                return entry.height;
            }
        }

        const float height = measureContentHeight(contentWidth, viewportHeight);
        if (cache.entries.size() >= 4) {
            cache.entries.erase(cache.entries.begin());
        }
        cache.entries.push_back({contentWidth, viewportHeight, gap_, height, contentKey_});
        return height;
    }

    static bool closeEnough(float left, float right) {
        return std::fabs(left - right) <= 0.5f;
    }

    float measureContentHeight(float contentWidth, float viewportHeight) const {
        if (!content_) {
            return viewportHeight;
        }

        core::dsl::Ui measureUi;
        measureUi.begin(id_ + ".measure");
        measureUi.column("content")
            .width(contentWidth)
            .height(core::SizeValue::wrapContent())
            .gap(gap_)
            .content([&] {
                content_(measureUi, contentWidth, viewportHeight);
            })
            .build();
        measureUi.end();
        measureUi.layout(contentWidth, 0.0f);
        const core::dsl::Element* content = measureUi.find("content");
        if (content == nullptr) {
            return viewportHeight;
        }
        return std::max(viewportHeight, content->frame.height);
    }

    core::dsl::Ui& ui_;
    std::string id_;
    ScrollStyle scrollStyle_;
    theme::ThemeMetricTokens metrics_;
    theme::ThemeColorTokens tokens_ = theme::dark();
    core::Transition transition_ = core::Transition::make(0.12f, core::Ease::OutCubic);
    std::function<void(float)> onChange_;
    std::function<void(core::dsl::Ui&, float, float)> content_;
    std::string contentKey_;
    float width_ = 320.0f;
    float height_ = 220.0f;
    float offset_ = 0.0f;
    float gap_ = 0.0f;
    float step_ = 0.0f;
    float scrollbarWidth_ = -1.0f;
    float scrollbarGap_ = -1.0f;
    float x_ = 0.0f;
    float y_ = 0.0f;
    bool hasX_ = false;
    bool hasY_ = false;
    int zIndex_ = 0;
};

inline ScrollViewBuilder scrollView(core::dsl::Ui& ui, const std::string& id) {
    return ScrollViewBuilder(ui, id);
}

} // namespace components



namespace components {

class VirtualListBuilder {
public:
    using RowCompose = std::function<void(core::dsl::Ui&, const std::string&, std::int64_t, float, float)>;

    VirtualListBuilder(core::dsl::Ui& ui, std::string id)
        : ui_(ui), id_(std::move(id)) {}

    VirtualListBuilder& x(float value) { x_ = value; hasX_ = true; return *this; }
    VirtualListBuilder& y(float value) { y_ = value; hasY_ = true; return *this; }
    VirtualListBuilder& position(float xValue, float yValue) {
        x_ = xValue;
        y_ = yValue;
        hasX_ = true;
        hasY_ = true;
        return *this;
    }
    VirtualListBuilder& size(float width, float height) { width_ = width; height_ = height; return *this; }
    VirtualListBuilder& itemCount(std::int64_t value) { itemCount_ = std::max<std::int64_t>(0, value); return *this; }
    VirtualListBuilder& rowHeight(float value) { rowHeight_ = std::max(1.0f, value); return *this; }
    VirtualListBuilder& offset(float value) { offset_ = std::max(0.0f, value); return *this; }
    VirtualListBuilder& bind(eui::Signal<float>& signal) {
        offset(signal.get());
        onChange([&signal](float value) { signal.set(value); });
        return *this;
    }
    VirtualListBuilder& step(float value) { step_ = std::max(1.0f, value); return *this; }
    VirtualListBuilder& overscanViewports(float value) { overscanViewports_ = std::max(0.0f, value); return *this; }
    VirtualListBuilder& scrollbarWidth(float value) { scrollbarWidth_ = std::max(0.0f, value); return *this; }
    VirtualListBuilder& scrollbarGap(float value) { scrollbarGap_ = std::max(0.0f, value); return *this; }
    VirtualListBuilder& zIndex(int value) { zIndex_ = value; return *this; }
    VirtualListBuilder& style(const ScrollStyle& value) { scrollStyle_ = value; return *this; }
    VirtualListBuilder& theme(const theme::ThemeColorTokens& tokens) {
        scrollStyle_ = ScrollStyle(tokens);
        metrics_ = tokens.metrics;
        tokens_ = tokens;
        return *this;
    }
    VirtualListBuilder& transition(const core::Transition& value) { transition_ = value; return *this; }
    VirtualListBuilder& transition(float duration, core::Ease ease = core::Ease::OutCubic) {
        transition_ = core::Transition::make(duration, ease);
        return *this;
    }
    VirtualListBuilder& onChange(std::function<void(float)> callback) {
        onChange_ = std::move(callback);
        return *this;
    }
    VirtualListBuilder& row(RowCompose compose) {
        row_ = std::move(compose);
        return *this;
    }

    void build() {
        const float viewportWidth = std::max(0.0f, width_);
        const float viewportHeight = std::max(0.0f, height_);
        const float rowHeight = std::max(1.0f, rowHeight_);
        const double totalHeightValue = static_cast<double>(itemCount_) * static_cast<double>(rowHeight);
        const float totalHeight = static_cast<float>(totalHeightValue);
        const float maxOffset = std::max(0.0f, totalHeight - viewportHeight);
        const float currentOffset = std::clamp(offset_, 0.0f, maxOffset);
        const bool scrollable = maxOffset > 0.0f;
        const float scrollbarWidth = scrollbarWidth_ >= 0.0f ? scrollbarWidth_ : metrics_.control.scrollbar;
        const float scrollbarGap = scrollbarGap_ >= 0.0f ? scrollbarGap_ : metrics_.spacing.section;
        const float scrollWidth = scrollable ? scrollbarWidth : 0.0f;
        const float scrollGap = scrollable ? scrollbarGap : 0.0f;
        const float contentWidth = std::max(0.0f, viewportWidth - scrollWidth - scrollGap);
        const std::function<void(float)> onChange = onChange_;
        const float scrollStep = step_ > 0.0f ? step_ : metrics_.spacing.overlay;

        const float overscanPixels = viewportHeight * overscanViewports_;
        const double firstPixel = std::max(0.0, static_cast<double>(currentOffset) - static_cast<double>(overscanPixels));
        const double lastPixel = std::min(totalHeightValue,
                                          static_cast<double>(currentOffset) +
                                              static_cast<double>(viewportHeight) +
                                              static_cast<double>(overscanPixels));
        const std::int64_t firstIndex = itemCount_ > 0
            ? std::clamp<std::int64_t>(
                  static_cast<std::int64_t>(std::floor(firstPixel / static_cast<double>(rowHeight))),
                  0,
                  itemCount_ - 1)
            : 0;
        const std::int64_t lastIndex = itemCount_ > 0
            ? std::clamp<std::int64_t>(
                  static_cast<std::int64_t>(std::ceil(lastPixel / static_cast<double>(rowHeight))) + 1,
                  firstIndex,
                  itemCount_)
            : 0;
        auto root = ui_.stack(id_)
            .size(viewportWidth, viewportHeight)
            .zIndex(zIndex_)
            .clip()
            .scrollState(id_, currentOffset, maxOffset, scrollStep)
            .composeOnScrollOffsetChange()
            .onScrollOffsetChanged([onChange](float value) {
                if (onChange) {
                    onChange(value);
                }
                core::platform::requestUiUpdate();
            });
        if (hasX_) {
            root.x(x_);
        }
        if (hasY_) {
            root.y(y_);
        }
        root.content([&] {
                ui_.stack(id_ + ".window")
                    .size(contentWidth, viewportHeight)
                    .dirtyKey(id_ + ".virtual")
                    .content([&] {
                        if (!row_) {
                            return;
                        }
                        const double offset = static_cast<double>(currentOffset);
                        std::int64_t slot = 0;
                        for (std::int64_t index = firstIndex; index < lastIndex; ++index) {
                            const std::string rowId = id_ + ".slot." + std::to_string(slot);
                            const double absoluteY = static_cast<double>(index) * static_cast<double>(rowHeight);
                            const float rowY = static_cast<float>(absoluteY - offset);
                            ui_.stack(rowId)
                                .y(rowY)
                                .size(contentWidth, rowHeight)
                                .content([&] {
                                    row_(ui_, rowId, index, contentWidth, rowHeight);
                                })
                                .build();
                            ++slot;
                        }
                    })
                    .build();

                if (scrollable) {
                    components::scroll(ui_, id_ + ".scroll")
                        .theme(tokens_)
                        .style(scrollStyle_)
                        .scrollStateId(id_)
                        .x(std::max(0.0f, viewportWidth - scrollWidth))
                        .size(scrollWidth, viewportHeight)
                        .viewport(viewportHeight)
                        .content(totalHeight)
                        .offset(currentOffset)
                        .step(scrollStep)
                        .zIndex(zIndex_ + 1)
                        .transition(transition_)
                        .build();
                }
            })
            .build();
    }

private:
    core::dsl::Ui& ui_;
    std::string id_;
    ScrollStyle scrollStyle_;
    theme::ThemeMetricTokens metrics_;
    theme::ThemeColorTokens tokens_ = theme::dark();
    core::Transition transition_ = core::Transition::make(0.12f, core::Ease::OutCubic);
    std::function<void(float)> onChange_;
    RowCompose row_;
    std::int64_t itemCount_ = 0;
    float width_ = 320.0f;
    float height_ = 220.0f;
    float rowHeight_ = 36.0f;
    float offset_ = 0.0f;
    float step_ = 0.0f;
    float overscanViewports_ = 1.0f;
    float scrollbarWidth_ = -1.0f;
    float scrollbarGap_ = -1.0f;
    float x_ = 0.0f;
    float y_ = 0.0f;
    bool hasX_ = false;
    bool hasY_ = false;
    int zIndex_ = 0;
};

inline VirtualListBuilder virtualList(core::dsl::Ui& ui, const std::string& id) {
    return VirtualListBuilder(ui, id);
}

} // namespace components



namespace components {

class VirtualMasonryBuilder {
public:
    using ItemHeight = std::function<float(std::int64_t, float)>;
    using ItemCompose = std::function<void(core::dsl::Ui&, const std::string&, std::int64_t, float, float)>;

    VirtualMasonryBuilder(core::dsl::Ui& ui, std::string id)
        : ui_(ui), id_(std::move(id)) {}

    VirtualMasonryBuilder& x(float value) { x_ = value; hasX_ = true; return *this; }
    VirtualMasonryBuilder& y(float value) { y_ = value; hasY_ = true; return *this; }
    VirtualMasonryBuilder& position(float xValue, float yValue) {
        x_ = xValue;
        y_ = yValue;
        hasX_ = true;
        hasY_ = true;
        return *this;
    }
    VirtualMasonryBuilder& size(float width, float height) { width_ = width; height_ = height; return *this; }
    VirtualMasonryBuilder& itemCount(std::int64_t value) { itemCount_ = std::max<std::int64_t>(0, value); return *this; }
    VirtualMasonryBuilder& columns(int value) { columns_ = std::max(1, value); return *this; }
    VirtualMasonryBuilder& gap(float value) { gap_ = std::max(0.0f, value); return *this; }
    VirtualMasonryBuilder& offset(float value) { offset_ = std::max(0.0f, value); return *this; }
    VirtualMasonryBuilder& bind(eui::Signal<float>& signal) {
        offset(signal.get());
        onChange([&signal](float value) { signal.set(value); });
        return *this;
    }
    VirtualMasonryBuilder& step(float value) { step_ = std::max(1.0f, value); return *this; }
    VirtualMasonryBuilder& overscanViewports(float value) { overscanViewports_ = std::max(0.0f, value); return *this; }
    VirtualMasonryBuilder& endReachedThresholdViewports(float value) {
        endReachedThresholdViewports_ = std::max(0.0f, value);
        return *this;
    }
    VirtualMasonryBuilder& scrollbarWidth(float value) { scrollbarWidth_ = std::max(0.0f, value); return *this; }
    VirtualMasonryBuilder& scrollbarGap(float value) { scrollbarGap_ = std::max(0.0f, value); return *this; }
    VirtualMasonryBuilder& zIndex(int value) { zIndex_ = value; return *this; }
    VirtualMasonryBuilder& style(const ScrollStyle& value) { scrollStyle_ = value; return *this; }
    VirtualMasonryBuilder& theme(const theme::ThemeColorTokens& tokens) {
        scrollStyle_ = ScrollStyle(tokens);
        metrics_ = tokens.metrics;
        tokens_ = tokens;
        return *this;
    }
    VirtualMasonryBuilder& transition(const core::Transition& value) { transition_ = value; return *this; }
    VirtualMasonryBuilder& transition(float duration, core::Ease ease = core::Ease::OutCubic) {
        transition_ = core::Transition::make(duration, ease);
        return *this;
    }
    VirtualMasonryBuilder& onChange(std::function<void(float)> callback) {
        onChange_ = std::move(callback);
        return *this;
    }
    VirtualMasonryBuilder& onEndReached(std::function<void()> callback) {
        onEndReached_ = std::move(callback);
        return *this;
    }
    VirtualMasonryBuilder& itemHeight(ItemHeight callback) {
        itemHeight_ = std::move(callback);
        return *this;
    }
    VirtualMasonryBuilder& item(ItemCompose compose) {
        item_ = std::move(compose);
        return *this;
    }

    void build() {
        const float viewportWidth = std::max(0.0f, width_);
        const float viewportHeight = std::max(0.0f, height_);
        const float scrollbarWidth = scrollbarWidth_ >= 0.0f ? scrollbarWidth_ : metrics_.control.scrollbar;
        const float scrollbarGap = scrollbarGap_ >= 0.0f ? scrollbarGap_ : metrics_.spacing.section;

        Layout layout = makeLayout(viewportWidth);
        bool scrollable = layout.totalHeight > viewportHeight;
        const float scrollWidth = scrollable ? scrollbarWidth : 0.0f;
        const float scrollGap = scrollable ? scrollbarGap : 0.0f;
        float contentWidth = std::max(0.0f, viewportWidth - scrollWidth - scrollGap);
        if (scrollable && std::fabs(contentWidth - viewportWidth) > 0.01f) {
            layout = makeLayout(contentWidth);
            scrollable = layout.totalHeight > viewportHeight;
            if (!scrollable) {
                contentWidth = viewportWidth;
                layout = makeLayout(contentWidth);
            }
        }

        const float maxOffset = std::max(0.0f, layout.totalHeight - viewportHeight);
        const float currentOffset = std::clamp(offset_, 0.0f, maxOffset);
        const float scrollStep = step_ > 0.0f ? step_ : metrics_.spacing.overlay;
        const float overscan = viewportHeight * overscanViewports_;
        const float visibleTop = std::max(0.0f, currentOffset - overscan);
        const float visibleBottom = currentOffset + viewportHeight + overscan;
        const float endThreshold = viewportHeight * endReachedThresholdViewports_;
        const std::function<void(float)> onChange = onChange_;
        const std::function<void()> onEndReached = onEndReached_;
        std::int64_t& lastAutoEndCount = ui_.state<std::int64_t>(id_ + ".end.count");
        if (onEndReached && itemCount_ > 0 && maxOffset - currentOffset <= endThreshold &&
            lastAutoEndCount != itemCount_) {
            lastAutoEndCount = itemCount_;
            onEndReached();
        }

        auto root = ui_.stack(id_)
            .size(viewportWidth, viewportHeight)
            .zIndex(zIndex_)
            .clip()
            .scrollState(id_, currentOffset, maxOffset, scrollStep)
            .composeOnScrollOffsetChange()
            .onScrollOffsetChanged([onChange, onEndReached, maxOffset, endThreshold](float value) {
                if (onChange) {
                    onChange(value);
                }
                if (onEndReached && maxOffset - value <= endThreshold) {
                    onEndReached();
                }
                core::platform::requestUiUpdate();
            });
        if (hasX_) {
            root.x(x_);
        }
        if (hasY_) {
            root.y(y_);
        }
        root.content([&] {
                ui_.stack(id_ + ".window")
                    .size(contentWidth, viewportHeight)
                    .dirtyKey(id_ + ".virtual")
                    .content([&] {
                        if (!item_) {
                            return;
                        }
                        for (std::size_t index = 0; index < layout.items.size(); ++index) {
                            const ItemFrame& frame = layout.items[index];
                            if (frame.y + frame.height < visibleTop || frame.y > visibleBottom) {
                                continue;
                            }
                            const std::string itemId = id_ + ".item." + std::to_string(index);
                            ui_.stack(itemId)
                                .position(frame.x, frame.y - currentOffset)
                                .size(frame.width, frame.height)
                                .content([&] {
                                    item_(ui_, itemId, static_cast<std::int64_t>(index), frame.width, frame.height);
                                })
                                .build();
                        }
                    })
                    .build();

                if (scrollable) {
                    components::scroll(ui_, id_ + ".scroll")
                        .theme(tokens_)
                        .style(scrollStyle_)
                        .scrollStateId(id_)
                        .x(std::max(0.0f, viewportWidth - scrollbarWidth))
                        .size(scrollbarWidth, viewportHeight)
                        .viewport(viewportHeight)
                        .content(layout.totalHeight)
                        .offset(currentOffset)
                        .step(scrollStep)
                        .zIndex(zIndex_ + 1)
                        .transition(transition_)
                        .build();
                }
            })
            .build();
    }

private:
    struct ItemFrame {
        float x = 0.0f;
        float y = 0.0f;
        float width = 0.0f;
        float height = 0.0f;
    };

    struct Layout {
        std::vector<ItemFrame> items;
        float totalHeight = 0.0f;
    };

    Layout makeLayout(float contentWidth) const {
        Layout layout;
        if (itemCount_ <= 0 || contentWidth <= 0.0f) {
            return layout;
        }

        const int columnCount = std::max(1, columns_);
        const float totalGap = gap_ * static_cast<float>(columnCount - 1);
        const float itemWidth = std::max(1.0f, (contentWidth - totalGap) / static_cast<float>(columnCount));
        std::vector<float> columnHeights(static_cast<std::size_t>(columnCount), 0.0f);
        layout.items.reserve(static_cast<std::size_t>(itemCount_));

        for (std::int64_t index = 0; index < itemCount_; ++index) {
            int column = 0;
            for (int candidate = 1; candidate < columnCount; ++candidate) {
                if (columnHeights[static_cast<std::size_t>(candidate)] < columnHeights[static_cast<std::size_t>(column)]) {
                    column = candidate;
                }
            }
            const float height = std::max(1.0f, itemHeight_ ? itemHeight_(index, itemWidth) : itemWidth);
            const float x = static_cast<float>(column) * (itemWidth + gap_);
            const float y = columnHeights[static_cast<std::size_t>(column)];
            layout.items.push_back({x, y, itemWidth, height});
            columnHeights[static_cast<std::size_t>(column)] = y + height + gap_;
        }

        for (float height : columnHeights) {
            layout.totalHeight = std::max(layout.totalHeight, height);
        }
        layout.totalHeight = std::max(0.0f, layout.totalHeight - gap_);
        return layout;
    }

    core::dsl::Ui& ui_;
    std::string id_;
    ScrollStyle scrollStyle_;
    theme::ThemeMetricTokens metrics_;
    theme::ThemeColorTokens tokens_ = theme::dark();
    core::Transition transition_ = core::Transition::make(0.12f, core::Ease::OutCubic);
    ItemHeight itemHeight_;
    ItemCompose item_;
    std::function<void(float)> onChange_;
    std::function<void()> onEndReached_;
    std::int64_t itemCount_ = 0;
    int columns_ = 1;
    float width_ = 320.0f;
    float height_ = 220.0f;
    float gap_ = 0.0f;
    float offset_ = 0.0f;
    float step_ = 0.0f;
    float overscanViewports_ = 1.0f;
    float endReachedThresholdViewports_ = 1.0f;
    float scrollbarWidth_ = -1.0f;
    float scrollbarGap_ = -1.0f;
    float x_ = 0.0f;
    float y_ = 0.0f;
    bool hasX_ = false;
    bool hasY_ = false;
    int zIndex_ = 0;
};

inline VirtualMasonryBuilder virtualMasonry(core::dsl::Ui& ui, const std::string& id) {
    return VirtualMasonryBuilder(ui, id);
}

} // namespace components



namespace components {

struct DropdownStyle {
    DropdownStyle() : DropdownStyle(theme::dark()) {}

    explicit DropdownStyle(const theme::ThemeColorTokens& tokens) {
        field = tokens.surface;
        fieldHover = tokens.surfaceHover;
        fieldPressed = tokens.surfaceActive;
        popup = tokens.dark
            ? core::mixColor(tokens.surface, theme::color(0.0f, 0.0f, 0.0f), 0.12f)
            : tokens.surface;
        optionHover = tokens.surfaceHover;
        optionPressed = tokens.surfaceActive;
        selected = theme::withAlpha(tokens.primary, tokens.dark ? 0.24f : 0.14f);
        text = tokens.text;
        mutedText = theme::withOpacity(tokens.text, 0.60f);
        accent = tokens.primary;
        border = theme::withOpacity(tokens.border, 0.78f);
        shadow = theme::popupShadow(tokens);
        radius = tokens.metrics.radius.card;
    }

    core::Color field;
    core::Color fieldHover;
    core::Color fieldPressed;
    core::Color popup;
    core::Color optionHover;
    core::Color optionPressed;
    core::Color selected;
    core::Color text;
    core::Color mutedText;
    core::Color accent;
    core::Color border;
    core::Shadow shadow;
    float radius = 12.0f;
};

class DropdownBuilder {
public:
    DropdownBuilder(core::dsl::Ui& ui, std::string id)
        : ui_(ui), id_(std::move(id)) {}

    DropdownBuilder& size(float width, float height) { width_ = width; height_ = height; return *this; }
    DropdownBuilder& items(std::vector<std::string> value) { items_ = std::move(value); return *this; }
    DropdownBuilder& selected(int value) { selected_ = value; return *this; }
    DropdownBuilder& bind(eui::Signal<int>& signal) {
        selected(signal.get());
        onChange([&signal](int value) { signal.set(value); });
        return *this;
    }
    DropdownBuilder& placeholder(const std::string& value) { placeholder_ = value; return *this; }
    DropdownBuilder& open(bool value = true) { open_ = value; return *this; }
    DropdownBuilder& bindOpen(eui::Signal<bool>& signal) {
        open(signal.get());
        onOpenChange([&signal](bool value) { signal.set(value); });
        return *this;
    }
    DropdownBuilder& itemHeight(float value) { itemHeight_ = std::max(1.0f, value); return *this; }
    DropdownBuilder& style(const DropdownStyle& value) { style_ = value; return *this; }
    DropdownBuilder& theme(const theme::ThemeColorTokens& tokens) {
        style_ = DropdownStyle(tokens);
        metrics_ = tokens.metrics;
        return *this;
    }
    DropdownBuilder& transition(const core::Transition& value) { transition_ = value; return *this; }
    DropdownBuilder& zIndex(int value) { zIndex_ = value; return *this; }
    DropdownBuilder& onChange(std::function<void(int)> callback) { onChange_ = std::move(callback); return *this; }
    DropdownBuilder& onOpenChange(std::function<void(bool)> callback) { onOpenChange_ = std::move(callback); return *this; }

    void build() {
        const int count = static_cast<int>(items_.size());
        const int selected = count > 0 ? std::clamp(selected_, 0, count - 1) : -1;
        const std::string label = selected >= 0 ? items_[selected] : placeholder_;
        const float height = height_ >= 0.0f ? height_ : metrics_.control.control;
        const float itemHeight = itemHeight_ > 0.0f
            ? std::max(metrics_.control.switchHeight, itemHeight_)
            : metrics_.control.menuItem;
        const float popupGap = metrics_.spacing.compact;
        const float popupPadding = metrics_.spacing.small;
        const float popupHeight = itemHeight * static_cast<float>(std::max(1, count)) + popupPadding * 2.0f;
        const float rootHeight = height + popupGap + popupHeight;
        const float visible = open_ ? 1.0f : 0.0f;
        const float popupOffsetY = open_ ? 0.0f : -6.0f;
        const float popupScale = open_ ? 1.0f : 0.96f;
        const std::function<void(int)> onChange = onChange_;
        const std::function<void(bool)> onOpenChange = onOpenChange_;

        ui_.stack(id_)
            .size(width_, rootHeight)
            .zIndex(zIndex_)
            .content([&] {
                ui_.rect(id_ + ".field")
                    .size(width_, height)
                    .states(style_.field, style_.fieldHover, style_.fieldPressed)
                    .radius(style_.radius)
                    .border(metrics_.spacing.hairline, style_.border)
                    .transition(transition_)
                    .onClick([onOpenChange, open = open_] {
                        if (onOpenChange) {
                            onOpenChange(!open);
                        }
                    })
                    .build();

                ui_.text(id_ + ".label")
                    .x(metrics_.spacing.content + metrics_.spacing.micro)
                    .size(std::max(0.0f, width_ - metrics_.spacing.overlay), height)
                    .text(label)
                    .fontSize(metrics_.typography.body)
                    .lineHeight(metrics_.typography.body + metrics_.typography.lineGap)
                    .color(selected >= 0 ? style_.text : style_.mutedText)
                    .verticalAlign(core::VerticalAlign::Center)
                    .build();

                ui_.text(id_ + ".chevron")
                    .x(std::max(0.0f, width_ - metrics_.control.menuItem))
                    .size(metrics_.spacing.large, height)
                    .icon(open_ ? 0xF077 : 0xF078)
                    .fontSize(metrics_.typography.hint)
                    .lineHeight(metrics_.typography.hint + metrics_.typography.lineGapRelaxed)
                    .color(style_.accent)
                    .horizontalAlign(core::HorizontalAlign::Center)
                    .verticalAlign(core::VerticalAlign::Center)
                    .transition(transition_)
                    .animate(core::AnimProperty::TextColor)
                    .build();

                ui_.stack(id_ + ".popup")
                    .y(height + popupGap)
                    .size(width_, popupHeight)
                    .opacity(visible)
                    .translateY(popupOffsetY)
                    .scale(popupScale)
                    .transformOrigin(0.5f, 0.0f)
                    .transition(transition_)
                    .animate(core::AnimProperty::Opacity | core::AnimProperty::Transform)
                    .content([&] {
                        ui_.rect(id_ + ".popup.bg")
                            .size(width_, popupHeight)
                            .color(style_.popup)
                            .radius(style_.radius)
                            .border(metrics_.spacing.hairline, style_.border)
                            .shadow(style_.shadow)
                            .build();

                        ui_.rect(id_ + ".popup.hit")
                            .size(width_, popupHeight)
                            .states(theme::color(0.0f, 0.0f, 0.0f, 0.0f),
                                    theme::color(0.0f, 0.0f, 0.0f, 0.0f),
                                    theme::color(0.0f, 0.0f, 0.0f, 0.0f))
                            .disabled(!open_)
                            .blockPointer()
                            .build();

                        for (int index = 0; index < count; ++index) {
                            const bool active = index == selected;
                            const float itemY = popupPadding + static_cast<float>(index) * itemHeight;
                            ui_.rect(id_ + ".item." + std::to_string(index))
                                .x(popupPadding)
                                .y(itemY)
                                .size(std::max(0.0f, width_ - popupPadding * 2.0f), itemHeight)
                                .states(theme::color(0.0f, 0.0f, 0.0f, 0.0f), style_.optionHover, style_.optionPressed)
                                .radius(std::max(metrics_.radius.tiny, style_.radius - metrics_.radius.tiny))
                                .instantStates()
                                .disabled(!open_)
                                .onClick([onChange, onOpenChange, index] {
                                    if (onChange) {
                                        onChange(index);
                                    }
                                    if (onOpenChange) {
                                        onOpenChange(false);
                                    }
                                })
                                .build();

                            ui_.text(id_ + ".item.label." + std::to_string(index))
                                .x(popupPadding + metrics_.spacing.content)
                                .y(itemY + std::max(0.0f, (itemHeight - metrics_.typography.option -
                                                           metrics_.typography.lineGapTight) * 0.5f))
                                .size(std::max(0.0f, width_ - popupPadding * 2.0f - metrics_.spacing.panel),
                                      metrics_.spacing.large)
                                .text(items_[index])
                                .fontSize(metrics_.typography.option)
                                .lineHeight(metrics_.typography.option + metrics_.typography.lineGapTight)
                                .color(active ? style_.accent : style_.text)
                                .transition(transition_)
                                .animate(core::AnimProperty::TextColor)
                                .build();
                        }
                    })
                    .build();
            })
            .build();
    }

private:
    core::dsl::Ui& ui_;
    std::string id_;
    std::vector<std::string> items_;
    DropdownStyle style_;
    theme::ThemeMetricTokens metrics_;
    core::Transition transition_ = core::Transition::make(0.16f, core::Ease::OutCubic);
    std::function<void(int)> onChange_;
    std::function<void(bool)> onOpenChange_;
    std::string placeholder_ = "Select";
    int selected_ = -1;
    bool open_ = false;
    float width_ = 260.0f;
    float height_ = -1.0f;
    float itemHeight_ = 0.0f;
    int zIndex_ = 20;
};

inline DropdownBuilder dropdown(core::dsl::Ui& ui, const std::string& id) {
    return DropdownBuilder(ui, id);
}

} // namespace components



namespace components {

struct ProgressStyle {
    ProgressStyle() : ProgressStyle(theme::dark()) {}

    explicit ProgressStyle(const theme::ThemeColorTokens& tokens)
        : track(tokens.surfaceHover), fill(tokens.primary) {}

    core::Color track;
    core::Color fill;
};

class ProgressBuilder {
public:
    ProgressBuilder(core::dsl::Ui& ui, std::string id)
        : ui_(ui), id_(std::move(id)) {}

    ProgressBuilder& size(float width, float height) { width_ = width; height_ = height; return *this; }
    ProgressBuilder& value(float value) { value_ = std::clamp(value, 0.0f, 1.0f); return *this; }
    ProgressBuilder& style(const ProgressStyle& value) { style_ = value; return *this; }
    ProgressBuilder& theme(const theme::ThemeColorTokens& tokens) {
        style_ = ProgressStyle(tokens);
        metrics_ = tokens.metrics;
        return *this;
    }
    ProgressBuilder& transition(const core::Transition& value) { transition_ = value; return *this; }
    ProgressBuilder& transition(float duration, core::Ease ease = core::Ease::OutCubic) {
        transition_ = core::Transition::make(duration, ease);
        return *this;
    }

    void build() {
        const float height = height_ >= 0.0f ? height_ : metrics_.control.progress;
        ui_.stack(id_)
            .size(width_, height)
            .content([&] {
                ui_.rect(id_ + ".track")
                    .size(width_, height)
                    .color(style_.track)
                    .radius(height * 0.5f)
                    .build();

                ui_.rect(id_ + ".fill")
                    .size(width_ * value_, height)
                    .color(style_.fill)
                    .radius(height * 0.5f)
                    .transition(transition_)
                    .animate(core::AnimProperty::Frame | core::AnimProperty::Color)
                    .build();
            })
            .build();
    }

private:
    core::dsl::Ui& ui_;
    std::string id_;
    ProgressStyle style_;
    theme::ThemeMetricTokens metrics_;
    core::Transition transition_ = core::Transition::make(0.18f, core::Ease::OutCubic);
    float width_ = 300.0f;
    float height_ = -1.0f;
    float value_ = 0.0f;
};

inline ProgressBuilder progress(core::dsl::Ui& ui, const std::string& id) {
    return ProgressBuilder(ui, id);
}

} // namespace components



namespace components::workshop {

struct CardSliderItem {
    std::string source;
    std::string title;
    std::string subtitle;
    std::string description;
};

struct CardSliderStyle {
    CardSliderStyle() : CardSliderStyle(theme::dark()) {}

    explicit CardSliderStyle(const theme::ThemeColorTokens& tokens) {
        background = tokens.background;
        overlay = theme::color(0.0f, 0.0f, 0.0f, tokens.dark ? 0.74f : 0.58f);
        title = theme::color(1.0f, 1.0f, 1.0f, 0.98f);
        subtitle = theme::color(1.0f, 1.0f, 1.0f, 0.80f);
        description = theme::color(1.0f, 1.0f, 1.0f, 0.70f);
        accent = tokens.primary;
        shadow = theme::color(0.0f, 0.0f, 0.0f, 0.30f);
        button = ButtonStyle(tokens, false);
        button.text = tokens.text;
        button.icon = tokens.text;
        button.radius = tokens.metrics.radius.card;
        radius = tokens.metrics.radius.control;
    }

    core::Color background;
    core::Color overlay;
    core::Color title;
    core::Color subtitle;
    core::Color description;
    core::Color accent;
    core::Color shadow;
    ButtonStyle button;
    float radius = 8.0f;
};

class CardSliderBuilder {
public:
    CardSliderBuilder(core::dsl::Ui& ui, std::string id)
        : ui_(ui), id_(std::move(id)) {}

    CardSliderBuilder& size(float width, float height) { width_ = width; height_ = height; return *this; }
    CardSliderBuilder& items(std::vector<CardSliderItem> value) { items_ = std::move(value); return *this; }
    CardSliderBuilder& currentIndex(int value) { requestedIndex_ = value; hasRequestedIndex_ = true; return *this; }
    CardSliderBuilder& dragOffset(float value) { dragOffset_ = value; return *this; }
    CardSliderBuilder& duration(float seconds) { duration_ = std::max(0.05f, seconds); return *this; }
    CardSliderBuilder& interval(float seconds) { interval_ = std::max(0.10f, seconds); return *this; }
    CardSliderBuilder& cardSpacing(float value) { cardSpacing_ = std::max(0.0f, value); return *this; }
    CardSliderBuilder& autoPlay(bool value = true) { autoPlay_ = value; return *this; }
    CardSliderBuilder& background(bool value = true) { backgroundEnabled_ = value; return *this; }
    CardSliderBuilder& tilt(bool value = true) { tiltEnabled_ = value; return *this; }
    CardSliderBuilder& style(const CardSliderStyle& value) { style_ = value; return *this; }
    CardSliderBuilder& theme(const theme::ThemeColorTokens& tokens) {
        style_ = CardSliderStyle(tokens);
        metrics_ = tokens.metrics;
        return *this;
    }
    CardSliderBuilder& onChange(std::function<void(int)> callback) { onChange_ = std::move(callback); return *this; }

    void build() {
        const int count = static_cast<int>(items_.size());
        const float safeWidth = std::max(1.0f, width_);
        const float safeHeight = std::max(1.0f, height_);
        CardSliderState& state = ui_.state<CardSliderState>(id_);
        initializeState(state, count);

        state.duration = duration_;
        state.interval = interval_;
        state.autoPlay = autoPlay_;
        state.backgroundEnabled = backgroundEnabled_;
        state.tiltEnabled = tiltEnabled_;
        state.dragOffset = dragOffset_;
        if (!tiltEnabled_) {
            state.targetHoverAngle = 0.0f;
        }

        if (count > 0 && hasRequestedIndex_) {
            const int requested = wrapIndex(requestedIndex_, count);
            if (requested != state.current && !state.animating) {
                startSlide(state, requested, shortestDirection(state.current, requested, count), count);
            }
        }

        const core::Transition motion = core::Transition::make(0.10f, core::Ease::OutCubic)
            .animate(core::AnimProperty::Opacity | core::AnimProperty::Transform | core::AnimProperty::Frame);
        const std::function<void(int)> onChange = onChange_;
        CardSliderState* runtimeState = &state;
        const float cardSpacing = cardSpacing_;

        ui_.stack(id_)
            .size(safeWidth, safeHeight)
            .clip()
            .content([&] {
                drawBackground(state, safeWidth, safeHeight);

                if (count == 0) {
                    drawEmpty(safeWidth, safeHeight);
                    return;
                }

                if (needsFrameTick(state)) {
                    ui_.stack(id_ + ".ticker")
                        .size(1.0f, 1.0f)
                        .onFrame([runtimeState](float deltaSeconds) {
                            tick(*runtimeState, deltaSeconds);
                        })
                        .build();
                }

                if (state.autoPlay) {
                    ui_.stack(id_ + ".autoplay")
                        .size(1.0f, 1.0f)
                        .onTimer(state.interval, [runtimeState, count, onChange] {
                            if (!runtimeState->animating && count > 1) {
                                startSlide(*runtimeState, wrapIndex(runtimeState->current + 1, count), 1, count);
                                emitChange(*runtimeState, onChange);
                            }
                        })
                        .build();
                }

                const auto scroll = [runtimeState, count, onChange](const MouseScrollEvent& event) {
                    if (count <= 1 || runtimeState->animating || event.stepY == 0.0f) {
                        return;
                    }
                    const int direction = event.stepY < 0.0f ? 1 : -1;
                    startSlide(*runtimeState, wrapIndex(runtimeState->current + direction, count), direction, count);
                    emitChange(*runtimeState, onChange);
                };

                mouseArea(ui_, id_ + ".input")
                    .size(safeWidth, safeHeight)
                    .zIndex(900)
                    .scrollStep(1.0f)
                    .maxScrollStep(1.0f)
                    .onMove([runtimeState, safeWidth, safeHeight, cardSpacing](const MouseEvent& event) {
                        updateHoverTarget(*runtimeState, event.x, safeWidth, safeHeight, cardSpacing);
                    })
                    .onLeave([runtimeState] {
                        runtimeState->targetHoverAngle = 0.0f;
                    })
                    .onScroll(scroll)
                    .build();

                std::vector<VisibleCard> cards = visibleCards(state, count);
                applyDragOffset(cards, state, safeWidth, safeHeight, cardSpacing, count);
                std::stable_sort(cards.begin(), cards.end(), [](const VisibleCard& left, const VisibleCard& right) {
                    return cardZ(left.slot) < cardZ(right.slot);
                });
                for (const VisibleCard& card : cards) {
                    drawCard(card, state, safeWidth, safeHeight, motion, onChange);
                }

                drawInfo(state, safeWidth, safeHeight, motion);
            })
            .build();
    }

private:
    struct CardSliderState {
        int current = 0;
        int from = 0;
        int to = 0;
        int direction = 1;
        int lastDirection = 1;
        float linearProgress = 1.0f;
        float progress = 1.0f;
        float hoverAngle = 0.0f;
        float targetHoverAngle = 0.0f;
        float duration = 0.8f;
        float interval = 2.0f;
        bool animating = false;
        bool initialized = false;
        bool autoPlay = false;
        bool backgroundEnabled = true;
        bool tiltEnabled = true;
        float dragOffset = 0.0f;
    };

    struct CardRect {
        float x = 0.0f;
        float y = 0.0f;
        float width = 0.0f;
        float height = 0.0f;
    };

    struct CardVisual {
        float scale = 1.0f;
        float opacity = 1.0f;
        float rotation = 0.0f;
    };

    struct VisibleCard {
        float slot = 0.0f;
        int index = 0;
        float opacityFactor = 1.0f;
    };

    static constexpr float kPi = 3.14159265358979323846f;
    static constexpr float kBaseItemWidth = 250.0f;
    static constexpr float kBaseItemHeight = 400.0f;

    static int wrapIndex(int index, int count) {
        if (count <= 0) {
            return 0;
        }
        int wrapped = index % count;
        if (wrapped < 0) {
            wrapped += count;
        }
        return wrapped;
    }

    static int shortestDirection(int from, int to, int count) {
        if (count <= 1 || from == to) {
            return 1;
        }
        int step = (to - from) % count;
        if (step < 0) {
            step += count;
        }
        if (step > count / 2) {
            step -= count;
        }
        return step >= 0 ? 1 : -1;
    }

    static float easeOutCubic(float t) {
        t = std::clamp(t, 0.0f, 1.0f);
        return 1.0f - std::pow(1.0f - t, 3.0f);
    }

    static void initializeState(CardSliderState& state, int count) {
        if (!state.initialized) {
            state.current = count > 0 ? 0 : -1;
            state.from = state.current;
            state.to = state.current;
            state.initialized = true;
        }
        if (count <= 0) {
            state.current = state.from = state.to = -1;
            state.animating = false;
            state.progress = 1.0f;
            state.linearProgress = 1.0f;
            return;
        }
        state.current = wrapIndex(state.current, count);
        state.from = wrapIndex(state.from, count);
        state.to = wrapIndex(state.to, count);
    }

    static void startSlide(CardSliderState& state, int index, int direction, int count) {
        if (count <= 1 || index == state.current || state.animating) {
            return;
        }
        state.from = state.current;
        state.to = wrapIndex(index, count);
        state.direction = direction >= 0 ? 1 : -1;
        state.lastDirection = state.direction;
        state.current = state.to;
        state.linearProgress = 0.0f;
        state.progress = 0.0f;
        state.animating = true;
    }

    static void emitChange(const CardSliderState& state, const std::function<void(int)>& onChange) {
        if (onChange && state.current >= 0) {
            onChange(state.current);
        }
    }

    static void tick(CardSliderState& state, float deltaSeconds) {
        const float clampedDelta = std::clamp(deltaSeconds, 0.0f, 0.08f);
        if (state.animating) {
            state.linearProgress = std::min(1.0f, state.linearProgress + clampedDelta / std::max(0.05f, state.duration));
            state.progress = easeOutCubic(state.linearProgress);
            if (state.linearProgress >= 1.0f) {
                state.progress = 1.0f;
                state.from = state.to = state.current;
                state.animating = false;
            }
        }

        state.hoverAngle += (state.targetHoverAngle - state.hoverAngle) *
            (1.0f - std::exp(-16.0f * clampedDelta));
        if (std::fabs(state.hoverAngle - state.targetHoverAngle) < 0.0009f) {
            state.hoverAngle = state.targetHoverAngle;
        }
    }

    static bool needsFrameTick(const CardSliderState& state) {
        return state.animating || std::fabs(state.hoverAngle - state.targetHoverAngle) >= 0.0009f;
    }

    static void updateHoverTarget(CardSliderState& state,
                                  float pointerX,
                                  float width,
                                  float height,
                                  float cardSpacing) {
        if (!state.tiltEnabled) {
            state.targetHoverAngle = 0.0f;
            return;
        }
        const CardRect rect = cardRect(0.0f, width, height, cardSpacing);
        const float centerX = rect.x + rect.width * 0.5f;
        const float amount = std::clamp((pointerX - centerX) / std::max(1.0f, rect.width) * 2.0f, -1.0f, 1.0f);
        state.targetHoverAngle = amount * 12.0f * kPi / 180.0f;
    }

    static int sideIndex(const CardSliderState& state, int side, int count) {
        return wrapIndex(state.current + side, count);
    }

    static std::vector<VisibleCard> visibleCards(const CardSliderState& state, int count) {
        std::vector<VisibleCard> cards;
        if (count <= 0 || state.current < 0) {
            return cards;
        }
        if (count == 1) {
            cards.push_back({0.0f, state.current, 1.0f});
            return cards;
        }
        if (count == 2 && !state.animating) {
            const int side = -state.lastDirection;
            cards.push_back({0.0f, state.current, 1.0f});
            cards.push_back({static_cast<float>(side), sideIndex(state, side, count), 1.0f});
            return cards;
        }
        if (state.animating) {
            const float p = state.progress;
            const float d = static_cast<float>(state.direction);
            if (count == 2) {
                cards.push_back({-d * p, state.from, 1.0f});
                cards.push_back({d * (1.0f - p), state.to, 1.0f});
                return cards;
            }

            const int oldSide = wrapIndex(state.from - state.direction, count);
            const int newSide = wrapIndex(state.to + state.direction, count);
            cards.push_back({-d * p, state.from, 1.0f});
            cards.push_back({d * (1.0f - p), state.to, 1.0f});
            if (oldSide == newSide) {
                cards.push_back({-d + 2.0f * d * p, oldSide, 1.0f});
            } else {
                cards.push_back({-d, oldSide, 1.0f - p});
                cards.push_back({d, newSide, p});
            }
            return cards;
        }

        cards.push_back({0.0f, state.current, 1.0f});
        cards.push_back({-1.0f, sideIndex(state, -1, count), 1.0f});
        cards.push_back({1.0f, sideIndex(state, 1, count), 1.0f});
        return cards;
    }

    static void applyDragOffset(std::vector<VisibleCard>& cards,
                                const CardSliderState& state,
                                float width,
                                float height,
                                float cardSpacing,
                                int count) {
        if (cards.empty() || state.animating || std::fabs(state.dragOffset) < 0.01f) {
            return;
        }

        const CardRect base = cardRect(0.0f, width, height, cardSpacing);
        const float slotStep = base.width * 1.10f + cardSpacing;
        const float slotOffset = std::clamp(state.dragOffset / std::max(1.0f, slotStep), -1.0f, 1.0f);

        if (count == 2) {
            const int side = state.dragOffset < 0.0f ? 1 : -1;
            cards.clear();
            cards.push_back({slotOffset, state.current, 1.0f});
            cards.push_back({
                static_cast<float>(side) + slotOffset,
                sideIndex(state, side, count),
                1.0f,
            });
            return;
        }

        for (VisibleCard& card : cards) {
            card.slot += slotOffset;
        }
    }

    static CardRect cardRect(float slot, float width, float height, float cardSpacing) {
        const float scale = std::min({
            width / (kBaseItemWidth * 3.0f),
            std::max(1.0f, height - 56.0f) / (kBaseItemHeight * 1.25f),
            1.0f
        });
        const float cardW = std::round(kBaseItemWidth * scale);
        const float cardH = std::round(kBaseItemHeight * scale);
        const float cx = std::round(width * 0.5f);
        const float cy = std::round(height * 0.5f - 10.0f);
        return {
            std::round(cx - cardW * 0.5f + slot * (cardW * 1.10f + cardSpacing)),
            std::round(cy - cardH * 0.5f),
            cardW,
            cardH
        };
    }

    CardRect cardRect(float slot, float width, float height) const {
        return cardRect(slot, width, height, cardSpacing_);
    }

    static CardVisual cardVisual(float slot, float hoverAngle) {
        const float amount = std::min(1.0f, std::fabs(slot));
        return {
            1.20f + (0.90f - 1.20f) * amount,
            0.80f + (0.40f - 0.80f) * amount,
            (-25.0f * slot * kPi / 180.0f) + hoverAngle * (1.0f - amount)
        };
    }

    static int cardZ(float slot) {
        return 100 - static_cast<int>(std::fabs(slot) * 20.0f);
    }

    void drawBackground(const CardSliderState& state, float width, float height) {
        ui_.rect(id_ + ".base")
            .size(width, height)
            .color(style_.background)
            .build();

        if (!state.backgroundEnabled || state.current < 0 || items_.empty()) {
            return;
        }

        if (state.animating && state.from >= 0 && state.to >= 0) {
            drawBackgroundImage(".bg.from", state.from, 1.0f - state.progress, -0.25f * state.direction * state.progress, width, height);
            drawBackgroundImage(".bg.to", state.to, state.progress, 0.25f * state.direction * (1.0f - state.progress), width, height);
        } else {
            drawBackgroundImage(".bg.current", state.current, 1.0f, 0.0f, width, height);
        }

        ui_.rect(id_ + ".overlay")
            .size(width, height)
            .color(style_.overlay)
            .build();
    }

    void drawBackgroundImage(const std::string& suffix, int index, float opacity, float offsetFactor, float width, float height) {
        if (index < 0 || index >= static_cast<int>(items_.size()) || opacity <= 0.0f) {
            return;
        }
        const float bgW = width * 1.80f;
        const float bgH = height * 1.80f;
        ui_.image(id_ + suffix)
            .position((width - bgW) * 0.5f + offsetFactor * width, (height - bgH) * 0.5f)
            .size(bgW, bgH)
            .source(items_[static_cast<std::size_t>(index)].source)
            .cover()
            .opacity(opacity)
            .build();
    }

    void drawCard(const VisibleCard& visible,
                  CardSliderState& state,
                  float width,
                  float height,
                  const core::Transition& motion,
                  const std::function<void(int)>& onChange) {
        if (visible.index < 0 || visible.index >= static_cast<int>(items_.size())) {
            return;
        }

        const CardRect base = cardRect(visible.slot, width, height);
        const CardVisual visual = cardVisual(visible.slot, state.hoverAngle);
        const float cardW = base.width * visual.scale;
        const float cardH = base.height * visual.scale;
        const float x = base.x + (base.width - cardW) * 0.5f;
        const float y = base.y + (base.height - cardH) * 0.5f;
        const float opacity = std::clamp((visual.opacity + 0.2f * (1.0f - std::min(1.0f, std::fabs(visible.slot)))) * visible.opacityFactor, 0.0f, 1.0f);
        const std::string cardId = id_ + ".card." + std::to_string(visible.index);

        ui_.stack(cardId)
            .position(x, y)
            .size(cardW, cardH)
            .zIndex(cardZ(visible.slot))
            .opacity(opacity)
            .rotateY(visual.rotation)
            .perspective(620.0f)
            .transformOrigin(0.5f, 0.5f)
            .transition(motion)
            .animate(core::AnimProperty::Frame | core::AnimProperty::Opacity | core::AnimProperty::Transform)
            .content([&] {
                ui_.rect(cardId + ".shadow")
                    .position(0.0f, 8.0f)
                    .size(cardW, cardH)
                    .color(theme::color(0.0f, 0.0f, 0.0f, 0.0f))
                    .radius(style_.radius)
                    .shadow(30.0f, 0.0f, 10.0f, style_.shadow)
                    .build();

                ui_.image(cardId + ".image")
                    .size(cardW, cardH)
                    .source(items_[static_cast<std::size_t>(visible.index)].source)
                    .cover()
                    .radius(style_.radius)
                    .build();

                const float shadeAlpha = 0.58f * (1.0f - visual.opacity);
                if (shadeAlpha > 0.01f) {
                    ui_.rect(cardId + ".shade")
                        .size(cardW, cardH)
                        .color(theme::color(0.0f, 0.0f, 0.0f, shadeAlpha))
                        .radius(style_.radius)
                        .build();
                }

            })
            .build();
    }

    void drawInfo(const CardSliderState& state, float width, float height, const core::Transition& motion) {
        if (state.current < 0 || state.current >= static_cast<int>(items_.size())) {
            return;
        }

        const float p = state.animating ? state.progress : 1.0f;
        const float oldOpacity = 1.0f - std::min(1.0f, p * 1.8f);
        const float newOpacity = std::min(1.0f, std::max(0.0f, (p - 0.35f) / 0.65f));
        if (state.animating && state.from >= 0 && oldOpacity > 0.0f) {
            drawInfoBlock(".info.old", items_[static_cast<std::size_t>(state.from)], oldOpacity, -120.0f * p, state.hoverAngle, width, height, motion);
        }
        drawInfoBlock(".info.current", items_[static_cast<std::size_t>(state.current)], newOpacity, 40.0f * (1.0f - newOpacity), state.hoverAngle, width, height, motion);
    }

    void drawInfoBlock(const std::string& suffix,
                       const CardSliderItem& item,
                       float opacity,
                       float offsetY,
                       float hoverAngle,
                       float width,
                       float height,
                       const core::Transition& motion) {
        if (opacity <= 0.0f) {
            return;
        }

        const CardRect rect = cardRect(0.0f, width, height);
        const float ratio = rect.width / kBaseItemWidth;
        const float infoW = std::max(160.0f, rect.width * 1.55f);
        const float baseX = width * 0.5f - rect.width * 1.5f + rect.width / 1.5f;
        const float baseY = rect.y + rect.height - rect.height / 8.0f + offsetY;
        const std::string rootId = id_ + suffix;

        ui_.stack(rootId)
            .position(baseX, baseY - 96.0f * ratio)
            .size(infoW, 150.0f * ratio)
            .zIndex(250)
            .opacity(opacity)
            .rotateY(hoverAngle * 0.35f)
            .perspective(620.0f)
            .transformOrigin(0.0f, 0.5f)
            .transition(motion)
            .animate(core::AnimProperty::Frame | core::AnimProperty::Opacity | core::AnimProperty::Transform)
            .content([&] {
                ui_.text(rootId + ".title")
                    .size(infoW, 46.0f * ratio)
                    .text(upperAscii(item.title))
                    .fontSize(std::max(metrics_.typography.control, rect.width * 0.18f))
                    .lineHeight(std::max(metrics_.typography.title, rect.width * 0.20f))
                    .fontWeight(860)
                    .color(style_.title)
                    .build();

                ui_.rect(rootId + ".mark.a")
                    .position(0.0f, 54.0f * ratio)
                    .size(20.0f * ratio, 5.0f * ratio)
                    .color(style_.title)
                    .radius(2.0f * ratio)
                    .build();
                ui_.rect(rootId + ".mark.b")
                    .position(0.0f, 94.0f * ratio)
                    .size(60.0f * ratio, 2.0f * ratio)
                    .color(style_.title)
                    .radius(1.0f * ratio)
                    .build();

                ui_.text(rootId + ".subtitle")
                    .position(40.0f * ratio, 38.0f * ratio)
                    .size(std::max(0.0f, infoW - 40.0f * ratio), 34.0f * ratio)
                    .text(upperAscii(item.subtitle))
                    .fontSize(std::max(metrics_.typography.hint, rect.width * 0.12f))
                    .lineHeight(std::max(metrics_.typography.input, rect.width * 0.14f))
                    .fontWeight(760)
                    .color(style_.subtitle)
                    .build();

                ui_.text(rootId + ".description")
                    .position(0.0f, 88.0f * ratio)
                    .size(infoW, 42.0f * ratio)
                    .text(item.description)
                    .fontSize(std::max(metrics_.typography.micro, rect.width * 0.062f))
                    .lineHeight(std::max(metrics_.typography.option, rect.width * 0.082f))
                    .fontWeight(540)
                    .wrap(true)
                    .color(style_.description)
                    .build();
            })
            .build();
    }

    void drawEmpty(float width, float height) {
        ui_.text(id_ + ".empty")
            .size(width, height)
            .text("No cards")
            .fontSize(metrics_.typography.control)
            .lineHeight(metrics_.typography.control + metrics_.typography.lineGapLoose)
            .color(style_.description)
            .horizontalAlign(core::HorizontalAlign::Center)
            .verticalAlign(core::VerticalAlign::Center)
            .build();
    }

    static std::string upperAscii(std::string value) {
        for (char& ch : value) {
            if (ch >= 'a' && ch <= 'z') {
                ch = static_cast<char>(ch - 'a' + 'A');
            }
        }
        return value;
    }

    core::dsl::Ui& ui_;
    std::string id_;
    std::vector<CardSliderItem> items_;
    CardSliderStyle style_;
    theme::ThemeMetricTokens metrics_;
    std::function<void(int)> onChange_;
    float width_ = 900.0f;
    float height_ = 560.0f;
    float duration_ = 0.8f;
    float interval_ = 2.0f;
    float cardSpacing_ = 0.0f;
    int requestedIndex_ = 0;
    bool hasRequestedIndex_ = false;
    bool autoPlay_ = false;
    bool backgroundEnabled_ = true;
    bool tiltEnabled_ = true;
    float dragOffset_ = 0.0f;
};

inline CardSliderBuilder cardSlider(core::dsl::Ui& ui, const std::string& id) {
    return CardSliderBuilder(ui, id);
}

} // namespace components::workshop

}
