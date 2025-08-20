#pragma once
#include "Action.h"
#include "ObjectVector.h"

namespace star {
class ActionManager {
protected:
  static ActionManager p_instance;

  ObjectVector<Action*> p_actions;

public:
  static ActionManager* getInstance();
};
} // namespace star
