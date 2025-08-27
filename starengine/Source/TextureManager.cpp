#include "TextureManager.h"
#include "Application.h"
#include "Macros.h"
#include "fmt/base.h"
#include <SDL2/SDL_image.h>

using namespace star;

TextureManager TextureManager::p_instance;

TextureManager* TextureManager::getInstance() {
  return &p_instance;
}

SDL_Texture* TextureManager::getTexture(std::string path) {
  if (!p_textures.contains(path)) {
    std::string fullPath = ("Content/" + path);
#ifdef STAR_PLATFORM_SWITCH
    fullPath = ("romfs:/Content/" + path);
#endif
    fmt::println("[star] load texture from {}", fullPath);
    // = IMG_LoadTexture(Application::getInstance()->getRenderer(), fullPath.c_str());
    auto surface = IMG_Load(fullPath.c_str());
    STARASSERT(surface, "{}", SDL_GetError());
    p_textures[path] =
        SDL_CreateTextureFromSurface(Application::getInstance()->getRenderer(), surface);
    SDL_FreeSurface(surface);
  }
  STARASSERT(p_textures[path], "{} {}", SDL_GetError(),
             (void*)Application::getInstance()->getRenderer());
  return p_textures[path];
}

void TextureManager::unloadAllTextures() {
  for (const auto& [_, texture] : p_textures) {
    SDL_DestroyTexture(texture);
  }
}
