#include "Node.h"
#include "Macros.h"
#include <cstdio>

using namespace star;

Node::Node() : p_position(Vec2(0, 0)) {
}

Node::~Node() {
	for (Node* child : children) {
		child->p_parent = nullptr;
		delete child;
	}
}

bool Node::init() {
	return true;
}

void Node::setPosition(Vec2 pos) {
	p_position = pos;
}
void Node::setPositionX(float x) {
	p_position.x = x;
}
void Node::setPositionY(float y) {
	p_position.y = y;
}
Vec2 Node::getPosition() {
	return p_position;
}
float Node::getPositionX() {
	return p_position.x;
}
float Node::getPositionY() {
	return p_position.y;
}

void Node::addChild(Node* child) {
	auto assertNotSelfChild([this, child]() -> bool {
		for (Node* parent(getParent()); parent != nullptr; parent = parent->getParent())
			if (parent == child)
				return false;

		return true;
	});
	(void)assertNotSelfChild;
	STARASSERT(assertNotSelfChild(), "A node cannot be the child of his own children");

	child->retain();
	children.push_back(child);
	child->setParent(this);
}

void Node::setParent(Node* parent) {
	p_parent = parent;
}

Node* Node::getParent() {
	return p_parent;
}

Node* Node::create() {
	Node* pRet = new Node();
	pRet->p_refCount = 1;
	printf("malloc %p\n", pRet);
	if (pRet && pRet->init()) {
		pRet->autorelease();
	} else {
		delete pRet;
		return nullptr;
	}
	return pRet;
}
