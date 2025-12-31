#include "BufferedRaylib.h"

#include "raymath.h"

#include <map>
#include <utility>

#define MAX_GAMEPADS 16

namespace raylib {

void BufferedInput::PollKey(KeyboardKey key) {
  bool isDown = IsKeyDown((KeyboardKey)key);
  auto it = keyboard_states.find((KeyboardKey)key);
  if (it == keyboard_states.end()) {
    // Initialize state silently on first poll
    keyboard_states[(KeyboardKey)key] = isDown;
  } else if (it->second != isDown) {
    // Only fire callback on actual state change
    keyboard_states[(KeyboardKey)key] = isDown;
    keyboard_callback((KeyboardKey)key, isDown);
  }
}

void BufferedInput::PollEvents(bool whileUnfocused /*= false*/) {
  if (!whileUnfocused && !IsWindowFocused())
    return;

  // Poll keyboard keys
  if (keyboard_callback) {
    for (int key = KEY_NULL; key <= KEY_KP_EQUAL; key++) {
      PollKey((KeyboardKey)key);
    }
    PollKey(KEY_LEFT_CONTROL);
  }

  // Poll mouse buttons (check all possible mouse buttons)
  if (mouse_button_callback) {
    for (int button = MOUSE_BUTTON_LEFT; button <= MOUSE_BUTTON_EXTRA; button++) {
      bool isDown = IsMouseButtonDown((MouseButton)button);
      auto it = mouse_button_states.find((MouseButton)button);
      if (it == mouse_button_states.end()) {
        // Initialize state silently on first poll
        mouse_button_states[(MouseButton)button] = isDown;
      } else if (it->second != isDown) {
        // Only fire callback on actual state change
        mouse_button_states[(MouseButton)button] = isDown;
        mouse_button_callback((MouseButton)button, isDown);
      }
    }
  }

  // Poll gamepad buttons
  if (gamepad_button_callback) {
    for (int gamepad = 0; gamepad < MAX_GAMEPADS; gamepad++) {
      if (!IsGamepadAvailable(gamepad))
        continue;
      for (int button = GAMEPAD_BUTTON_UNKNOWN; button <= GAMEPAD_BUTTON_RIGHT_THUMB; button++) {
        bool isDown = IsGamepadButtonDown(gamepad, (GamepadButton)button);
        auto key = std::make_pair(gamepad, (GamepadButton)button);
        auto it = gamepad_button_states.find(key);
        if (it == gamepad_button_states.end()) {
          // Initialize state silently on first poll
          gamepad_button_states[key] = isDown;
        } else if (it->second != isDown) {
          // Only fire callback on actual state change
          gamepad_button_states[key] = isDown;
          gamepad_button_callback(gamepad, (GamepadButton)button, isDown);
        }
      }
    }
  }

  // Poll mouse wheel
  if (mouse_wheel_callback) {
    float movement = GetMouseWheelMove();
    if (movement != 0) {
      mouse_wheel_value += movement;
      float delta = movement;
      mouse_wheel_callback(mouse_wheel_value, delta);
    }
  }

  // Poll gamepad axes
  if (gamepad_axis_callback) {
    for (int gamepad = 0; gamepad < MAX_GAMEPADS; gamepad++) {
      if (!IsGamepadAvailable(gamepad))
        continue;
      for (int axis = GAMEPAD_AXIS_LEFT_X; axis <= GAMEPAD_AXIS_RIGHT_TRIGGER; axis++) {
        float movement = GetGamepadAxisMovement(gamepad, (GamepadAxis)axis);
        if (movement != 0) {
          auto key = std::make_pair(gamepad, (GamepadAxis)axis);
          auto it = gamepad_axis_states.find(key);
          float lastValue = (it != gamepad_axis_states.end()) ? it->second : 0.0f;
          float newValue = lastValue + movement;
          float delta = movement;
          gamepad_axis_states[key] = newValue;
          gamepad_axis_callback(gamepad, (GamepadAxis)axis, newValue, delta);
        }
      }
    }
  }

  // Poll mouse position
  if (mouse_position_callback) {
    Vector2 newPos = GetMousePosition();
    // Check if this is the first poll (mouse_position still at initial {0,0})
    bool isFirstPoll = (mouse_position.x == 0.0f && mouse_position.y == 0.0f);

    if (isFirstPoll) {
      // Silently initialize on first poll, don't fire callback
      mouse_position = newPos;
    } else if (!Vector2Equals(newPos, mouse_position)) {
      // Actual position change on subsequent polls
      Vector2 delta = Vector2Subtract(newPos, mouse_position);
      mouse_position = newPos;
      mouse_position_callback(newPos, delta);
    }
  }
}
} // namespace raylib
