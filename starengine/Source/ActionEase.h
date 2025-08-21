#pragma once
#include "Action.h"

namespace star {
/** ActionEase
 *
 * Represents an action that has an easing
 */
class ActionEase : public Action {
protected:
  /** inner action */
  Action* p_inner;

public:
  ~ActionEase();

  /**
   * Get the inner action
   */
  virtual Action* getInnerAction();

  virtual void startWithTarget(Node* target) override;
  virtual void update(float time) override;
};

#define DECLARE_EASING_CLASS(name)                                                                 \
  class name : public ActionEase {                                                                 \
  public:                                                                                          \
    static name* create(Action* inner);                                                            \
    virtual void update(float dt);                                                                 \
  }

#define DECLARE_EASING_CLASS_RATE(name)                                                            \
  class name : public ActionEase {                                                                 \
  protected:                                                                                       \
    float p_rate;                                                                                  \
                                                                                                   \
  public:                                                                                          \
    static name* create(Action* inner, float rate);                                                \
    virtual void update(float dt);                                                                 \
  }

DECLARE_EASING_CLASS_RATE(EaseIn);
DECLARE_EASING_CLASS_RATE(EaseOut);
DECLARE_EASING_CLASS_RATE(EaseInOut);

DECLARE_EASING_CLASS(EaseQuadraticIn);
DECLARE_EASING_CLASS(EaseQuadraticOut);
DECLARE_EASING_CLASS(EaseQuadraticInOut);

DECLARE_EASING_CLASS(EaseSineIn);
DECLARE_EASING_CLASS(EaseSineOut);
DECLARE_EASING_CLASS(EaseSineInOut);

DECLARE_EASING_CLASS(EaseQuadIn);
DECLARE_EASING_CLASS(EaseQuadOut);
DECLARE_EASING_CLASS(EaseQuadInOut);

DECLARE_EASING_CLASS(EaseCubicIn);
DECLARE_EASING_CLASS(EaseCubicOut);
DECLARE_EASING_CLASS(EaseCubicInOut);

DECLARE_EASING_CLASS(EaseQuartIn);
DECLARE_EASING_CLASS(EaseQuartOut);
DECLARE_EASING_CLASS(EaseQuartInOut);

DECLARE_EASING_CLASS(EaseQuintIn);
DECLARE_EASING_CLASS(EaseQuintOut);
DECLARE_EASING_CLASS(EaseQuintInOut);

DECLARE_EASING_CLASS(EaseExpoIn);
DECLARE_EASING_CLASS(EaseExpoOut);
DECLARE_EASING_CLASS(EaseExpoInOut);

DECLARE_EASING_CLASS(EaseCircIn);
DECLARE_EASING_CLASS(EaseCircOut);
DECLARE_EASING_CLASS(EaseCircInOut);

DECLARE_EASING_CLASS(EaseBackIn);
DECLARE_EASING_CLASS(EaseBackOut);
DECLARE_EASING_CLASS(EaseBackInOut);

DECLARE_EASING_CLASS(EaseBounceIn);
DECLARE_EASING_CLASS(EaseBounceOut);
DECLARE_EASING_CLASS(EaseBounceInOut);

} // namespace star
