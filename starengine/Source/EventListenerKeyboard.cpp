#include "EventListenerKeyboard.h"
#include "RaylibEvent.h"
#include <raylib.h>

bool star::EventListenerKeyboard::listen(const RaylibEvent& event) {
  if (event.type != RaylibEvent::kKeyboard)
    return false;
  if (event.state == RaylibEvent::kPressed && onKeyPressed)
    return onKeyPressed((KeyboardKey)event.button);
  else if (event.state == RaylibEvent::kDown && onKeyDown)
    return onKeyDown((KeyboardKey)event.button);
  else if (event.state == RaylibEvent::kUp && onKeyUp)
    return onKeyUp((KeyboardKey)event.button);
  return false;
}
