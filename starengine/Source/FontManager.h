#pragma once
#include <raylib.h>
#include <string>
#include <unordered_map>

namespace star {
/** FontManager
 *
 * Manages fonts, if a font is already loaded it will not load it again
 */
class FontManager {
protected:
  /** global instance */
  static FontManager p_instance;

  /** fonts map, maps a font path to the font resource */
  std::unordered_map<std::string, Font> p_fonts;

public:
  /** get the global instance */
  static FontManager* getInstance();

  /**
   * Loads or gets the Font raylib resource from a given path
   */
  Font getFont(std::string path);
  /**
   * Unloads all fonts
   *
   * Automatically called by Application when the game closes
   */
  void unloadAllFonts();
};
} // namespace star
