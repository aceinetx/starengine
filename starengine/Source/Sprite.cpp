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
	pos.x -= ((float)p_texture.width / 2) * getScale();
	pos.y += ((float)p_texture.height / 2) * getScale();

	Vector2 rlPos = CLITERAL(Vector2){pos.x, GetScreenHeight() - pos.y};
	DrawTextureEx(p_texture, rlPos, 0.0f, getScale(), WHITE);
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
