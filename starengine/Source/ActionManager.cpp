#include "ActionManager.h"

using namespace star;

ActionManager ActionManager::p_instance;

ActionManager* ActionManager::getInstance() {
  return &p_instance;
}
