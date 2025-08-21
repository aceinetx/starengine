#pragma once
#include "star.h"

class ActionScene : public star::Scene {
private:
  static constexpr float sm_logoDefaultScale = 0.5f;
  star::Sprite* m_logo;

public:
  bool init() override;

  void update(float dt) override;
  bool onKeyPressed(KeyboardKey key);

  CREATE_FUNC(ActionScene);
};
