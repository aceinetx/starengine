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

IMPL_EASING_CLASS(BackInOut, ease::backEaseInOut);
