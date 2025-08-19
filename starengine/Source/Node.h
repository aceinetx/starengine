#pragma once
#include "Object.h"
#include "Vec2.h"
#include <vector>

namespace star {
/** Node
 *
 * Base class for all nodes
 *
 * Controls the position, children and drawing
 */
class Node : public Object {
protected:
	Vec2 p_position;
	std::vector<Node*> children;
	Node* p_parent;

public:
	Node();
	virtual ~Node();

	/**
	 * Initialize
	 */
	virtual bool init();
	/**
	 * Set position from Vec2
	 */
	virtual void setPosition(Vec2 pos);
	/**
	 * Set X position
	 */
	virtual void setPositionX(float x);
	/**
	 * Set Y position
	 */
	virtual void setPositionY(float y);
	/**
	 * Get position in Vec2
	 */
	virtual Vec2 getPosition();
	/**
	 * Get position X
	 */
	virtual float getPositionX();
	/**
	 * Get position Y
	 */
	virtual float getPositionY();

	/**
	 * Add the child to the current node
	 * Retains the child and sets the child's parent to the current node
	 */
	virtual void addChild(Node* child);

	/**
	 * Set the parent of the current node
	 */
	virtual void setParent(Node* parent);
	/**
	 * Get the parent of the current node
	 */
	virtual Node* getParent();

	/**
	 * Draw the node, in base class does nothing, derived class should override it
	 */
	virtual void draw();

	/**
	 * Get the content size of the node. In other words, how much space does this node take
	 */
	virtual Vec2 getContentSize();

	/**
	 * Create an autoreleased Node
	 */
	static Node* create();
};
} // namespace star
