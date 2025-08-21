#pragma once
#include "Object.h"
#include "ObjectVector.h"
#include "Vec2.h"
#include <functional>
#include <vector>

namespace star {
class Action;
class Director;
class FontManager;
class TextureManager;
class Scheduler;
class EventDispatcher;
class ActionManager;

/** Node
 *
 * Base class for all nodes
 *
 * Controls the position, children and drawing
 *
 * This node can run actions and schedule functions
 */
class Node : public Object {
private:
  Vec2 m_position;
  ObjectVector<Node*> m_children;
  Node* m_parent;
  float m_scale;
  float m_rotation;

protected:
  /** director instance */
  Director* p_director;
  /** font manager instance */
  FontManager* p_fontManager;
  /** texture manager instance */
  TextureManager* p_textureManager;
  /** scheduler instance */
  Scheduler* p_scheduler;
  /** event dispatcher instance */
  EventDispatcher* p_eventDispatcher;
  /** action manager instance */
  ActionManager* p_actionManager;

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
   * Set the node's scale
   */
  virtual void setScale(float scale);
  /**
   * Get the node's scale
   */
  virtual float getScale();

  /**
   * Set the node's rotation
   */
  virtual void setRotation(float rotation);
  /**
   * Get the node's rotation
   */
  virtual float getRotation();

  /**
   * Add the child to the current node
   *
   * Retains the child and sets the child's parent to the current node
   */
  virtual void addChild(Node* child);

  /**
   * Called when node enters the tree
   */
  virtual void onEnter();

  /**
   * Called when node exits the tree
   */
  virtual void onExit();

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
   * Get the children array
   */
  virtual const std::vector<Node*> getChildren();

  /**
   * Runs every frame, override if you need
   */
  virtual void update(float dt);

  /**
   * Schedule update
   */
  virtual void scheduleUpdate();

  /**
   * Schedule a function that runs only once
   */
  virtual void scheduleOnce(std::function<void(float)> function, float timeout);

  /**
   * Cleans schedules
   */
  virtual void cleanup();

  /**
   * Removes the child from parent and calls cleanup()
   */
  virtual void removeFromParentAndCleanup();

  /**
   * Removes a certain child
   */
  virtual void removeChild(Node* child);

  /**
   * Removes a certain child and calls cleanup() on it
   */
  virtual void removeChildAndCleanup(Node* child);

  /**
   * Removes all children and calls cleanup() on them
   */
  virtual void removeAllChildrenAndCleanup();

  /**
   * Runs an action
   */
  virtual void runAction(Action* action);

  /**
   * Remove all actions from this node
   */
  virtual void stopAllActions();

  /**
   * Create an autoreleased Node
   */
  static Node* create();
};
} // namespace star
