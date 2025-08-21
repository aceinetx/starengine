#pragma once
#include "Action.h"

namespace star {
class ActionEase : public Action {
protected:
  Action* p_inner;

public:
  ~ActionEase();

  virtual Action* getInnerAction();

  virtual void startWithTarget(Node* target) override;
  virtual void update(float time) override;
};

#define DECLARE_EASING_CLASS(name)                                                                 \
  class name : public ActionEase {                                                                 \
  public:                                                                                          \
    static name* create(Action* inner);                                                            \
    virtual void update(float dt);                                                                 \
  };

DECLARE_EASING_CLASS(BackInOut);

} // namespace star
