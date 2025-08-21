#pragma once
#include "Action.h"

namespace star {
/** RotateTo
 *
 * Action that rotates a node in a given amount of time
 */
class RotateTo : public Action {
protected:
  /** end rotation */
  float p_rotation;
  /** initial rotation */
  float p_initialRotation;

public:
  void update(float time) override;
  void startWithTarget(Node* target) override;

  /** Create an autoreleased action */
  static RotateTo* create(float duration, float rotation);
};
} // namespace star
