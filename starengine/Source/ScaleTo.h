#pragma once
#include "Action.h"

namespace star {
/** ScaleTo
 *
 * Action that scales a node to a certain scale in a given amount of time
 */
class ScaleTo : public Action {
protected:
  /** initial scale of the target */
  float p_initial;
  /** goal scale */
  float p_scale;

public:
  void update(float time) override;
  void startWithTarget(Node* target) override;

  /** Create an autoreleased action */
  static ScaleTo* create(float duration, float scale);
};
} // namespace star
