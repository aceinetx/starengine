#pragma once

namespace star {
struct Vec2 {
	float x, y;

	Vec2();
	Vec2(float x, float y);

	Vec2 operator/(float v);
	Vec2 operator*(float v);

	Vec2 operator-(Vec2 vec);
	Vec2 operator+(Vec2 vec);
};
} // namespace star
