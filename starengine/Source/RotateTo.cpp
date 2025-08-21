#include "RotateTo.h"

using namespace star;

void RotateTo::update(float time) {
  float rotation = (p_initialRotation + (p_rotation - p_initialRotation) * time);
  p_target->setRotation(rotation);
}

void RotateTo::startWithTarget(Node* target) {
  Action::startWithTarget(target);
  p_initialRotation = p_target->getRotation();
}

RotateTo* RotateTo::create(float duration, float rotation) {
  auto pRet = new RotateTo();
  if (pRet) {
    pRet->autorelease();
  } else {
    return nullptr;
  }
  pRet->p_duration = duration;
  pRet->p_rotation = rotation;
  return pRet;
}
