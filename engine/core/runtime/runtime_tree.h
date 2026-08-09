#pragma once

#include "core/dsl.h"

#include <algorithm>
#include <memory>
#include <vector>

namespace core::dsl {

inline const std::vector<const Element*>& orderedElements(const Ui& ui) {
    return ui.orderedRoots();
}

inline const std::vector<const Element*>& orderedElements(const Element& element) {
    return element.orderedChildren;
}

} // namespace core::dsl
