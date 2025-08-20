#include "MoveTo.h"

using namespace star;

void MoveTo::update(float time) {
  p_initialPosition = p_target->getPosition() - p_diff;
  p_diff = (p_initialPosition + (p_position - p_initialPosition) * time) - p_target->getPosition();
  p_target->setPosition(p_target->getPosition() + p_diff);
}

MoveTo* MoveTo::create(float duration, Vec2 pos) {
  auto pRet = new MoveTo();
  if (pRet) {
    pRet->autorelease();
  } else {
    return nullptr;
  }
  pRet->p_duration = duration;
  pRet->p_position = pos;
  return pRet;
}
