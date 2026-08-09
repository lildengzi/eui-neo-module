module;

#include "core/layout.h"
#include "core/animation.h"
#include "core/render/render_types.h"
#include "core/render/text_types.h"
#include "core/input/input_types.h"

export module eui.types;

export namespace eui {
using Align = core::Align;
using AnimProperty = core::AnimProperty;
using Ease = core::Ease;
using Transition = core::Transition;
using Color = core::Color;
using Vec2 = core::Vec2;
using Vec3 = core::Vec3;
using Rect = core::Rect;
using SizeValue = core::SizeValue;
using SizeMode = core::SizeMode;
using LayoutType = core::LayoutType;
using Gradient = core::Gradient;
using GradientDirection = core::GradientDirection;
using Border = core::Border;
using Shadow = core::Shadow;
using Transform = core::Transform;
using TransformMatrix = core::TransformMatrix;
using HorizontalAlign = core::HorizontalAlign;
using VerticalAlign = core::VerticalAlign;
using TextStyle = core::TextStyle;
using CursorShape = core::CursorShape;
using PointerEvent = core::PointerEvent;
}