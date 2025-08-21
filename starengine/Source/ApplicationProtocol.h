#pragma once

namespace star {
/** ApplicationProtocol
 *
 * Bare minimum of what the application needs to implement
 */
class ApplicationProtocol {
public:
  /**
   * What to do when the app finishes launching?
   */
  virtual bool applicationDidFinishLaunching() = 0;

  /**
   * Run the application
   *
   * Calls applicationDidFinishLaunching, runs the main loop, and releases everything at the end
   */
  virtual int run() = 0;
};
} // namespace star
