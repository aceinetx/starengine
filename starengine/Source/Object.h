#pragma once

namespace star {
class Object {
protected:
	unsigned int p_refCount;

public:
	Object();
	virtual ~Object();

	void retain();
	void release();
	Object* autorelease();
	unsigned int getReferenceCount();
};
} // namespace star
