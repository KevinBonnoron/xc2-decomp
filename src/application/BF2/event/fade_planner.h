#pragma once
#include "event/fade_ctrl.h"
#include "mm_math/mm_col4.h"
#include "types.h"

namespace event {

class FadePlanner {
public:
  enum TYPE {
    TYPE_OP_FADE_OUT,
    TYPE_OP_FADE_IN,
    TYPE_ED_FADE_OUT,
    TYPE_ED_FADE_IN,
    TYPE_COUNT,
  };

  struct Plan {
    enum {
      FLAG_ENABLE = 1 << 0,
      FLAG_REQUEST = 1 << 1,
      FLAG_WAIT = 1 << 2,
    };

    Plan() { clear(); }
    void clear() {
      flags = 0;
      frame = 0;
      wait = 0;
      prio = FadeCtrl::PRIO_LOW;
      color = mm::Col4::black;
      waitTimer = 0.0f;
    }

    u32 flags;
    u32 frame;
    u32 wait;
    FadeCtrl::PRIO prio;
    mm::Col4 color;
    f32 waitTimer;
  };

  FadePlanner();
  virtual ~FadePlanner() {}
  void clear();
  void update(f32 delta);
  void play(TYPE type);
  void plan(TYPE type, bool isEnable, u32 frame, u32 wait, FadeCtrl::PRIO prio, const mm::Col4 &color);
  void request(TYPE type);

private:
  u32 flags;
  Plan mPlans[TYPE_COUNT];
};

static_assert(sizeof(FadePlanner) == 0xa0, "");

} // namespace event
