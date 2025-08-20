#pragma once

#include "Node.h"
#include <functional>
namespace star {

struct ScheduleEntry {
  std::function<void(float)> function;
  float initialTime;
  float time;
  bool once;
  Node* target;
};

/** Scheduler
 *
 * Manages schedules
 */
class Scheduler {
protected:
  static Scheduler p_instance;

  std::vector<ScheduleEntry> p_schedules;

public:
  static Scheduler* getInstance();

  /** Add an update schedule for a given target that runs every frame */
  void scheduleUpdateForTarget(Node* target);
  /** Add a schedule for a given target that runs only once */
  void scheduleOnceForTarget(Node* target, std::function<void(float)> function, float timeout);
  /** Removes all schedules from a given target */
  void removeAllSchedulesFromTarget(Node* target);
  size_t getSchedulesCount();

  void update(float dt);
};
} // namespace star
