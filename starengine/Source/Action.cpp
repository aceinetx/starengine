#include "Action.h"

using namespace star;

bool Action::isDone() {
  return p_done;
}

void Action::step(float dt) {
  p_elapsed += dt;

  float updateDt = std::max(0.0f, // needed for rewind. elapsed could be negative
                            std::min(1.0f, p_elapsed / p_duration));

  this->update(updateDt);

  p_done = p_elapsed >= p_duration;
}

void Action::update(float time) {
}

void Action::startWithTarget(Node* target) {
  p_target = target;
}

float Action::getDuration() {
  return p_duration;
}
