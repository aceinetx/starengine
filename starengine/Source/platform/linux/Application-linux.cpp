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
		p_deltaTime = GetFrameTime();

		BeginDrawing();
		ClearBackground(BLACK);

		if (director->statsDisplay) {
			const char* text = TextFormat("%d / %.3f", GetFPS(), getDeltaTime());
			Vector2 size = MeasureTextEx(GetFontDefault(), text, 30.0f, 0);
			DrawText(text, 0, GetScreenHeight() - size.y, 30.0f, WHITE);
		}
		EndDrawing();
	}

	CloseWindow();
	if (Director::getInstance())
		delete Director::getInstance();

	return 0;
}

float Application::getDeltaTime() {
	return p_deltaTime;
}
