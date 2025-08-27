#include "Director.h"
#include "ActionManager.h"
#include "Application.h"
#include "AutoreleasePool.h"
#include "Scheduler.h"

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
  auto application = Application::getInstance();
  auto window = application->getWindow();
  int w, h;
  SDL_GetWindowSize(window, &w, &h);
  return Vec2(w, h);
}

static uint64_t now = SDL_GetPerformanceCounter();
static uint64_t last = 0;

void Director::mainLoop() {
  auto application = Application::getInstance();
  auto renderer = application->getRenderer();

  last = now;
  now = SDL_GetPerformanceCounter();

  p_deltaTime = (float)((now - last) * 1000 / (float)SDL_GetPerformanceFrequency());

  Scheduler::getInstance()->update(getDeltaTime());
  ActionManager::getInstance()->stepActions(getDeltaTime());

  SDL_RenderClear(renderer);

  Scene* scene = getRunningScene();
  // auto camera = scene->getCamera();
  if (scene) {
    // BeginMode2D(camera->getRaylibCamera());
  }

  scene->draw();

  if (scene) {
    // EndMode2D();
  }

  if (statsDisplay) {
    /*
    const char* text = TextFormat("%d / %.3f", GetFPS(), getDeltaTime());
    Vector2 size = MeasureTextEx(GetFontDefault(), text, 30.0f, 0);
    DrawText(text, 0, GetScreenHeight() - size.y, 30.0f, WHITE);
    */
  }

  SDL_RenderPresent(renderer);

  AutoreleasePool::getInstance()->clear();
}

float Director::getDeltaTime() {
  return p_deltaTime;
}
