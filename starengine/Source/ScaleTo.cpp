#include "ScaleTo.h"

using namespace star;

void ScaleTo::update(float time) {
  float scale = (p_initial + (p_scale - p_initial) * time);
  p_target->setScale(scale);
}

void ScaleTo::startWithTarget(Node* target) {
  Action::startWithTarget(target);
  p_initial = p_target->getScale();
}

ScaleTo* ScaleTo::create(float duration, float scale) {
  auto pRet = new ScaleTo();
  if (pRet) {
    pRet->autorelease();
  } else {
    return nullptr;
  }
  pRet->p_duration = duration;
  pRet->p_scale = scale;
  return pRet;
}
