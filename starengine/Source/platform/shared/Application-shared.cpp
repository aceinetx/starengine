#include "Application-shared.h"
#include "ActionManager.h"
#include "Director.h"
#include "EventDispatcher.h"
#include "FontManager.h"
#include "Macros.h"
#include "RaylibEvent.h"
#include "Scheduler.h"
#include "TextureManager.h"
#include <raylib.h>
#ifdef STAR_IMGUI
#include <imgui.h>
#include <rlImGui.h>
#endif

using namespace star;

Application* Application::p_instance = nullptr;

void star::Application::keyboardCallback(KeyboardKey key, bool isDown) {
  auto eventDispatcher = EventDispatcher::getInstance();
  auto director = Director::getInstance();
  RaylibEvent ev;
  ev.type = RaylibEvent::kKeyboard;
  ev.state = isDown ? RaylibEvent::kDown : RaylibEvent::kUp;
  ev.button = key;
  eventDispatcher->dispatchEvent(ev, director->getRunningScene());
}

Application::Application() {
  p_instance = this;

  p_input.keyboard_callback = [this](KeyboardKey key, bool isDown) {
    keyboardCallback(key, isDown);
  };
}

Application* Application::getInstance() {
  return p_instance;
}

int Application::run() {
  if (!applicationDidFinishLaunching()) {
    return 0;
  }

  /* Initialize everything */
  auto director = Director::getInstance();
  auto fontManager = FontManager::getInstance();
  auto textureManager = TextureManager::getInstance();
  auto actionManager = ActionManager::getInstance();
  auto scheduler = Scheduler::getInstance();
  (void)actionManager;
#ifdef STAR_IMGUI
  rlImGuiSetup(true);
  static auto& io = ImGui::GetIO();
  io.IniFilename = nullptr; // Don't create imgui.ini
#endif

  while (!WindowShouldClose()) {
    p_input.PollEvents();

    /* main loop */
    director->mainLoop();
  }

  /* Cleanup */
  fontManager->unloadAllFonts();
  textureManager->unloadAllTextures();
#ifdef STAR_IMGUI
  rlImGuiShutdown();
#endif

  director->getRunningScene()->removeFromParentAndCleanup();
  STARASSERT(scheduler->getSchedulesCount() == 0,
             "Some schedules are still not deleted, this shouldn't do anything bad, but you should "
             "be concerned.");
  CloseWindow();
  if (Director::getInstance())
    delete Director::getInstance();

  return 0;
}
