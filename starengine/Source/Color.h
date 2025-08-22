#pragma once
#include <raylib.h>
#include <stdint.h>

namespace star {
/** Represents a color in RGBA values */
struct Color4B {
  uint8_t r, g, b, a;

  Color toRaylib() const;
};
} // namespace star