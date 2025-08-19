#pragma once
#include "Macros.h"
#include "Node.h"
#include <raylib.h>

using rlCamera = Camera2D;

namespace star {
class Camera : public Node {
protected:
	rlCamera p_rlCamera;

public:
	virtual void setPosition(Vec2 pos);
	virtual void setPositionX(float x);
	virtual void setPositionY(float y);
	virtual Vec2 getPosition();
	virtual float getPositionX();
	virtual float getPositionY();

	virtual rlCamera getRaylibCamera();

	CREATE_FUNC(Camera);
};
} // namespace star
