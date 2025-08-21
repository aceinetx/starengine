#pragma once
#include "Action.h"

namespace star {
/** ScaleTo
 *
 * Action that scales a node to a certain scale in a given amount of time
 */
class ScaleTo : public Action {
protected:
  float p_initial;
  float p_scale;

public:
  void update(float time) override;

  static ScaleTo* create(float duration, float scale);
};
} // namespace star
