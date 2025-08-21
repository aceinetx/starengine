#include "MainScene.h"
#include <fmt/format.h>
#include <raylib.h>

using namespace star;

bool MainScene::init() {
  if (!Scene::init())
    return false;

  // get the director instance
  auto director = Director::getInstance();

  // get the window size
  auto winSize = director->getVisibleSize();

  {
    // create a hello label
    auto label = Label::createWithDefaultFont("Hello from starengine", 30.0f);
    label->setPosition(winSize / 2);
    addChild(label);

    // create another label
    auto labelSize = Label::create();
    labelSize->setFont("Mecha.ttf");
    labelSize->setString(fmt::format("The window size is {}", winSize));
    labelSize->setPosition(Vec2(winSize.x / 2, label->getPositionY() - label->getContentSize().y));
    addChild(labelSize);

    // create a sprite with the starengine logo on it
    m_logo = Sprite::create("logo.png");
    m_logo->setPosition(winSize / 2);
    m_logo->setScale(0.5f);
    m_logo->setPositionY(m_logo->getContentSize().y * m_logo->getScale() / 1.5f);
    m_logo->setScale(1.5f);
    addChild(m_logo);

    // create another sprite within the logo
    {
      auto logo = Sprite::create("logo.png");
      logo->setScale(0.5f);
      logo->setPositionY(100);
      m_logo->addChild(logo);
    }
  }

  // scale down the logo with an easing
  auto action = ScaleTo::create(1.0f, 0.5f);
  auto ease = EaseBackInOut::create(action);
  m_logo->runAction(ease);

  // add a keyboard listener
  auto keyboardListener = EventListenerKeyboard::create();
  keyboardListener->onKeyDown = CALLBACK_1(MainScene::onKeyDown, this);
  keyboardListener->onKeyUp = CALLBACK_1(MainScene::onKeyUp, this);
  EventDispatcher::getInstance()->addListenerWithSceneGraphPriority(keyboardListener, this);

  // call update() every single frame
  scheduleUpdate();

  return true;
}

void MainScene::update(float dt) {
  static bool increase = false;
  static const float step = 0.05f;
  if (increase) {
    m_logo->setScale(m_logo->getScale() + step * dt);
    if (m_logo->getScale() > 0.5f) {
      increase = false;
    }
  } else {
    m_logo->setScale(m_logo->getScale() - step * dt);
    if (m_logo->getScale() < 0.4f) {
      increase = true;
    }
  }

  Vec2 direction = Vec2(0, 0);
  static constexpr float s_speed = 100.0f;
  for (KeyboardKey key : m_keysDown) {
    if (key == KEY_W)
      direction.y += s_speed;
    if (key == KEY_S)
      direction.y -= s_speed;
    if (key == KEY_D)
      direction.x += s_speed;
    if (key == KEY_A)
      direction.x -= s_speed;
  }
  m_logo->setPosition(m_logo->getPosition() + direction * dt);
}

bool MainScene::onKeyDown(KeyboardKey key) {
  m_keysDown.insert(key);
  return true;
}

bool MainScene::onKeyUp(KeyboardKey key) {
  m_keysDown.erase(key);
  return true;
}
