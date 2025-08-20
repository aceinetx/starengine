/**
 * \file
 *
 * This file contains formatters for classes like star::Vec2 and raylib's Vector2
 */
#pragma once
#include "Vec2.h"
#include <fmt/base.h>

namespace fmt {
/** Formats star::Vec2 in this way: (12.3, 6.7)
 */
template <> class formatter<star::Vec2> {
public:
  constexpr auto parse(format_parse_context& ctx) {
    return ctx.begin();
  }
  template <typename Context> constexpr auto format(star::Vec2 const& obj, Context& ctx) const {
    return format_to(ctx.out(), "({},{})", obj.x, obj.y);
  }
};

/** Formats raylib's Vector2 in this way: (12.3, 6.7)
 */
template <> class formatter<Vector2> {
public:
  constexpr auto parse(format_parse_context& ctx) {
    return ctx.begin();
  }
  template <typename Context> constexpr auto format(Vector2 const& obj, Context& ctx) const {
    return format_to(ctx.out(), "({},{})", obj.x, obj.y);
  }
};
} // namespace fmt
