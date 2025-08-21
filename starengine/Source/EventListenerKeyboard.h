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
  /** callback to run when a key is pressed */
  std::function<bool(KeyboardKey)> onKeyPressed;
  /** callback to run when a key is down */
  std::function<bool(KeyboardKey)> onKeyDown;
  /** callback to run when a key is up */
  std::function<bool(KeyboardKey)> onKeyUp;

  /** Listen to an event, true if successfully dispatched, false if we should continue dispatching
   * events */
  bool listen(const RaylibEvent& event);

  CREATE_FUNC_NO_INIT(EventListenerKeyboard);
};
} // namespace star
