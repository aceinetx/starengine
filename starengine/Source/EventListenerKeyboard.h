#pragma once

#include "EventListener.h"
#include "Macros.h"
#include "RaylibEvent.h"
#include <functional>

namespace star {
/** EventListenerKeyboard
 *
 * Listens to keyboard events
 */
class EventListenerKeyboard : public EventListener {
public:
  std::function<bool(KeyboardKey)> onKeyPressed;
  std::function<bool(KeyboardKey)> onKeyDown;
  std::function<bool(KeyboardKey)> onKeyUp;

  bool listen(const RaylibEvent& event);

  CREATE_FUNC_LISTENER(EventListenerKeyboard);
};
} // namespace star
