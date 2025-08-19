#pragma once

#include "Macros.h"
#include "Node.h"
#include <string>

namespace star {
class Label : public Node {
protected:
	std::string string;
	float spacing;
	float fontSize;

public:
	virtual bool init() override;

	virtual void setString(std::string string);
	virtual std::string getString();

	virtual void draw() override;

	CREATE_FUNC(Label);
};
} // namespace star
