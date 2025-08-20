#include "TextureManager.h"
#include "Macros.h"
#include "fmt/base.h"
#include <raylib.h>

using namespace star;

TextureManager TextureManager::p_instance;

TextureManager* TextureManager::getInstance() {
  return &p_instance;
}

Texture2D TextureManager::getTexture(std::string path) {
  if (!p_textures.contains(path)) {
    std::string fullPath = ("Content/" + path);
    fmt::println("[star] load texture from {}", fullPath);
    p_textures[path] = LoadTexture(fullPath.c_str());
  }
  STARASSERT(p_textures[path].width > 0, "p_textures[path].width <= 0, is the texture path valid?");
  return p_textures[path];
}

void TextureManager::unloadAllTextures() {
  for (const auto& [_, texture] : p_textures) {
    UnloadTexture(texture);
  }
}
