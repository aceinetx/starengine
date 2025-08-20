#pragma once
#include "Action.h"

namespace star {
class MoveTo : public Action {
protected:
  Vec2 p_position;
  Vec2 p_initialPosition;
  Vec2 p_diff;

public:
  void update(float time) override;

  static MoveTo* create(float duration, Vec2 pos);
};
} // namespace star
