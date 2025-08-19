#pragma once

namespace star {
/** Auto memory managed object
 * Base class for all nodes
 */
class Object {
protected:
	unsigned int p_refCount;

public:
	Object();
	virtual ~Object();

	/**
	 * Increment the reference count
	 */
	void retain();
	/**
	 * Decrement the reference count
	 * Frees itself if the reference count == 0
	 */
	void release();
	/**
	 * Add the object to the autorelease pool
	 */
	Object* autorelease();
	/**
	 * Get the reference count
	 */
	unsigned int getReferenceCount();
};
} // namespace star
