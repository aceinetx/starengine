#include "EventDispatcher.h"
#include "Director.h"
#include "EventListener.h"
#include "RaylibEvent.h"
#include <algorithm>

using namespace star;

EventDispatcher EventDispatcher::p_instance;

EventDispatcher* EventDispatcher::getInstance() {
  return &p_instance;
}

EventDispatcher::~EventDispatcher() {
}

bool EventDispatcher::dispatchEvent(const RaylibEvent& event, Node* startNode) {
  //  check for a listener on the node itself
  fmt::println("[star] Dispatching event ({}, {}, {})", (int)event.type, (int)event.state,
               (int)event.button);

  for (auto* listener : p_listeners) {
    if (listener->p_attachedNode == startNode) {
      if (listener->listen(event))
        return true;
    }
  }

  // check for a listener on the node's children
  for (auto* listener : p_listeners) {
    for (auto* child : startNode->getChildren()) {
      if (listener->p_attachedNode == child) {
        if (listener->listen(event))
          return true;
      }
    }
  }

  return false;
}

void EventDispatcher::addListenerWithSceneGraphPriority(EventListener* listener, Node* node) {
  listener->p_attachedNode = node;
  p_listeners.push_back(listener);
}

void EventDispatcher::removeAllListenersFromTarget(Node* target) {
  for (size_t i = 0; i < p_listeners.size(); i++) {
    if (p_listeners[i]->p_attachedNode == target) {
      p_listeners.erase(p_listeners.begin() + i);
      i--;
    }
  }
}
