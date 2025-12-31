/**
 * @file BufferedInput.hpp
 * @brief Contains definitions for buffered input handling based off raylib
 */

#include "raylib.h"

#include <functional>
#include <map>
#include <utility>

namespace raylib {

using KeyboardCallback = std::function<void(KeyboardKey key, bool isDown)>;
using MouseButtonCallback = std::function<void(MouseButton button, bool isDown)>;
using GamepadButtonCallback = std::function<void(int gamepadId, GamepadButton button, bool isDown)>;
using MouseWheelCallback = std::function<void(float value, float delta)>;
using GamepadAxisCallback =
    std::function<void(int gamepadId, GamepadAxis axis, float value, float delta)>;
using MousePositionCallback = std::function<void(Vector2 position, Vector2 delta)>;

/**
 * @brief Input manager with direct callback members for OpenGL-style input
 * handling
 */
struct BufferedInput {
public:
  // Function which polls all input devices and invokes callbacks
  void PollEvents(bool whileUnfocused = false);

  // Direct callback members
  KeyboardCallback keyboard_callback = nullptr;
  MouseButtonCallback mouse_button_callback = nullptr;
  GamepadButtonCallback gamepad_button_callback = nullptr;
  MouseWheelCallback mouse_wheel_callback = nullptr;
  GamepadAxisCallback gamepad_axis_callback = nullptr;
  MousePositionCallback mouse_position_callback = nullptr;

private:
  void PollKey(KeyboardKey key);

  float mouse_wheel_value = 0.0f;
  Vector2 mouse_position = {0, 0};
  std::map<KeyboardKey, bool> keyboard_states;
  std::map<MouseButton, bool> mouse_button_states;
  std::map<std::pair<int, GamepadButton>, bool> gamepad_button_states;
  std::map<std::pair<int, GamepadAxis>, float> gamepad_axis_states;
};
} // namespace raylib
