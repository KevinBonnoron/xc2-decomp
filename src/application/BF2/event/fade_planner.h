#pragma once
#include "event/fade_ctrl.h"
#include "mm_math/mm_col4.h"
#include "types.h"

namespace event {

class FadePlanner {
public:
  enum TYPE {
    TYPE_UNKNOWN_0, // Inferred role: op fade out; original name unknown.
    TYPE_UNKNOWN_1, // Inferred role: op fade in; original name unknown.
    TYPE_UNKNOWN_2, // Inferred role: ed fade out; original name unknown.
    TYPE_UNKNOWN_3, // Inferred role: ed fade in; original name unknown.
    TYPE_COUNT,
  };

  struct Plan {
    enum {
      FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: enable flag; original name unknown.
      FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: request flag; original name unknown.
      FLAG_UNKNOWN_2 = 1 << 2, // Inferred role: wait flag; original name unknown.
    };

    Plan() { clear(); }
    void clear() {
      unknown00 = 0;
      unknown04 = 0;
      unknown08 = 0;
      unknown0c = FadeCtrl::PRIO_LOW;
      unknown10 = mm::Col4::black;
      unknown20 = 0.0f;
    }

    u32 unknown00;            // Inferred role: flags; original member name unknown.
    u32 unknown04;            // Inferred role: frame; original member name unknown.
    u32 unknown08;            // Inferred role: wait; original member name unknown.
    FadeCtrl::PRIO unknown0c; // Inferred role: prio; original member name unknown.
    mm::Col4 unknown10;       // Inferred role: color; original member name unknown.
    f32 unknown20;            // Inferred role: wait timer; original member name unknown.
  };

  FadePlanner();
  virtual ~FadePlanner() {}
  void clear();
  void update(f32 delta);
  void play(TYPE type);
  void plan(TYPE type, bool isEnable, u32 frame, u32 wait, FadeCtrl::PRIO prio, const mm::Col4 &color);
  void request(TYPE type);

private:
  u32 unknown08;              // Inferred role: flags; original member name unknown.
  Plan unknown0c[TYPE_COUNT]; // Inferred role: plans; original member name unknown.
};

static_assert(sizeof(FadePlanner) == 0xa0, "");

} // namespace event
