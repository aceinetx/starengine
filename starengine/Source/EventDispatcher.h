#pragma once
#include "Node.h"
#include "RaylibEvent.h"
#include <raylib.h>

namespace star {
class EventListener;

/** EventDispatcher
 *
 * Controls, dispatches, and runs event's callbacks
 */
class EventDispatcher {
protected:
  static EventDispatcher p_instance;

  std::vector<EventListener*> p_listeners;

public:
  static EventDispatcher* getInstance();
  ~EventDispatcher();

  /**
   * Dispatch an event starting from a node
   *
   * Events will be dispatched from top to bottom by the scene graph, like this:
   *
   * Node (1)
   * - Label (2)
   * - Label (3)
   *
   * Node (4)
   *
   */
  bool dispatchEvent(const RaylibEvent& event, Node* startNode);

  /**
   * Add an event listener with scene graph priority, check out EventDispatcher::dispatchEvent to
   * see how would it be dispatched
   */
  void addListenerWithSceneGraphPriority(EventListener* listener, Node* node);
};
} // namespace star
