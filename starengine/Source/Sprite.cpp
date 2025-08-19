#include "Sprite.h"
#include "TextureManager.h"
#include <raylib.h>

using namespace star;

void Sprite::setTexture(std::string texturePath) {
	p_texture = TextureManager::getInstance()->getTexture(texturePath);
}

void Sprite::draw() {
	Vec2 pos = getPosition();
	pos += getParent()->getPosition();

	// Ugly math goin' on here!
	Rectangle src(0, 0, p_texture.width, p_texture.height);
	Rectangle dest(pos.x, GetScreenHeight() - pos.y, p_texture.width * getScale(), p_texture.height * getScale());
	Vector2 origin((float)p_texture.width / 2 * getScale(), (float)p_texture.height / 2 * getScale());
	DrawTexturePro(p_texture, src, dest, origin, getRotation(), WHITE);
}

Vec2 Sprite::getContentSize() {
	return Vec2(p_texture.width, p_texture.height);
}

Sprite* Sprite::create(std::string texturePath) {
	auto pRet = new Sprite();
	pRet->setTexture(texturePath);
	if (pRet && pRet->init()) {
		pRet->autorelease();
	} else {
		delete pRet;
		return nullptr;
	}
	return pRet;
}
