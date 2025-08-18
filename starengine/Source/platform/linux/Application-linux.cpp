#include "Application-linux.h"
#include <raylib.h>

using namespace star;

Application* Application::p_instance = nullptr;

Application::Application() {
	p_instance = this;
}

int Application::run() {
	if (!applicationDidFinishLaunching()) {
		return 0;
	}

	while (!WindowShouldClose()) {
		BeginDrawing();
		EndDrawing();
	}

	CloseWindow();

	return 0;
}

Application* Application::getInstance() {
	return p_instance;
}
