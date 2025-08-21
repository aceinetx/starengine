#pragma once

#include "Macros.h"
#include "Node.h"
#include <string>

namespace star {
/** Label
 *
 * Display text on the screen
 */
class Label : public Node {
protected:
  /** text of the label */
  std::string p_string;
  /** font spacing */
  float p_spacing;
  /** font size */
  float p_fontSize;
  /** raylib's font resource */
  Font p_font;
  /** font path */
  std::string p_fontPath;

public:
  virtual bool init() override;

  /**
   * Set the label's text
   */
  virtual void setString(std::string string);
  /**
   * Get the label's text
   */
  virtual std::string getString();

  /**
   * Draw the label on the screen
   */
  virtual void draw() override;

  virtual Vec2 getContentSize() override;

  /**
   * Set the label's font
   */
  virtual void setFont(std::string path);
  /**
   * Get the label's font path
   */
  virtual std::string getFontPath();

  /**
   * Set the label's font size
   */
  virtual void setFontSize(float size);
  /**
   * Get the label's font size
   */
  virtual float getFontSize();

  /**
   * Create an autoreleased Label
   */
  CREATE_FUNC(Label);
  /** Create a label with text, font and font size */
  static Label* createWithFont(std::string text, std::string font, float fontSize);
  /** Create a label with text and font size */
  static Label* createWithDefaultFont(std::string text, float fontSize);
};
} // namespace star
