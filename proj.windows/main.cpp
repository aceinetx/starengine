#include "../Source/AppDelegate.h"
#include "windows.h"

using namespace star;

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	AppDelegate app;
	return Application::getInstance()->run();
}
