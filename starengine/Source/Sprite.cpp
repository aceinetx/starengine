#include "Sprite.h"
#include "Application.h"
#include "TextureManager.h"
#include <SDL2/SDL.h>

using namespace star;

void Sprite::setTexture(std::string texturePath) {
  p_texture = p_textureManager->getTexture(texturePath);
}

void Sprite::draw() {

  Vec2 pos = p_getPositionTransform();
  float scale = p_getScaleTransform();
  float rotation = p_getRotationTransform();
  auto renderer = p_application->getRenderer();
  auto window = p_application->getWindow();
  SDL_Point windowSize;
  SDL_GetWindowSize(window, &windowSize.x, &windowSize.y);

  // Rectangle src(0, 0, p_texture.width, p_texture.height);
  // Rectangle dest(pos.x, GetScreenHeight() - pos.y, p_texture.width * scale,
  // p_texture.height * scale);
  // Vector2 origin((float)p_texture.width / 2 * scale, (float)p_texture.height / 2 * scale);
  // DrawTexturePro(p_texture, src, dest, origin, rotation, getColor().toRaylib());
  SDL_Rect srcrect(0, 0, 0, 0);
  SDL_QueryTexture(p_texture, NULL, NULL, &srcrect.w, &srcrect.h);
  SDL_Rect dstrect(pos.x, windowSize.y - pos.y, srcrect.w * scale, srcrect.h * scale);
  SDL_Point center(0, 0);
  SDL_RenderCopyEx(renderer, p_texture, &srcrect, &dstrect, rotation, &center,
                   SDL_RendererFlip::SDL_FLIP_NONE);

  Node::draw();
}

Vec2 Sprite::getContentSize() {
  int w, h;
  SDL_QueryTexture(p_texture, NULL, NULL, &w, &h);
  return Vec2(w, h);
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
