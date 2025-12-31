#pragma once
#include <raylib.h>

namespace star {
/** RaylibEvent
 *
 * Describes an event that was sent by raylib
 */
struct RaylibEvent {
  /** type of the event */
  enum { kNothing, kKeyboard, kMouse } type{kNothing};

  /** button id */
  int button;
  /** state of the button */
  enum { kNone, kDown, kUp, kPressed } state{kNone};

  RaylibEvent() = default;
};
} // namespace star
