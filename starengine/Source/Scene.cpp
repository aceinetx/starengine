#include "Scene.h"
#include "Camera.h"
#include "Director.h"

using namespace star;

Scene::~Scene() {
}

bool Scene::init() {
	if (!Node::init())
		return false;

	p_camera = Camera::create();
	p_camera->setPosition(Director::getInstance()->getVisibleSize() / 2);

	addChild(p_camera);

	return true;
}

star::Camera* Scene::getCamera() {
	return p_camera;
}
