#pragma once

namespace star {
class ApplicationProtocol {
protected:
	float p_deltaTime;

public:
	virtual bool applicationDidFinishLaunching() = 0;
	virtual float getDeltaTime() = 0;
};
} // namespace star
