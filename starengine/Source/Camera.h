#pragma once
#include "Macros.h"
#include "Node.h"
#include <raylib.h>

using rlCamera = Camera2D;

namespace star {
class Camera : public Node {
public:
	virtual rlCamera getRaylibCamera();

	CREATE_FUNC(Camera);
};
} // namespace star
