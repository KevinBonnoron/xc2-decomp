#pragma once
#include "ai/ai_state.h"

namespace gf {

class GfMenuFieldSkill {
public:
  class StateIdle : public ai::State {
  public:
    static ai::State *create(void *buffer);
    const char *getName() const override;
    void onEnter(void *owner, ai::State *previous) override;
    void onLeave(void *owner, ai::State *next) override;
    void onStep(void *owner, const void *param) override;
  };

  static bool isRunning();
};

} // namespace gf
