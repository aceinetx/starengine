#pragma once
#include "Node.h"
#include "Object.h"

namespace star {
class ActionManager;
class ActionEase;

/** Action
 *
 * Base class for every action
 *
 * Controls the action flow
 */
class Action : public Object {
protected:
  float p_duration = 0.0f;
  float p_elapsed = 0.0f;
  bool p_done = false;
  Node* p_target = nullptr;

public:
  bool isDone();
  virtual void step(float dt);
  virtual void update(float time);
  virtual void startWithTarget(Node* target);
  virtual float getDuration();

  friend class ActionManager;
  friend class ActionEase;
};
} // namespace star
