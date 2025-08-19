#include "Application-linux.h"
#include "Director.h"
#include "FontManager.h"
#include "TextureManager.h"
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

	/* Initialize everything */
	auto director = Director::getInstance();
	auto fontManager = FontManager::getInstance();
	auto textureManager = TextureManager::getInstance();
#ifdef STAR_IMGUI
	rlImGuiSetup(true);
	static auto& io = ImGui::GetIO();
	io.IniFilename = nullptr; // Don't create imgui.ini
#endif
	while (!WindowShouldClose()) {
		director->mainLoop();
	}

	/* Cleanup */
	fontManager->unloadAllFonts();
	textureManager->unloadAllTextures();
#ifdef STAR_IMGUI
	rlImGuiShutdown();
#endif
	CloseWindow();

	director->getRunningScene()->release();
	if (Director::getInstance())
		delete Director::getInstance();

	return 0;
}
