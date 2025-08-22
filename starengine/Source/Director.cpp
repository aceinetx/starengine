#include "Director.h"
#include "ActionManager.h"
#include "Application.h"
#include "AutoreleasePool.h"
#include "Scheduler.h"
#include <raylib.h>
#ifdef STAR_IMGUI
#include <rlImGui.h>
#endif

using namespace star;

Director* Director::p_instance = nullptr;

Director::~Director() {
}

Director* Director::getInstance() {
  if (p_instance == nullptr)
    p_instance = new Director();
  return p_instance;
}

void Director::runWithScene(Scene* scene) {
  currentScene = scene;
  currentScene->retain();
}

void Director::replaceScene(Scene* scene) {
  currentScene->removeFromParentAndCleanup();

  currentScene = scene;
  scene->retain();
}

Scene* Director::getRunningScene() {
  return currentScene;
}

Vec2 Director::getVisibleSize() {
  return Vec2(GetScreenWidth(), GetScreenHeight());
}

void Director::mainLoop() {
  p_deltaTime = GetFrameTime();

  Scheduler::getInstance()->update(getDeltaTime());
  ActionManager::getInstance()->stepActions(getDeltaTime());

  BeginDrawing();
  ClearBackground(BLACK);

  Scene* scene = getRunningScene();
  auto camera = scene->getCamera();
  if (scene) {
    BeginMode2D(camera->getRaylibCamera());
  }

  scene->draw();

  if (scene) {
    EndMode2D();
  }

  if (statsDisplay) {
    const char* text = TextFormat("%d / %.3f", GetFPS(), getDeltaTime());
    Vector2 size = MeasureTextEx(GetFontDefault(), text, 30.0f, 0);
    DrawText(text, 0, GetScreenHeight() - size.y, 30.0f, WHITE);
  }

#ifdef STAR_IMGUI
  rlImGuiBegin();
#endif
#ifdef STAR_INSPECTOR
  drawInspector();
#endif
#ifdef STAR_IMGUI
  rlImGuiEnd();
#endif

  EndDrawing();

  AutoreleasePool::getInstance()->clear();
}

float Director::getDeltaTime() {
  return p_deltaTime;
}
