#include "Color.h"
#include <raylib.h>

using namespace star;

Color Color4B::toRaylib() const {
  return CLITERAL(Color){r, g, b, a};
}