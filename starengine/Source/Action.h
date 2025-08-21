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
  /**
   * Is the action done?
   */
  bool isDone();
  /**
   * Step the current action by one tick
   */
  virtual void step(float dt);
  virtual void update(float time);
  /** Setup an action for a specific target
   *
   * ! DOES NOT START THE ACTION, NAME INHERITED FROM COCOS2D-X !
   */
  virtual void startWithTarget(Node* target);
  /**
   * Get the action duration
   */
  virtual float getDuration();

  friend class ActionManager;
  friend class ActionEase;
};
} // namespace star
