#include "AppDelegate.h"
#include "ActionScene.h"
#include "MainScene.h"

using namespace star;

AppDelegate::AppDelegate() {
}

bool AppDelegate::applicationDidFinishLaunching() {
  // initialize director
  auto director = Director::getInstance();

  p_window = SDL_CreateWindow("Hello World!", 0, 0, 1280, 720, SDL_WINDOW_SHOWN);
  if (!p_window) {
    fmt::println("[star]: {}", SDL_GetError());
    return false;
  }

  p_renderer =
      SDL_CreateRenderer(p_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!p_renderer) {
    fmt::println("[star]: {}", SDL_GetError());
    return false;
  }

  director->runWithScene(MainScene::create());
  director->statsDisplay = false;

  return true;
}
