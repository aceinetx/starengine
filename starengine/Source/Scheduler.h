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

class Scheduler {
protected:
	static Scheduler p_instance;

	std::vector<ScheduleEntry> p_schedules;

public:
	static Scheduler* getInstance();

	void scheduleUpdateForTarget(Node* target);
	void removeAllSchedulesFromTarget(Node* target);
	size_t getSchedulesCount();

	void update(float dt);
};
} // namespace star
