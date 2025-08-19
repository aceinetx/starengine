#include "../Source/AppDelegate.h"
#include "AutoreleasePool.h"
#include "Node.h"

using namespace star;

int main() {
	AppDelegate app;
	return Application::getInstance()->run();
}
