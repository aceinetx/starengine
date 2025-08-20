#include "Sprite.h"
#include "TextureManager.h"
#include <raylib.h>

using namespace star;

void Sprite::setTexture(std::string texturePath) {
  p_texture = TextureManager::getInstance()->getTexture(texturePath);
}

void Sprite::draw() {
  Vec2 pos = getPosition() * getParent()->getScale();
  pos += getParent()->getPosition();
  float scale = getScale() / (1.0f / getParent()->getScale());

  // Ugly math goin' on here!
  Rectangle src(0, 0, p_texture.width, p_texture.height);
  Rectangle dest(pos.x, GetScreenHeight() - pos.y, p_texture.width * scale,
                 p_texture.height * scale);
  Vector2 origin((float)p_texture.width / 2 * scale, (float)p_texture.height / 2 * scale);
  DrawTexturePro(p_texture, src, dest, origin, getRotation(), WHITE);

  Node::draw();
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
