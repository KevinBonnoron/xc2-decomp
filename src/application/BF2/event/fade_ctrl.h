#pragma once
#include "event/fade_updater.h"
#include "mm_mtl/noncopyable.h"
#include "types.h"

namespace mm {
struct Col4;
} // namespace mm

namespace event {

class FadeCtrl : public mm::mtl::NoncopyableBase {
public:
  enum PRIO {
    PRIO_LOW,
    PRIO_MIDDLE,
    PRIO_HIGH,
    PRIO_COUNT,
  };

  enum {
    FLAG_EVENT_SKIP = 1 << 0,
  };

  FadeCtrl();
  virtual ~FadeCtrl() {}
  bool isFading() const {
    for (u32 i = 0; i < PRIO_COUNT; i++) {
      if (mUpdaters[i].isFading()) {
        return true;
      }
    }
    return false;
  }
  bool isFading(PRIO prio) const { return mUpdaters[prio].isFading(); }
  void clear();
  void update();
  void fadeout(int frame, PRIO prio, const mm::Col4 *color);
  void fadein(int frame);
  void fadeoutEventSkip(int frame);
  void fadeinEventSkip(int frame);

private:
  FadeUpdater mUpdaters[PRIO_COUNT];
  u32 flags;
};

static_assert(sizeof(FadeCtrl) == 0x70, "");

} // namespace event
