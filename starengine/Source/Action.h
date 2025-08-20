#pragma once
#include "Node.h"
#include "Object.h"

namespace star {
class Action : public Object {
protected:
  Node* p_target;
  float* p_value;
  float p_duration;
  float p_time;

public:
  virtual void update(float dt) = 0;
};
} // namespace star
