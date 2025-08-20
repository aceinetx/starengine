#pragma once
#include <raylib.h>

namespace star {
/** RaylibEvent
 *
 * Describes an event that was sent by raylib
 */
struct RaylibEvent {
  enum { kNothing, kKeyboard, kMouse } type;

  int button;
  enum { kNone, kDown, kUp, kPressed } state;

  RaylibEvent() : type(kNothing), state(kNone) {
  }
};
} // namespace star
