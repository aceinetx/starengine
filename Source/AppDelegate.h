#pragma once
#include "Application.h"

class AppDelegate : private star::Application {
public:
	AppDelegate();
	virtual bool applicationDidFinishLaunching();
};
