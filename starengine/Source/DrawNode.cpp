#include "DrawNode.h"
#include "ClassFormatters.h"
#include "Color.h"
#include "Director.h"
#include "Scheduler.h"
#include <raylib.h>

using namespace star;

DrawNode::~DrawNode() {
  UnloadRenderTexture(p_renderTexture);
  fmt::println("[star] render texture unloaded");
}

bool DrawNode::init() {
  if (!Node::init())
    return false;

  auto winSize = p_director->getVisibleSize();
  p_renderTexture = LoadRenderTexture(1, 1);
  p_texture = p_renderTexture.texture;
  fmt::println("[star] created a render texture with size {}", winSize);

  return true;
}

void DrawNode::draw() {
  Vec2 pos = p_getPositionTransform();
  float scale = p_getScaleTransform();
  float rotation = p_getRotationTransform();

  Rectangle src(0, 0, p_texture.width, p_texture.height);
  Rectangle dest(pos.x, GetScreenHeight() - pos.y, p_texture.width * scale,
                 p_texture.height * scale);
  Vector2 origin((float)p_texture.width / 2 * scale, (float)p_texture.height / 2 * scale);
  DrawTexturePro(p_texture, src, dest, origin, rotation, WHITE);

  DrawTexture(p_renderTexture.texture, 0, 0, WHITE);

  Node::draw();
}

void DrawNode::clear(Color4B color) {
  BeginTextureMode(p_renderTexture);
  ClearBackground(WHITE);
  EndTextureMode();
}

void DrawNode::drawRectangleOutline(float x, float y, float width, float height, float outlineWidth,
                                    Color4B outlineColor) {
  BeginTextureMode(p_renderTexture);
  Rectangle rec;
  rec.x = x;
  rec.y = y;
  rec.width = width;
  rec.height = height;
  DrawRectangleLinesEx(rec, outlineWidth, outlineColor.toRaylib());
  EndTextureMode();
}