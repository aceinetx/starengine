#include "Node.h"
#include "Macros.h"
#include "Scheduler.h"
#include <cstdio>

using namespace star;

Node::Node() : p_position(Vec2(0, 0)), p_parent(nullptr), p_scale(1.0f), p_rotation(0.0f) {
}

Node::~Node() {
  removeAllChildrenAndCleanup();
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

void Node::setScale(float scale) {
  if (scale < 0)
    return; // Why would you want negative scale?
  p_scale = scale;
}
float Node::getScale() {
  return p_scale;
}

void Node::setRotation(float rotation) {
  p_rotation = rotation;
}
float Node::getRotation() {
  return p_rotation;
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
  p_children.push_back(child);
  child->setParent(this);
  child->onEnter();
}

void Node::onEnter() {
  fmt::println("[star] {} entered", (void*)this);
}
void Node::onExit() {
  fmt::println("[star] {} exited", (void*)this);
}

void Node::setParent(Node* parent) {
  p_parent = parent;
}

Node* Node::getParent() {
  return p_parent;
}

void Node::draw() {
  for (auto child : p_children) {
    child->draw();
  }
}

Vec2 Node::getContentSize() {
  return Vec2(0, 0);
}

const std::vector<Node*> Node::getChildren() {
  return p_children;
}

void Node::update(float dt) {
}

void Node::scheduleUpdate() {
  Scheduler::getInstance()->scheduleUpdateForTarget(this);
}

void Node::scheduleOnce(std::function<void(float)> function, float timeout) {
  Scheduler::getInstance()->scheduleOnceForTarget(this, function, timeout);
}

void Node::cleanup() {
  Scheduler::getInstance()->removeAllSchedulesFromTarget(this);
}

void Node::removeFromParentAndCleanup() {
  cleanup();
  if (getParent() != nullptr)
    getParent()->removeChild(this);
  else
    release();
}

void Node::removeChild(Node* child) {
  for (size_t i = 0; i < p_children.size(); i++) {
    Node* node = p_children.at(i);
    if (node == child) {
      child->onExit();
      child->release();
      p_children.erase(p_children.begin() + i);
    }
  }
}

void Node::removeChildAndCleanup(Node* child) {
  child->cleanup();
  removeChild(child);
}

void Node::removeAllChildrenAndCleanup() {
  for (Node* child : p_children) {
    child->onExit();
    child->cleanup();
    child->removeAllChildrenAndCleanup();
    child->release();
  }
  p_children.clear();
}

Node* Node::create() {
  Node* pRet = new Node();
  pRet->p_refCount = 1;
  printf("[star] malloc %p\n", pRet);
  if (pRet && pRet->init()) {
    pRet->autorelease();
  } else {
    delete pRet;
    return nullptr;
  }
  return pRet;
}
