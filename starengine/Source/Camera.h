#pragma once
#include "Macros.h"
#include "Node.h"
#include <raylib.h>

using rlCamera = Camera2D;

namespace star {
/** Camera
 *
 * Controls how the player sees the world
 */
class Camera : public Node {
protected:
	float p_zoom;

public:
	virtual bool init() override;

	/**
	 * Create a raylib's Camera2D with the properties of the current camera converted to it
	 */
	virtual rlCamera getRaylibCamera();

	/**
	 * Get camera zoom
	 */
	virtual float getZoom();

	/**
	 * Set camera zoom
	 */
	virtual void setZoom(float zoom);

	/**
	 * In Node, it returns the content size, here it returns the screen size
	 */
	Vec2 getContentSize() override;

	CREATE_FUNC(Camera);
};
} // namespace star
