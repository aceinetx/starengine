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

void ActionManager::stepActions(float dt) {
  for (Action* action : p_actions) {
    action->step(dt);
  }
}
