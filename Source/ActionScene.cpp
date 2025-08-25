#include "ActionScene.h"
#include "ActionEase.h"
#include "Label.h"
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

  auto label = Label::createWithDefaultFont("Press R to run an action", 40.0f);
  label->setPosition(Vec2(winSize.x / 2, label->getContentSize().y / 2));
  addChild(label);

  auto background = DrawNode::create();
  background->clear(Color4B(255, 255, 255, 50));
  background->setZOrder(-1);
  addChild(background);

  auto keyboardListener = EventListenerKeyboard::create();
  keyboardListener->onKeyPressed = CALLBACK_1(ActionScene::onKeyPressed, this);
  EventDispatcher::getInstance()->addListenerWithSceneGraphPriority(keyboardListener, this);

  scheduleUpdate();

  return true;
}

void ActionScene::update(float dt) {
  if (m_logo->getNumberOfRunningActions() == 0) {
    // m_logo->setScale(sm_logoDefaultScale);
    m_logo->setRotation(0.0f);
  }
}

bool ActionScene::onKeyPressed(KeyboardKey key) {
  if (key == KEY_R && m_logo->getScale() == sm_logoDefaultScale) {
    static constexpr float s_duration = 2.0f;
    auto scale = EaseBackInOut::create(ScaleTo::create(s_duration, 0.4f));
    auto rotate = EaseBackInOut::create(RotateTo::create(s_duration, 360.0f));
    m_logo->runAction(scale);
    m_logo->runAction(rotate);
  }
  return true;
}
