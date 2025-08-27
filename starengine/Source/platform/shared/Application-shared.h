#pragma once
#include <ApplicationProtocol.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

namespace star {
class Application : protected ApplicationProtocol {
protected:
  static Application* p_instance;
  SDL_Window* p_window;
  SDL_Renderer* p_renderer;

public:
  Application();
  static Application* getInstance();

  int run() override;

  SDL_Window* getWindow();
  SDL_Renderer* getRenderer();
};
} // namespace star
