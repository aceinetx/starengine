#include "FontManager.h"
#include "Macros.h"

using namespace star;

FontManager FontManager::p_instance;

FontManager* FontManager::getInstance() {
	return &p_instance;
}

Font FontManager::getFont(std::string path) {
	if (p_fonts.contains(path))
		p_fonts[path] = LoadFont(path.c_str());
	STARASSERT(p_fonts[path].glyphCount > 0, "glyphCount <= 0, is the font path valid?");
	return p_fonts[path];
}
