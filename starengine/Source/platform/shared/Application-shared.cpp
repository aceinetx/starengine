#include "Application-shared.h"
#include "Director.h"
#include "FontManager.h"
#include "Macros.h"
#include "Scheduler.h"
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
	auto scheduler = Scheduler::getInstance();
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

	director->getRunningScene()->removeFromParentAndCleanup();
	STARASSERT(scheduler->getSchedulesCount() == 0, "Some schedules are still not deleted, this shouldn't do anything bad, but you should be concerned.");
	if (Director::getInstance())
		delete Director::getInstance();

	return 0;
}
