#include "Camera.h"
#include "Director.h"
#include <fmt/base.h>
#include <raylib.h>

using namespace star;

bool star::Camera::init() {
  if (!Node::init())
    return false;

  p_zoom = 1.f;

  return true;
}

// We can't use Camera:: since the compiler will confuse it with raylib's camera
rlCamera star::Camera::getRaylibCamera() {
  auto director = Director::getInstance();
  auto winSize = director->getVisibleSize();
  auto pos = getPosition();

  rlCamera camera;
  camera.zoom = p_zoom;
  camera.rotation = getRotation();
  camera.target = CLITERAL(Vector2){pos.x, pos.y};
  camera.offset = CLITERAL(Vector2){winSize.x / 2, winSize.y / 2};
  return camera;
}

float star::Camera::getZoom() {
  return p_zoom;
}

void star::Camera::setZoom(float zoom) {
  p_zoom = zoom;
}

Vec2 star::Camera::getContentSize() {
  return Director::getInstance()->getVisibleSize();
}
