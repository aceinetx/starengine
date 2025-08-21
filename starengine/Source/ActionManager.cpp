#include "ActionManager.h"

using namespace star;

ActionManager ActionManager::p_instance;

ActionManager* ActionManager::getInstance() {
  return &p_instance;
}

void ActionManager::runActionForTarget(Action* action, Node* target) {
  action->p_target = target;

  p_actions.push_back(action);
}

void ActionManager::removeAllActionsFromTarget(Node* target) {
  for (size_t i = 0; i < p_actions.size(); i++) {
    if (p_actions[i]->p_target == target) {
      p_actions[i]->release();
      p_actions.erase(p_actions.begin() + i);
    }
  }
}

void ActionManager::stepActions(float dt) {
  for (Action* action : p_actions) {
    action->step(dt);
  }
}
