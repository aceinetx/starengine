#include "Application-linux.h"
#include "Director.h"
#include "FontManager.h"
#include <raylib.h>
#include <rlImGui.h>

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
	auto fontManager = FontManager::getInstance();
#ifdef STAR_IMGUI
	rlImGuiSetup(true);
	static auto& io = ImGui::GetIO();
	io.IniFilename = nullptr;
#endif
	while (!WindowShouldClose()) {
		director->mainLoop();
	}

	fontManager->unloadAllFonts();
#ifdef STAR_IMGUI
	rlImGuiShutdown();
#endif
	CloseWindow();

	director->getRunningScene()->release();
	if (Director::getInstance())
		delete Director::getInstance();

	return 0;
}
