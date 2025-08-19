#pragma once
#include "Object.h"
#include <vector>

namespace star {
class AutoreleasePool {
protected:
	static AutoreleasePool p_instance;

private:
	std::vector<Object*> objectArray;

public:
	static AutoreleasePool* getInstance();

	void addObject(Object* obj);
	void clear();
	bool contains(Object* obj);
};
} // namespace star
