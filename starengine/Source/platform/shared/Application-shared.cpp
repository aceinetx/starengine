#include "Application-shared.h"
#include "Director.h"
#include "EventDispatcher.h"
#include "FontManager.h"
#include "Macros.h"
#include "RaylibEvent.h"
#include "Scheduler.h"
#include "TextureManager.h"
#include <algorithm>
#include <raylib.h>
#include <set>
#ifdef STAR_IMGUI
#include <imgui.h>
#include <rlImGui.h>
#endif

using namespace star;

static std::set<int> s_downKeys;
static std::set<int> s_downMouseButtons;

static void processInput(RaylibEvent& ev) {

  // TODO: REFACTOR THIS STUPID PIECE OF CODE
  auto validateButton = [](std::set<int>& set, int button) -> bool {
    if (!set.count(button)) {
      return false;
    }
    set.erase(button); // erase it from down buttons since it's up
    return true;
  };

  /* keyboard input */
  for (int key = KEY_NULL + 4; key <= KEY_KP_EQUAL; key++) {
    ev.type = RaylibEvent::kKeyboard;
    ev.button = key;
    ev.state = RaylibEvent::kNone;
    if (IsKeyPressed(key)) {
      ev.state = RaylibEvent::kPressed;
    } else if (IsKeyUp(key)) {
      // check if an event is valid, because it will spam all
      // listeners with events that don't exist
      if (validateButton(s_downKeys, ev.button))
        ev.state = RaylibEvent::kUp;
    } else if (IsKeyDown(key)) {
      if (!s_downKeys.count(ev.button)) {
        ev.state = RaylibEvent::kDown;
        s_downKeys.insert(ev.button);
      }
    } else
      ev.type = RaylibEvent::kNothing;
    if (ev.state != RaylibEvent::kNone) {
      break;
    }
  }

  /* mouse input */
  if (ev.state == RaylibEvent::kNone) {
    for (int mouseButton = MOUSE_BUTTON_LEFT; mouseButton <= MOUSE_BUTTON_BACK; mouseButton++) {
      ev.type = RaylibEvent::kMouse;
      ev.button = mouseButton;
      ev.state = RaylibEvent::kNone;
      if (IsMouseButtonPressed(mouseButton))
        ev.state = RaylibEvent::kPressed;
      else if (IsMouseButtonUp(mouseButton)) {
        // check if an event is valid, because it will spam all
        // listeners with events that don't exist
        if (validateButton(s_downMouseButtons, ev.button))
          ev.state = RaylibEvent::kUp;
      } else if (IsMouseButtonDown(mouseButton)) {
        if (!s_downMouseButtons.count(ev.button)) {
          ev.state = RaylibEvent::kDown;
          s_downMouseButtons.insert(ev.button);
        }
      } else
        ev.type = RaylibEvent::kNothing;
      if (ev.state != RaylibEvent::kNone)
        break;
    }
  }
}

Application* Application::p_instance = nullptr;

Application::Application() {
  p_instance = this;
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
  auto scheduler = Scheduler::getInstance();
  auto eventDispatcher = EventDispatcher::getInstance();
#ifdef STAR_IMGUI
  rlImGuiSetup(true);
  static auto& io = ImGui::GetIO();
  io.IniFilename = nullptr; // Don't create imgui.ini
#endif

  while (!WindowShouldClose()) {
    RaylibEvent ev;
    processInput(ev);

    /* dispatch the event */
    if (ev.type != RaylibEvent::kNothing && ev.state != RaylibEvent::kNone)
      eventDispatcher->dispatchEvent(ev, director->getRunningScene());

    /* main loop */
    director->mainLoop();
  }

  /* Cleanup */
  fontManager->unloadAllFonts();
  textureManager->unloadAllTextures();
#ifdef STAR_IMGUI
  rlImGuiShutdown();
#endif
  CloseWindow();

  director->getRunningScene()->removeFromParentAndCleanup();
  STARASSERT(scheduler->getSchedulesCount() == 0,
             "Some schedules are still not deleted, this shouldn't do anything bad, but you should "
             "be concerned.");
  if (Director::getInstance())
    delete Director::getInstance();

  return 0;
}
