#pragma once
#include "Scene.h"
#include <vector>

namespace star {
/** Director
 *
 * Controls the game, scenes, and objects, draws nodes
 */
class Director {
protected:
  /** global instance */
  static Director* p_instance;

  /** current scene */
  Scene* currentScene;
  /** delta time */
  float p_deltaTime;

public:
  /** display stats? */
  bool statsDisplay;

public:
  ~Director();
  /**
   * Get the instance of a director
   */
  static Director* getInstance();

  /**
   * Run the game with a scene
   */
  void runWithScene(Scene* scene);

  /**
   * Get the current running scene
   */
  Scene* getRunningScene();

  /**
   * Get the screen size
   */
  Vec2 getVisibleSize();

  /**
   * Get the game delta time (time from previous to the current frame)
   */
  float getDeltaTime();

#ifdef STAR_INSPECTOR
  /**
   * Draws the inspector
   */
  void drawInspector();
#endif

  /**
   * Main loop of the game, draws nodes and manages memory
   */
  void mainLoop();
};
} // namespace star
