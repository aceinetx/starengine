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
  p_renderTexture = LoadRenderTexture(winSize.x, winSize.y);
  fmt::println("[star] created a render texture with size {}", winSize);

  setPosition(winSize / 2);

  return true;
}

void DrawNode::draw() {
  Texture2D texture = p_renderTexture.texture;
  Vec2 pos = p_getPositionTransform();
  float scale = p_getScaleTransform();
  float rotation = p_getRotationTransform();

  Rectangle src(0, 0, texture.width, texture.height);
  Rectangle dest(pos.x, GetScreenHeight() - pos.y, texture.width * scale, texture.height * scale);
  Vector2 origin((float)texture.width / 2 * scale, (float)texture.height / 2 * scale);
  DrawTexturePro(texture, src, dest, origin, rotation, getColor().toRaylib());

  Node::draw();
}

void DrawNode::clear(Color4B color) {
  BeginTextureMode(p_renderTexture);
  ClearBackground(color.toRaylib());
  EndTextureMode();
  fmt::println("[star] clear");
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

void DrawNode::drawRectangleFill(float x, float y, float width, float height, Color4B color) {
  BeginTextureMode(p_renderTexture);
  Rectangle rec;
  rec.x = x;
  rec.y = y;
  rec.width = width;
  rec.height = height;
  DrawRectangleRec(rec, color.toRaylib());
  EndTextureMode();
}

void DrawNode::drawCircleOutline(float x, float y, float radius, float outlineWidth,
                                 Color4B outlineColor) {
  BeginTextureMode(p_renderTexture);
  DrawCircleLines(x, y, radius, outlineColor.toRaylib());
  EndTextureMode();
}

void DrawNode::drawCircleFill(float x, float y, float radius, Color4B color) {
  BeginTextureMode(p_renderTexture);
  DrawCircle(x, y, radius, color.toRaylib());
  EndTextureMode();
}