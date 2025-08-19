#include "MainScene.h"

using namespace star;

bool MainScene::init() {
	if (!Scene::init())
		return false;

	auto director = Director::getInstance();

	auto label = Label::create();
	label->setString("Hello from starengine!");
	label->setPosition(director->getVisibleSize() / 2);
	addChild(label);

	return true;
}
