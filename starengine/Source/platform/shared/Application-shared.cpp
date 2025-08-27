#include "Application-shared.h"
#include "ActionManager.h"
#include "Director.h"
#include "EventDispatcher.h"
#include "FontManager.h"
#include "Macros.h"
#include "Scheduler.h"
#include "TextureManager.h"
#include <SDL2/SDL_image.h>

using namespace star;

Application* Application::p_instance = nullptr;

Application::Application() {
  p_instance = this;
}

Application* Application::getInstance() {
  return p_instance;
}

int Application::run() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fmt::println("[star]: {}", SDL_GetError());
    return 1;
  }
  if (SDL_Init(IMG_INIT_PNG) != 0) {
    fmt::println("[star]: {}", SDL_GetError());
    return 1;
  }

  if (!applicationDidFinishLaunching()) {
    return 0;
  }

  /* Initialize everything */
  auto director = Director::getInstance();
  auto fontManager = FontManager::getInstance();
  auto textureManager = TextureManager::getInstance();
  auto actionManager = ActionManager::getInstance();
  auto scheduler = Scheduler::getInstance();
  auto eventDispatcher = EventDispatcher::getInstance();
  (void)actionManager;

  bool done = false;
  while (!done) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        done = true;
        break;
      default:
        /* dispatch the event */
        eventDispatcher->dispatchEvent(event, director->getRunningScene());
        break;
      }
    }

    /* main loop */
    director->mainLoop();
  }

  /* Cleanup */
  fontManager->unloadAllFonts();
  textureManager->unloadAllTextures();

  director->getRunningScene()->removeFromParentAndCleanup();
  STARASSERT(scheduler->getSchedulesCount() == 0,
             "Some schedules are still not deleted, this shouldn't do anything bad, but you should "
             "be concerned.");
  if (Director::getInstance())
    delete Director::getInstance();

  return 0;
}

SDL_Window* Application::getWindow() {
  return p_window;
}

SDL_Renderer* Application::getRenderer() {
  return p_renderer;
}