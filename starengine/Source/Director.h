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
	static Director* p_instance;

	std::vector<Scene*> p_sceneStack;
	float p_deltaTime;

public:
	bool statsDisplay;

public:
	~Director();
	/**
	 * Get the instance of a director
	 */
	static Director* getInstance();

	/**
	 * Reserves space on the scene stack and push the scene
	 */
	void runWithScene(Scene* scene);
	/**
	 * Push the scene to the scene stack
	 */
	void pushScene(Scene* scene);
	/**
	 * Pop the scene from the scene stack
	 */
	void popScene();

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
