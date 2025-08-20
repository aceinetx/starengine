#pragma once
#include "Node.h"
#include "Object.h"

namespace star {
class ActionManager;
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

  friend class ActionManager;
};
} // namespace star
