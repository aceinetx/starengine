#include "Director.h"

using namespace star;

Director* Director::p_instance = nullptr;

Director::~Director() {
	for (Scene* scene : p_sceneStack) {
		delete scene;
	}
}

Director* Director::getInstance() {
	if (p_instance == nullptr)
		p_instance = new Director();
	return p_instance;
}

void Director::runWithScene(Scene* scene) {
	p_sceneStack.reserve(15);
	pushScene(scene);
}

void Director::pushScene(Scene* scene) {
	p_sceneStack.push_back(scene);
}

void Director::popScene() {
	delete p_sceneStack.back();
	p_sceneStack.pop_back();
}
