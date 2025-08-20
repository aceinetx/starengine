#include "MainScene.h"
#include "EventDispatcher.h"
#include "EventListenerKeyboard.h"
#include "Macros.h"
#include "fmt/base.h"
#include <ClassFormatters.h>
#include <fmt/format.h>
#include <raylib.h>

using namespace star;

bool MainScene::init() {
  if (!Scene::init())
    return false;

  auto director = Director::getInstance();
  auto winSize = director->getVisibleSize();

  {
    auto label = Label::createWithDefaultFont("Hello from starengine", 30.0f);
    label->setPosition(winSize / 2);
    addChild(label);

    auto labelSize = Label::create();
    labelSize->setFont("Mecha.ttf");
    labelSize->setString(fmt::format("The window size is {}", winSize));
    labelSize->setPosition(Vec2(winSize.x / 2, label->getPositionY() - label->getContentSize().y));
    addChild(labelSize);

    logo = Sprite::create("logo.png");
    logo->setPosition(winSize / 2);
    logo->setScale(0.5f);
    logo->setPositionY(logo->getContentSize().y * logo->getScale() / 1.5f);
    addChild(logo);
  }

  scheduleUpdate();

  auto keyboardListener = EventListenerKeyboard::create();
  keyboardListener->onKeyDown = CALLBACK_1(MainScene::onKeyDown, this);
  keyboardListener->onKeyUp = CALLBACK_1(MainScene::onKeyUp, this);
  EventDispatcher::getInstance()->addListenerWithSceneGraphPriority(keyboardListener, this);

  return true;
}

void MainScene::update(float dt) {
  static bool increase = false;
  static const float step = 0.05f;
  if (increase) {
    logo->setScale(logo->getScale() + step * dt);
    if (logo->getScale() > 0.5f) {
      increase = false;
    }
  } else {
    logo->setScale(logo->getScale() - step * dt);
    if (logo->getScale() < 0.4f) {
      increase = true;
    }
  }
  logo->setPosition(logo->getPosition() + direction * dt);
}

bool MainScene::onKeyDown(KeyboardKey key) {
  static float speed = 100.0f;
  switch (key) {
  case KEY_W:
    direction.y = speed;
    break;
  case KEY_S:
    direction.y = -speed;
    break;
  case KEY_D:
    direction.x = speed;
    break;
  case KEY_A:
    direction.x = -speed;
    break;
  default:
    break;
  }
  return true;
}

bool MainScene::onKeyUp(KeyboardKey key) {
  switch (key) {
  case KEY_W:
    if (direction.y > 0)
      direction.y = 0;
    break;
  case KEY_S:
    if (direction.y < 0)
      direction.y = 0;
    break;
  case KEY_D:
    if (direction.x > 0)
      direction.x = 0;
    break;
  case KEY_A:
    if (direction.x < 0)
      direction.x = 0;
    break;
  default:
    break;
  }
  return true;
}
