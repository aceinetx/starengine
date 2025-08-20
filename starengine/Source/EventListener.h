#pragma once
#include "EventDispatcher.h"
#include "Object.h"
#include "RaylibEvent.h"

namespace star {
/** EventListener
 *
 * Listens to events
 */
class EventListener : public Object {
protected:
  Node* p_attachedNode;

public:
  /**
   * Listen to an event
   *
   * Returns true if an event has been successfully dispatched, false if not and we should continue
   * down the scene graph calling every single event listener
   */
  virtual bool listen(const RaylibEvent& event) = 0;

  friend class EventDispatcher;
};
} // namespace star
