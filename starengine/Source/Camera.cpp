#include "Camera.h"

using namespace star;

void star::Camera::setPosition(Vec2 pos) {
	p_rlCamera.target.x = pos.x;
	p_rlCamera.target.y = pos.y;
}
void star::Camera::setPositionX(float x) {
	p_rlCamera.target.x = x;
}
void star::Camera::setPositionY(float y) {
	p_rlCamera.target.y = y;
}
Vec2 star::Camera::getPosition() {
	Vec2 pos;
	pos.x = p_rlCamera.target.x;
	pos.y = p_rlCamera.target.y;
	return pos;
}
float star::Camera::getPositionX() {
	return p_rlCamera.target.x;
}
float star::Camera::getPositionY() {
	return p_rlCamera.target.y;
}

rlCamera star::Camera::getRaylibCamera() {
	return p_rlCamera;
}
