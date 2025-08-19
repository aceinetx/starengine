#pragma once
#include "Vec2.h"
#include <fmt/base.h>

namespace fmt {
template <> class formatter<star::Vec2> {
public:
	constexpr auto parse(format_parse_context& ctx) {
		return ctx.begin();
	}
	template <typename Context> constexpr auto format(star::Vec2 const& obj, Context& ctx) const {
		return format_to(ctx.out(), "({},{})", obj.x, obj.y);
	}
};
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
