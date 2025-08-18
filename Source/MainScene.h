#pragma once
#include "star.h"

class MainScene : public star::Scene {
public:
	bool init() override;

	CREATE_FUNC(MainScene);
};
