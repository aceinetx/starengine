#include "ScaleTo.h"

using namespace star;

void ScaleTo::update(float time) {
  static bool s_firstTick = true;
  if (s_firstTick) {
    p_initial = p_target->getScale();
    s_firstTick = false;
  }

  float scale = (p_initial + (p_scale - p_initial) * time);
  p_target->setScale(scale);
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
