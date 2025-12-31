#pragma once
#include <ApplicationProtocol.h>
#include <BufferedRaylib.h>

namespace star {
class Application : protected ApplicationProtocol {
protected:
  static Application* p_instance;

  raylib::BufferedInput p_input;

  void keyboardCallback(KeyboardKey key, bool isDown);

public:
  Application();
  static Application* getInstance();

  int run() override;
};
} // namespace star
