#pragma once
#include "Vec2.h"
#include <vector>

namespace star {
class Node {
protected:
	Vec2 p_position;
	std::vector<Node*> children;

public:
	Node();
	virtual ~Node();

	virtual bool init();

	static Node* create();
};
} // namespace star
