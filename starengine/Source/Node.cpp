#include "Node.h"

using namespace star;

Node::Node() : p_position(Vec2(0, 0)) {
}

Node::~Node() {
	for (Node* child : children)
		delete child;
}

bool Node::init() {
	return true;
}

Node* Node::create() {
	Node* pRet = new Node();
	if (!pRet->init())
		return nullptr;
	return pRet;
}
