#pragma once
#include "Node.h"
#include <functional>

namespace star {
/** ScheduleEntry
 *
 * Contains data about a certain schedule
 */
struct ScheduleEntry {
  /** scheduled function */
  std::function<void(float)> function;
  /** initial time, 0 if run every frame */
  float initialTime;
  /** current time, when reaches 0, call the scheduled function and set it to the initial time */
  float time;
  /** only run the action once? */
  bool once;
  /** target of the scheduled entry */
  Node* target;
};

/** Scheduler
 *
 * Manages schedules
 */
class Scheduler {
protected:
  /** global instance */
  static Scheduler p_instance;

  /** schedule array of the entire game */
  std::vector<ScheduleEntry> p_schedules;

public:
  /** get the global instance */
  static Scheduler* getInstance();

  /** Add an update schedule for a given target that runs every frame */
  void scheduleUpdateForTarget(Node* target);
  /** Add a schedule for a given target that runs only once */
  void scheduleOnceForTarget(Node* target, std::function<void(float)> function, float timeout);
  /** Removes all schedules from a given target */
  void removeAllSchedulesFromTarget(Node* target);
  /** Get the total count of all schedules */
  size_t getSchedulesCount();

  /** Update, run schedules if needed */
  void update(float dt);
};
} // namespace star
