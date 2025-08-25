#include "Node.h"
#include "Action.h"
#include "ActionManager.h"
#include "Color.h"
#include "Director.h"
#include "EventDispatcher.h"
#include "FontManager.h"
#include "Macros.h"
#include "Scheduler.h"
#include "TextureManager.h"
#include <algorithm>
#include <raymath.h>

using namespace star;

Node::Node()
    : m_position(Vec2(0, 0)), m_parent(nullptr), m_scale(1.0f), m_rotation(0.0f), m_zOrder(0),
      m_color(255, 255, 255, 255) {
  p_director = Director::getInstance();
  p_fontManager = FontManager::getInstance();
  p_textureManager = TextureManager::getInstance();
  p_scheduler = Scheduler::getInstance();
  p_eventDispatcher = EventDispatcher::getInstance();
  p_actionManager = ActionManager::getInstance();
}

Node::~Node() {
  removeAllChildrenAndCleanup();
}

bool Node::init() {
  return true;
}

void Node::setPosition(Vec2 pos) {
  m_position = pos;
}
void Node::setPositionX(float x) {
  m_position.x = x;
}
void Node::setPositionY(float y) {
  m_position.y = y;
}
Vec2 Node::getPosition() {
  return m_position;
}
float Node::getPositionX() {
  return m_position.x;
}
float Node::getPositionY() {
  return m_position.y;
}

void Node::setScale(float scale) {
  if (scale < 0)
    return; // Why would you want negative scale?
  m_scale = scale;
}
float Node::getScale() {
  return m_scale;
}

void Node::setRotation(float rotation) {
  m_rotation = rotation;
}
float Node::getRotation() {
  return m_rotation;
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

  insertChild(child, child->getZOrder());
}

void Node::onEnter() {
  // fmt::println("[star] {} entered", (void*)this);
  m_parent->m_sortSceneGraph();
}
void Node::onExit() {
  // fmt::println("[star] {} exited", (void*)this);
}

void Node::setParent(Node* parent) {
  m_parent = parent;
}

Node* Node::getParent() {
  return m_parent;
}

void Node::draw() {
  for (auto child : m_children) {
    child->draw();
  }
}

Vec2 Node::getContentSize() {
  return Vec2(0, 0);
}

const std::vector<Node*> Node::getChildren() {
  return m_children.vector();
}

void Node::update(float dt) {
}

void Node::scheduleUpdate() {
  p_scheduler->scheduleUpdateForTarget(this);
}

void Node::scheduleOnce(std::function<void(float)> function, float timeout) {
  p_scheduler->scheduleOnceForTarget(this, function, timeout);
}

void Node::cleanup() {
  p_scheduler->removeAllSchedulesFromTarget(this);
  p_eventDispatcher->removeAllListenersFromTarget(this);
  stopAllActions();
  removeAllChildrenAndCleanup();
}

void Node::removeFromParentAndCleanup() {
  cleanup();
  if (getParent() != nullptr)
    getParent()->removeChild(this);
  else
    release();
}

void Node::removeChild(Node* child) {
  for (size_t i = 0; i < m_children.size(); i++) {
    Node* node = m_children.at(i);
    if (node == child) {
      child->onExit();
      m_children.erase(m_children.begin() + i);
    }
  }
  child->m_children.clear();
}

void Node::removeChildAndCleanup(Node* child) {
  child->cleanup();
  removeChild(child);
}

void Node::removeAllChildrenAndCleanup() {
  for (Node* child : m_children) {
    child->onExit();
    child->cleanup();
    child->removeAllChildrenAndCleanup();
  }
  m_children.clear();
}

void Node::runAction(Action* action) {
  action->startWithTarget(this);
  p_actionManager->runActionForTarget(action, this);
}

void Node::stopAllActions() {
  p_actionManager->removeAllActionsFromTarget(this);
}

size_t Node::getNumberOfRunningActions() {
  return p_actionManager->getNumberOfRunningActions(this);
}

void Node::insertChild(Node* child, int zOrder) {
  child->setParent(this);
  child->setZOrder(zOrder);
  m_children.push_back(child);
  child->onEnter();
}

void Node::setZOrder(int zOrder) {
  m_zOrder = zOrder;
  if (m_parent)
    m_parent->m_sortSceneGraph();
}

int Node::getZOrder() {
  return m_zOrder;
}

Color4B Node::getColor() {
  return m_color;
}

void Node::setColor(Color4B color) {
  m_color = color;
}

uint8_t Node::getOpacity() {
  return m_color.a;
}

void Node::setOpacity(uint8_t opacity) {
  m_color.a = opacity;
}

void Node::m_sortSceneGraph() {
  std::sort(m_children.begin(), m_children.end(),
            [](Node* a, Node* b) { return a->getZOrder() < b->getZOrder(); });
  // fmt::println("[star] scene graph sorted");
}

float Node::p_getScaleTransform() {
  if (getParent() == nullptr)
    return getScale();
  float scale = getScale() / (1.0f / getParent()->p_getScaleTransform());
  return scale;
}

float Node::p_getRotationTransform() {
  if (getParent() == nullptr)
    return getRotation();
  float rotation = getRotation() + getParent()->p_getRotationTransform();
  return rotation;
}

Vec2 Node::p_getPositionTransform() {
  if (getParent() == nullptr)
    return getPosition();
  Vec2 pos = getPosition();
  float parentRotDeg = -getParent()->p_getRotationTransform();
  float r = parentRotDeg * (M_PI / 180.0f);
  float s = getParent()->p_getScaleTransform();

  // Scale then rotate then translate
  pos *= s;
  Vec2 rotated = Vec2(pos.x * cosf(r) - pos.y * sinf(r), pos.x * sinf(r) + pos.y * cosf(r));
  rotated += getParent()->p_getPositionTransform();
  pos = rotated;
  return pos;
}

Node* Node::create() {
  Node* pRet = new Node();
  pRet->p_refCount = 1;
  // printf("[star] malloc %p\n", pRet);
  if (pRet && pRet->init()) {
    pRet->autorelease();
  } else {
    delete pRet;
    return nullptr;
  }
  return pRet;
}
