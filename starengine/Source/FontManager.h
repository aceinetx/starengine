#pragma once
#include <raylib.h>
#include <string>
#include <unordered_map>

namespace star {
/**
 * FontManager
 * Manages fonts, if a font is already loaded it will not load it again
 */
class FontManager {
protected:
	static FontManager p_instance;

	std::unordered_map<std::string, Font> p_fonts;

public:
	static FontManager* getInstance();

	/**
	 * Loads or gets the Font raylib resource from a given path
	 */
	Font getFont(std::string path);
};
} // namespace star
