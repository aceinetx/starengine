#include "AppDelegate.h"
#include <raylib.h>

using namespace star;

AppDelegate::AppDelegate() {
}

bool AppDelegate::applicationDidFinishLaunching() {
	InitWindow(1280, 720, "Star engine");

	return true;
}
