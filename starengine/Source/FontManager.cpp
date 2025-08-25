#include "FontManager.h"
#include "Macros.h"
#include <raylib.h>

using namespace star;

FontManager FontManager::p_instance;

FontManager* FontManager::getInstance() {
  return &p_instance;
}

Font FontManager::getFont(std::string path) {
  if (!p_fonts.contains(path)) {
    std::string fullPath = ("Content/" + path);
#ifdef STAR_PLATFORM_SWITCH
    fullPath = ("romfs:/Content/" + path);
#endif
    fmt::println("[star] load font from {}", fullPath);
    p_fonts[path] = LoadFont(fullPath.c_str());
  }
  // STARASSERT(p_fonts[path].glyphCount > 0, "glyphCount <= 0, is the font path valid?");
  return p_fonts[path];
}

void FontManager::unloadAllFonts() {
  for (const auto& [_, font] : p_fonts) {
    UnloadFont(font);
  }
}
