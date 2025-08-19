#include "Camera.h"
#include <raylib.h>

using namespace star;

rlCamera star::Camera::getRaylibCamera() {
	rlCamera camera;
	camera.offset = Vector2{0, 0};
	camera.target = Vector2{0, 0};
	camera.zoom = 1.0f;
	camera.rotation = 0.0f;
	return camera;
}
