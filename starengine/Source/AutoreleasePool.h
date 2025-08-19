#pragma once
#include "Object.h"
#include <vector>

namespace star {
/** Autorelease pool
 * This is a pool that contains objects which were marked as autorelease in the current frame
 * At the end of a frame the pool is drained (cleared) and all objects are released
 */
class AutoreleasePool {
protected:
	static AutoreleasePool p_instance;

private:
	std::vector<Object*> objectArray;

public:
	static AutoreleasePool* getInstance();

	/**
	 * Adds an object to the pool
	 */
	void addObject(Object* obj);
	/**
	 * Drains (clears) the pool, releasing all of the added objects
	 */
	void clear();
	/**
	 * Check if the pool contains a certain object
	 */
	bool contains(Object* obj);
};
} // namespace star
