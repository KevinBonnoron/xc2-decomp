#pragma once
#include <stddef.h>

#include "framework/pointer_map.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace ui {

class UITimer;

class UITimerManager : public mm::mtl::PtrSingleton<UITimerManager> {
public:
  struct TimerInfo : public mm::mtl::IntrusiveListNode<TimerInfo> {
    u32 unknown10;  // Inferred role: timer; original member name unknown.
    u32 unknown14;  // Inferred role: object; original member name unknown.
    u16 unknown18;  // Inferred role: id; original member name unknown.
    u16 unknown1a;  // Inferred role: count; original member name unknown.
    bool unknown1c; // Inferred role: suspended; original member name unknown.
    bool unknown1d; // Inferred role: repeat; original member name unknown.
  };

  UITimerManager();
  virtual ~UITimerManager();
  UITimer *getTimer(u32 timer) const;
  void update(const fw::UpdateInfo &info);
  void suspend();
  void resume();
  u32 registTimer(u32 object, u16 id, u64 time, bool repeat);
  void releaseTimer(u32 timer);
  void setTimerSpeedFactor(u32 timer, f32 speedFactor);
  u32 getTimerHandle(u32 object);
  void setRepeatTimer(u32 timer, bool repeat);
  TimerInfo *getTimerInfo(u32 timer);
  void suspendTimer(u32 timer);
  void resumeTimer(u32 timer);
  bool isValidTimer(u32 timer);

  fw::PointerMap unknown08;                    // Inferred role: timer map; original member name unknown.
  mm::mtl::IntrusiveList<TimerInfo> unknown40; // Inferred role: timers; original member name unknown.
  bool unknown58;                              // Inferred role: suspended; original member name unknown.
};

static_assert(offsetof(UITimerManager::TimerInfo, unknown10) == 0x10, "");
static_assert(offsetof(UITimerManager::TimerInfo, unknown1d) == 0x1d, "");
static_assert(sizeof(UITimerManager::TimerInfo) == 0x20, "");
static_assert(offsetof(UITimerManager, unknown08) == 0x08, "");
static_assert(offsetof(UITimerManager, unknown40) == 0x40, "");
static_assert(offsetof(UITimerManager, unknown58) == 0x58, "");
static_assert(sizeof(UITimerManager) == 0x60, "");

} // namespace ui
