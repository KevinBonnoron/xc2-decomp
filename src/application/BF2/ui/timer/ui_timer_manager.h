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
    u32 timer;
    u32 object;
    u16 id;
    u16 count;
    bool suspended;
    bool repeat;
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

  fw::PointerMap timerMap;
  mm::mtl::IntrusiveList<TimerInfo> timers;
  bool suspended;
};

static_assert(offsetof(UITimerManager::TimerInfo, timer) == 0x10, "");
static_assert(offsetof(UITimerManager::TimerInfo, repeat) == 0x1d, "");
static_assert(sizeof(UITimerManager::TimerInfo) == 0x20, "");
static_assert(offsetof(UITimerManager, timerMap) == 0x08, "");
static_assert(offsetof(UITimerManager, timers) == 0x40, "");
static_assert(offsetof(UITimerManager, suspended) == 0x58, "");
static_assert(sizeof(UITimerManager) == 0x60, "");

} // namespace ui
