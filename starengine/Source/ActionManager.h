#pragma once
#include "Action.h"
#include "ObjectVector.h"

namespace star {
class ActionManager {
  /** ActionManager
   *
   * Manages actions, runs step() method on each action every frame
   */
protected:
  static ActionManager p_instance;

  ObjectVector<Action*> p_actions;

public:
  static ActionManager* getInstance();

  /**
   * Run action for a given target
   *
   * Adds the action to p_actions vector
   */
  void runActionForTarget(Action* action, Node* target);
  /**
   * Remove all actions from a given target
   */
  void removeAllActionsFromTarget(Node* target);
  /**
   * Remove all done actions
   */
  void removeAllDoneActions();
  /**
   * Run step() on every added action
   */
  void stepActions(float dt);
};
} // namespace star
