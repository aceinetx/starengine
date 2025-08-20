#include "Scheduler.h"
#include <cstdint>
#include <fmt/base.h>

using namespace star;

Scheduler Scheduler::p_instance;

Scheduler* Scheduler::getInstance() {
  return &p_instance;
}

void Scheduler::scheduleUpdateForTarget(Node* target) {
  ScheduleEntry schedule;
  schedule.target = target;
  schedule.function = std::bind(&Node::update, target, std::placeholders::_1);
  schedule.initialTime = 0.0f;
  schedule.time = 0.0f;
  schedule.once = false;
  p_schedules.push_back(schedule);
  fmt::println("[star] scheduled update for {}", (void*)target);
}

void Scheduler::scheduleOnceForTarget(Node* target, std::function<void(float)> function,
                                      float timeout) {
  ScheduleEntry schedule;
  schedule.target = target;
  schedule.function = function;
  schedule.initialTime = 0.0f;
  schedule.time = timeout;
  schedule.once = true;
  p_schedules.push_back(schedule);
  fmt::println("[star] scheduled once for {}", (void*)target);
}

void Scheduler::removeAllSchedulesFromTarget(Node* target) {
  for (size_t i = 0; i < p_schedules.size(); i++) {
    ScheduleEntry& schedule = p_schedules.at(i);
    if (schedule.target == target) {
      p_schedules.erase(p_schedules.begin() + i);
      i--;
      fmt::println("[star] removed a schedule for {}", (void*)target);
    }
  }
}

size_t Scheduler::getSchedulesCount() {
  return p_schedules.size();
}

void Scheduler::update(float dt) {
  for (size_t i = 0; i < p_schedules.size(); i++) {
    ScheduleEntry& schedule = p_schedules.at(i);

    schedule.time -= dt;
    if (schedule.time <= 0) {
      schedule.function(dt);
      schedule.time = schedule.initialTime;

      if (schedule.once) {
        p_schedules.erase(p_schedules.begin() + i);
        i--;
        fmt::println("[star] removed a schedule for {}", (void*)schedule.target);
      }
    }
  }
}
