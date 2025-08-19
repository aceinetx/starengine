#include "Camera.h"
#include <raylib.h>

using namespace star;

// We can't use Camera:: since the compiler will confuse it with raylib's camera
rlCamera star::Camera::getRaylibCamera() {
	rlCamera camera;
	// TODO: Use actual position
	camera.offset = Vector2{0, 0};
	camera.target = Vector2{0, 0};
	camera.zoom = p_zoom;
	camera.rotation = 0.0f;
	return camera;
}

float star::Camera::getZoom() {
	return p_zoom;
}

void star::Camera::setZoom(float zoom) {
	p_zoom = zoom;
}
