#include "Sprite.h"
#include "TextureManager.h"
#include <raylib.h>
#include <raymath.h>

using namespace star;

void Sprite::setTexture(std::string texturePath) {
  p_texture = p_textureManager->getTexture(texturePath);
}

void Sprite::draw() {
  Vec2 pos = getPosition();
  float parentRotDeg = -getParent()->getRotation();
  float r = parentRotDeg * (M_PI / 180.0f);
  float s = getParent()->getScale();

  // Scale then rotate then translate
  pos *= s;
  Vec2 rotated = Vec2(pos.x * cosf(r) - pos.y * sinf(r), pos.x * sinf(r) + pos.y * cosf(r));
  rotated += getParent()->getPosition();
  pos = rotated;

  // Translated scale and rotation
  float scale = getScale() / (1.0f / getParent()->getScale());
  float rotation = getRotation() + getParent()->getRotation();

  // Ugly stuff goin' on here!
  Rectangle src(0, 0, p_texture.width, p_texture.height);
  Rectangle dest(pos.x, GetScreenHeight() - pos.y, p_texture.width * scale,
                 p_texture.height * scale);
  Vector2 origin((float)p_texture.width / 2 * scale, (float)p_texture.height / 2 * scale);
  DrawTexturePro(p_texture, src, dest, origin, rotation, WHITE);

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
