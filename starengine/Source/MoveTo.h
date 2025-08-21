#pragma once
#include "Action.h"

namespace star {
/** MoveTo
 *
 * Action that moves a node by certain position in a given amount of time
 */
class MoveTo : public Action {
protected:
  /** position to move to */
  Vec2 p_position;
  /** initial position of the target */
  Vec2 p_initialPosition;

public:
  void update(float time) override;
  void startWithTarget(Node* target) override;

  /** Create an autoreleased action */
  static MoveTo* create(float duration, Vec2 pos);
};
} // namespace star
