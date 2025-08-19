#pragma once
#include "Camera.h"
#include "Macros.h"
#include "Node.h"

namespace star {
/*
 * Scene
 * Always the parent node of the scene graph
 * Creates the camera for you
 */
class Scene : public Node {
protected:
	Camera* p_camera;

public:
	virtual ~Scene() override;

	bool init() override;
	Camera* getCamera();

	CREATE_FUNC(Scene);
};
} // namespace star
