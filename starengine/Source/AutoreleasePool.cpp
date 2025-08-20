#include "AutoreleasePool.h"
#include <cstdio>

using namespace star;

AutoreleasePool AutoreleasePool::p_instance;

AutoreleasePool* AutoreleasePool::getInstance() {
	return &p_instance;
}

void AutoreleasePool::addObject(Object* obj) {
	printf("[star] add %p\n", obj);
	objectArray.emplace_back(obj);
}

void AutoreleasePool::clear() {
	std::vector<Object*> releasings;
	releasings.swap(objectArray);
	for (const auto& obj : releasings) {
		obj->release();
	}
}

bool AutoreleasePool::contains(Object* obj) {
	return std::ranges::find(objectArray.begin(), objectArray.end(), obj) != objectArray.end();
}
