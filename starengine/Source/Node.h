#pragma once
#include "Object.h"
#include "Vec2.h"
#include <vector>

namespace star {
class Node : public Object {
protected:
	Vec2 p_position;
	std::vector<Node*> children;
	Node* p_parent;

public:
	Node();
	virtual ~Node();

	virtual bool init();
	virtual void setPosition(Vec2 pos);
	virtual void setPositionX(float x);
	virtual void setPositionY(float y);
	virtual Vec2 getPosition();
	virtual float getPositionX();
	virtual float getPositionY();

	virtual void addChild(Node* child);

	virtual void setParent(Node* parent);
	virtual Node* getParent();

	static Node* create();
};
} // namespace star
