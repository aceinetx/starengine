#include "MainScene.h"
#include <ClassFormatters.h>
#include <fmt/format.h>

using namespace star;

bool MainScene::init() {
	if (!Scene::init())
		return false;

	auto director = Director::getInstance();
	auto winSize = director->getVisibleSize();

	{
		auto label = Label::createWithDefaultFont("Hello from starengine", 30.0f);
		label->setPosition(winSize / 2);
		addChild(label);

		auto labelSize = Label::create();
		labelSize->setFont("Mecha.ttf");
		labelSize->setString(fmt::format("The window size is {}", winSize));
		labelSize->setPosition(Vec2(winSize.x / 2, label->getPositionY() - label->getContentSize().y));
		addChild(labelSize);

		auto logo = Sprite::create("logo.png");
		logo->setPosition(winSize / 2);
		logo->setScale(0.5f);
		logo->setPositionY(logo->getContentSize().y * logo->getScale() / 1.5f);
		addChild(logo);
	}

	return true;
}
