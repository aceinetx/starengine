#pragma once

#include "Macros.h"
#include "Node.h"
#include <string>

namespace star {
/*
 * Label
 * Display text on the screen
 */
class Label : public Node {
protected:
	std::string string;
	float spacing;
	float fontSize;

public:
	virtual bool init() override;

	/*
	 * Set the label's text
	 */
	virtual void setString(std::string string);
	/*
	 * Get the label's text
	 */
	virtual std::string getString();

	/*
	 * Draw the label on the screen
	 */
	virtual void draw() override;

	/*
	 * Create an autoreleased Label
	 */
	CREATE_FUNC(Label);
};
} // namespace star
