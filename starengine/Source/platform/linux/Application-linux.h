#pragma once
#include <ApplicationProtocol.h>

namespace star {
class Application : protected ApplicationProtocol {
protected:
	static Application* p_instance;

public:
	Application();
	static Application* getInstance();

	int run();
};
} // namespace star
