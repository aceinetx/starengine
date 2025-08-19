#include "Director.h"
#include "Application.h"
#include "AutoreleasePool.h"
#include <raylib.h>

using namespace star;

Director* Director::p_instance = nullptr;

Director::~Director() {
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
	scene->retain();
	p_sceneStack.push_back(scene);
}

void Director::popScene() {
	p_sceneStack.back()->release();
	p_sceneStack.pop_back();
}

Scene* Director::getRunningScene() {
	if (p_sceneStack.empty())
		return nullptr;
	return p_sceneStack.back();
}

Vec2 Director::getVisibleSize() {
	return Vec2(GetScreenWidth(), GetScreenHeight());
}

void Director::mainLoop() {
	p_deltaTime = GetFrameTime();

	BeginDrawing();
	ClearBackground(BLACK);

	Scene* scene = getRunningScene();
	auto camera = scene->getCamera();
	if (scene) {
		BeginMode2D(camera->getRaylibCamera());
	}

	scene->draw();

	if (scene) {
		EndMode2D();
	}

	if (statsDisplay) {
		const char* text = TextFormat("%d / %.3f", GetFPS(), getDeltaTime());
		Vector2 size = MeasureTextEx(GetFontDefault(), text, 30.0f, 0);
		DrawText(text, 0, GetScreenHeight() - size.y, 30.0f, WHITE);
	}

	EndDrawing();

	AutoreleasePool::getInstance()->clear();
}

float Director::getDeltaTime() {
	return p_deltaTime;
}
