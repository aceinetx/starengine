#pragma once
#include "star.h"

class MainScene : public star::Scene {
private:
	star::Sprite* logo;

public:
	bool init() override;

	void update(float dt) override;

	CREATE_FUNC(MainScene);
};
