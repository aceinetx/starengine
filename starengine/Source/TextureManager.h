#pragma once
#include <raylib.h>
#include <string>
#include <unordered_map>

namespace star {
/** TextureManager
 *
 * Manages textures, if a texture is already loaded it will not load it again
 */
class TextureManager {
protected:
  /** global instance */
  static TextureManager p_instance;

  /** textures map, maps a texture path to the texture resource */
  std::unordered_map<std::string, Texture2D> p_textures;

public:
  /** Get the global instance */
  static TextureManager* getInstance();

  /**
   * Loads or gets the Texture2D raylib resource from a given path
   */
  Texture2D getTexture(std::string path);
  /**
   * Unloads all textures
   *
   * Automatically called by Application when the game closes
   */
  void unloadAllTextures();
};
} // namespace star
