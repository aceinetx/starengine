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
  pos.y = windowSize.y - pos.y;

  int texW, texH; // texture size
  SDL_QueryTexture(p_texture, NULL, NULL, &texW, &texH);

  SDL_Rect dstrect(pos.x, pos.y, ((float)texW * scale), ((float)texH * scale));
  dstrect.x -= texW / 2.0f * scale;
  dstrect.y -= texH / 2.0f * scale;
  SDL_Point center(texW / 2.0f * scale, texH / 2.0f * scale);
  SDL_RenderCopyEx(renderer, p_texture, NULL, &dstrect, rotation, &center,
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
