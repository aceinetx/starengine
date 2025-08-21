#include "ActionScene.h"
#include "ActionEase.h"
#include "ScaleTo.h"

using namespace star;

bool ActionScene::init() {
  if (!Scene::init())
    return false;

  auto winSize = p_director->getVisibleSize();

  m_logo = Sprite::create("logo.png");
  m_logo->setPosition(winSize / 2);
  m_logo->setScale(sm_logoDefaultScale);
  addChild(m_logo);

  auto keyboardListener = EventListenerKeyboard::create();
  keyboardListener->onKeyPressed = CALLBACK_1(ActionScene::onKeyPressed, this);
  EventDispatcher::getInstance()->addListenerWithSceneGraphPriority(keyboardListener, this);

  return true;
}

bool ActionScene::onKeyPressed(KeyboardKey key) {
  if (key == KEY_R) {
    static constexpr float s_duration = 2.0f;
    auto scale = EaseBackInOut::create(ScaleTo::create(s_duration, 0.4f));
    auto rotate = EaseBackInOut::create(RotateTo::create(s_duration, 360.0f));
    m_logo->runAction(scale);
    m_logo->runAction(rotate);
    scheduleOnce(
        [this](float dt) {
          fmt::println("ok");
          m_logo->setScale(sm_logoDefaultScale);
          m_logo->setRotation(0.0f);
        },
        s_duration + 0.1f);
  }
  return true;
}
