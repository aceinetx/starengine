#include "MoveTo.h"

using namespace star;

void MoveTo::update(float time) {
  Vec2 pos = (p_initialPosition + (p_position - p_initialPosition) * time);
  p_target->setPosition(pos);
}

void MoveTo::startWithTarget(Node* target) {
  Action::startWithTarget(target);
  p_initialPosition = p_target->getPosition();
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
