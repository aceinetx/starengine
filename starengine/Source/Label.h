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
	std::string p_string;
	float p_spacing;
	float p_fontSize;
	Font p_font;
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
	static Label* createWithFont(std::string text, std::string font, float fontSize);
	static Label* createWithDefaultFont(std::string text, float fontSize);
};
} // namespace star
