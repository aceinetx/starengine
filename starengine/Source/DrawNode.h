#pragma once
#include "ApplicationProtocol.h"
#include "Color.h"
#include "Macros.h"
#include "Node.h"
#include <climits>
#include <raylib.h>

namespace star {
/** DrawNode
 *
 * A node you can draw primitive shapes on
 */
class DrawNode : public Node {
protected:
  /** Render texture to draw on */
  RenderTexture p_renderTexture;
  /** p_renderTexture.texture. ! DON'T UNLOAD THIS, UNLOAD p_renderTexture INSTEAD ! */
  Texture p_texture;

public:
  ~DrawNode();
  virtual bool init() override;
  void draw() override;

  void clear(Color4B color);
  void drawRectangleOutline(float x, float y, float width, float height, float outlineWidth,
                            Color4B outlineColor);

  CREATE_FUNC(DrawNode);
};
} // namespace star