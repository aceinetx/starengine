#pragma once
#include "Node.h"
#include <SDL2/SDL.h>
#include <string>

namespace star {
/** Sprite
 *
 * Draws textures on the screen
 */
class Sprite : public Node {
protected:
  /** texture of the sprite */
  SDL_Texture* p_texture;

public:
  /** Set the sprite's texture from the path */
  virtual void setTexture(std::string texturePath);
  virtual void draw() override;
  virtual Vec2 getContentSize() override;

  static Sprite* create(std::string texturePath);
};
} // namespace star
