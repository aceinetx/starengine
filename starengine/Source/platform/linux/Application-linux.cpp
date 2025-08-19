#include "Application-linux.h"
#include "Director.h"
#include <raylib.h>

using namespace star;

Application* Application::p_instance = nullptr;

Application::Application() {
	p_instance = this;
}

Application* Application::getInstance() {
	return p_instance;
}

int Application::run() {
	if (!applicationDidFinishLaunching()) {
		return 0;
	}

	auto director = Director::getInstance();
	while (!WindowShouldClose()) {
		director->mainLoop();
	}

	CloseWindow();

	director->getRunningScene()->release();
	if (Director::getInstance())
		delete Director::getInstance();

	return 0;
}
