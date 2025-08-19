#pragma once
#include "Scene.h"
#include <vector>

namespace star {
class Director {
protected:
	static Director* p_instance;

	std::vector<Scene*> p_sceneStack;
	float p_deltaTime;

public:
	bool statsDisplay;

public:
	~Director();
	static Director* getInstance();

	void runWithScene(Scene* scene);
	void pushScene(Scene* scene);
	void popScene();

	Scene* getRunningScene();

	Vec2 getVisibleSize();

	float getDeltaTime();
	void mainLoop();
};
} // namespace star
