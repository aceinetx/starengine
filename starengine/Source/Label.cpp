#include "Label.h"
#include <raylib.h>

using namespace star;

bool Label::init() {
	if (!Node::init())
		return false;

	fontSize = 30.0f;
	spacing = fontSize / 10.0f;

	return true;
}

void Label::setString(std::string string) {
	this->string = string;
}

std::string Label::getString() {
	return this->string;
}

void Label::draw() {
	Vector2 size = MeasureTextEx(GetFontDefault(), string.c_str(), fontSize, spacing);
	Vec2 pos = getPosition();
	pos.x -= size.x / 2;
	pos.y += size.y / 2;
	Vector2 rlPos = CLITERAL(Vector2){pos.x, GetScreenHeight() - pos.y};
	DrawTextEx(GetFontDefault(), string.c_str(), rlPos, fontSize, spacing, WHITE);
}
