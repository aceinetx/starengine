#include "MoveTo.h"

using namespace star;

void MoveTo::update(float time) {
  static bool s_firstTick = true;
  if (s_firstTick) {
    p_initialPosition = p_target->getPosition();
    s_firstTick = false;
  }

  Vec2 pos = (p_initialPosition + (p_position - p_initialPosition) * time);
  p_target->setPosition(pos);
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
