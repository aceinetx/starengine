#include "Label.h"
#include "FontManager.h"
#include <raylib.h>
#include <rlgl.h>

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
  float scale = p_getScaleTransform();
  float rotation = p_getRotationTransform();

  Vector2 size = MeasureTextEx(p_font, p_string.c_str(), p_fontSize, p_spacing);
  Vec2 pos = p_getPositionTransform();
  Vector2 rlPos = CLITERAL(Vector2){pos.x, GetScreenHeight() - pos.y};
  rlPos.x /= scale;
  rlPos.y /= scale;

  rlPushMatrix();
  rlScalef(scale, scale, 1.0f);
  DrawTextPro(p_font, p_string.c_str(), rlPos, Vector2(size.x / 2, size.y / 2), rotation,
              p_fontSize, p_spacing, getColor().toRaylib());
  rlPopMatrix();

  Node::draw();
}

void Label::setFont(std::string path) {
  p_font = p_fontManager->getFont(path);
  p_fontPath = path;
}

std::string Label::getFontPath() {
  return p_fontPath;
}

void Label::setFontSize(float size) {
  p_fontSize = size;
}

float Label::getFontSize() {
  return p_fontSize;
}

Vec2 Label::getContentSize() {
  Vector2 size = MeasureTextEx(p_font, p_string.c_str(), p_fontSize, p_spacing);
  return Vec2(size.x, size.y);
}

Label* Label::createWithFont(std::string text, std::string font, float fontSize) {
  auto label = Label::create();
  label->setFontSize(fontSize);
  label->setFont(font);
  label->setString(text);
  return label;
}

Label* Label::createWithDefaultFont(std::string text, float fontSize) {
  auto label = Label::create();
  label->setFontSize(fontSize);
  label->setString(text);
  return label;
}
