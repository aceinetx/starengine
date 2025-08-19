#include "Label.h"
#include <raylib.h>

using namespace star;

bool Label::init() {
	if (!Node::init())
		return false;

	p_fontSize = 30.0f;
	p_spacing = p_fontSize / 10.0f;
	p_font = GetFontDefault();

	return true;
}

void Label::setString(std::string string) {
	this->p_string = string;
}

std::string Label::getString() {
	return this->p_string;
}

void Label::draw() {
	Vector2 size = MeasureTextEx(p_font, p_string.c_str(), p_fontSize, p_spacing);
	Vec2 pos = getPosition();
	pos.x -= size.x / 2;
	pos.y += size.y / 2;
	Vector2 rlPos = CLITERAL(Vector2){pos.x, GetScreenHeight() - pos.y};
	DrawTextEx(p_font, p_string.c_str(), rlPos, p_fontSize, p_spacing, WHITE);
}

Vec2 Label::getContentSize() {
	Vector2 size = MeasureTextEx(p_font, p_string.c_str(), p_fontSize, p_spacing);
	return Vec2(size.x, size.y);
}
