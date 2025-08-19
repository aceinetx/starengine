#pragma once

namespace star {
class ApplicationProtocol {
public:
	/**
	 * What to do when the app finishes launching?
	 */
	virtual bool applicationDidFinishLaunching() = 0;
};
} // namespace star
