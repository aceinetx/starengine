#pragma once
#include "Action.h"

namespace star {
/** MoveTo
 *
 * Action that moves a node by certain position in a given amount of time
 */
class MoveTo : public Action {
protected:
  Vec2 p_position;
  Vec2 p_initialPosition;

public:
  void update(float time) override;

  static MoveTo* create(float duration, Vec2 pos);
};
} // namespace star
