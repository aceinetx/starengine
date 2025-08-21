#include "ActionEase.h"
#include "Macros.h"
#include "TweenFunction.h"

using namespace star;

ActionEase::~ActionEase() {
  if (p_inner)
    p_inner->release();
}

Action* ActionEase::getInnerAction() {
  return p_inner;
}

void ActionEase::startWithTarget(Node* target) {
  STARASSERT(target && p_inner, "target && p_inner failed");
  Action::startWithTarget(target);
  p_inner->startWithTarget(target);
}

void ActionEase::update(float time) {
  Action::update(time);
}

#define IMPL_EASING_CLASS(name, tweenFunc)                                                         \
  name* name::create(Action* inner) {                                                              \
    auto pRet = new name();                                                                        \
    if (pRet) {                                                                                    \
      pRet->autorelease();                                                                         \
    } else                                                                                         \
      return nullptr;                                                                              \
    pRet->p_inner = inner;                                                                         \
    pRet->p_inner->retain();                                                                       \
    pRet->p_duration = pRet->p_inner->getDuration();                                               \
    return pRet;                                                                                   \
  }                                                                                                \
  void name::update(float time) {                                                                  \
    p_inner->update(tweenFunc(time));                                                              \
  }

#define IMPL_EASING_CLASS_RATE(name, tweenFunc)                                                    \
  name* name::create(Action* inner, float rate) {                                                  \
    auto pRet = new name();                                                                        \
    if (pRet) {                                                                                    \
      pRet->autorelease();                                                                         \
    } else                                                                                         \
      return nullptr;                                                                              \
    pRet->p_inner = inner;                                                                         \
    pRet->p_inner->retain();                                                                       \
    pRet->p_duration = pRet->p_inner->getDuration();                                               \
    pRet->p_rate = rate;                                                                           \
    return pRet;                                                                                   \
  }                                                                                                \
  void name::update(float time) {                                                                  \
    p_inner->update(tweenFunc(time, p_rate));                                                      \
  }

IMPL_EASING_CLASS_RATE(EaseIn, ease::easeIn);
IMPL_EASING_CLASS_RATE(EaseOut, ease::easeOut);
IMPL_EASING_CLASS_RATE(EaseInOut, ease::easeInOut);

IMPL_EASING_CLASS(EaseQuadraticIn, ease::quadraticIn);
IMPL_EASING_CLASS(EaseQuadraticOut, ease::quadraticOut);
IMPL_EASING_CLASS(EaseQuadraticInOut, ease::quadraticInOut);

IMPL_EASING_CLASS(EaseSineIn, ease::sineEaseIn);
IMPL_EASING_CLASS(EaseSineOut, ease::sineEaseOut);
IMPL_EASING_CLASS(EaseSineInOut, ease::sineEaseInOut);

IMPL_EASING_CLASS(EaseQuadIn, ease::quadEaseIn);
IMPL_EASING_CLASS(EaseQuadOut, ease::quadEaseOut);
IMPL_EASING_CLASS(EaseQuadInOut, ease::quadEaseInOut);

IMPL_EASING_CLASS(EaseCubicIn, ease::cubicEaseIn);
IMPL_EASING_CLASS(EaseCubicOut, ease::cubicEaseOut);
IMPL_EASING_CLASS(EaseCubicInOut, ease::cubicEaseInOut);

IMPL_EASING_CLASS(EaseQuartIn, ease::quartEaseIn);
IMPL_EASING_CLASS(EaseQuartOut, ease::quartEaseOut);
IMPL_EASING_CLASS(EaseQuartInOut, ease::quartEaseInOut);

IMPL_EASING_CLASS(EaseQuintIn, ease::quintEaseIn);
IMPL_EASING_CLASS(EaseQuintOut, ease::quintEaseOut);
IMPL_EASING_CLASS(EaseQuintInOut, ease::quintEaseInOut);

IMPL_EASING_CLASS(EaseExpoIn, ease::expoEaseIn);
IMPL_EASING_CLASS(EaseExpoOut, ease::expoEaseOut);
IMPL_EASING_CLASS(EaseExpoInOut, ease::expoEaseInOut);

IMPL_EASING_CLASS(EaseCircIn, ease::circEaseIn);
IMPL_EASING_CLASS(EaseCircOut, ease::circEaseOut);
IMPL_EASING_CLASS(EaseCircInOut, ease::circEaseInOut);

IMPL_EASING_CLASS(EaseBackIn, ease::backEaseIn);
IMPL_EASING_CLASS(EaseBackOut, ease::backEaseOut);
IMPL_EASING_CLASS(EaseBackInOut, ease::backEaseInOut);

IMPL_EASING_CLASS(EaseBounceIn, ease::bounceEaseIn);
IMPL_EASING_CLASS(EaseBounceOut, ease::backEaseOut);
IMPL_EASING_CLASS(EaseBounceInOut, ease::backEaseInOut);
