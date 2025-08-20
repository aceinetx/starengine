#include "AppDelegate.h"
#include "MainScene.h"
#include <raylib.h>

using namespace star;

AppDelegate::AppDelegate() {
}

bool AppDelegate::applicationDidFinishLaunching() {
  // initialize director
  auto director = Director::getInstance();

  InitWindow(1280, 720, "StarEngine");
  SetTargetFPS(60);

  director->runWithScene(MainScene::create());
  director->statsDisplay = false;

  return true;
}
