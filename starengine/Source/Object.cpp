#include "Object.h"
#include "AutoreleasePool.h"
#include "Macros.h"

using namespace star;

Object::Object() : p_refCount(1) {
}

Object::~Object() {
}

void Object::retain() {
  STARASSERT(p_refCount, "Reference count should be greater than 0");
  // printf("[star] retain %p ref %d\n", this, (int)p_refCount);
  p_refCount++;
}

void Object::release() {
  // printf("[star] release %p ref %d\n", this, (int)p_refCount);
  STARASSERT(p_refCount, "Reference count should be greater than 0");
  --p_refCount;

  if (p_refCount == 0) {
    if (AutoreleasePool::getInstance()->contains(this)) {
      STARASSERT(false, "The reference shouldn't be 0 because it is still in autorelease pool.");
    }
    // printf("[star] deleting %p\n", this);
    delete this;
  }
}

Object* Object::autorelease() {
  AutoreleasePool::getInstance()->addObject(this);
  return this;
}

unsigned int Object::getReferenceCount() {
  return p_refCount;
}
