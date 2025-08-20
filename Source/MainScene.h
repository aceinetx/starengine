#pragma once
#include "star.h"
#include <raylib.h>

class MainScene : public star::Scene {
private:
  star::Sprite* logo;

  star::Vec2 direction;

public:
  bool init() override;

  void update(float dt) override;

  bool onKeyDown(KeyboardKey key);
  bool onKeyUp(KeyboardKey key);

  CREATE_FUNC(MainScene);
};
