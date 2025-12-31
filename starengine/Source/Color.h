#pragma once
#include <cstdint>
#include <raylib.h>

namespace star {
/** Represents a color in RGBA values */
struct Color4B {
  uint8_t r, g, b, a;

  [[nodiscard]] Color toRaylib() const;
};
} // namespace star
