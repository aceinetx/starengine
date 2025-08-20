#pragma once
#include "star.h"
#include <raylib.h>
#include <set>

class MainScene : public star::Scene {
private:
  star::Sprite* m_logo;

  std::set<KeyboardKey> m_keysDown;

public:
  bool init() override;

  void update(float dt) override;

  bool onKeyDown(KeyboardKey key);
  bool onKeyUp(KeyboardKey key);

  CREATE_FUNC(MainScene);
};
