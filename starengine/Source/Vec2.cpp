#include "Vec2.h"
#include <raylib.h>

using namespace star;

Vec2::Vec2() : x(0), y(0) {
}

Vec2::Vec2(float x, float y) : x(x), y(y) {
}

Vec2 Vec2::operator/(float v) {
  return Vec2(x / v, y / v);
}

Vec2 Vec2::operator*(float v) {
  return Vec2(x * v, y * v);
}

Vec2 Vec2::operator-(Vec2 vec) {
  return Vec2(x - vec.x, y - vec.y);
}

Vec2 Vec2::operator+(Vec2 vec) {
  return Vec2(x + vec.x, y + vec.y);
}

void Vec2::operator-=(Vec2 vec) {
  x -= vec.x;
  y -= vec.y;
}

void Vec2::operator+=(Vec2 vec) {
  x += vec.x;
  y += vec.y;
}
