#include "ui/timer/ui_timer_manager.h"

#include "framework/memory/framework_memory.h"
#include "ui/timer/ui_timer.h"
#include "ui/ui_util.h"

namespace ui {

UITimerManager::UITimerManager() : suspended(false) { timerMap.reserve(UIUtil::getProgAllocator(), 64); }

UITimer *UITimerManager::getTimer(u32 timer) const { return static_cast<UITimer *>(timerMap.getPtr(timer)); }

void UITimerManager::suspend() { suspended = true; }

void UITimerManager::resume() { suspended = false; }

u32 UITimerManager::registTimer(u32 object, u16 id, u64 time, bool repeat) {
// __LINE__ is the line argument of the operator new calls.
#line 172
  UITimer *timer = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UITimer();
  if (timer == nullptr) {
    return 0;
  }

#line 177
  TimerInfo *info = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) TimerInfo;
  if (info == nullptr) {
    delete timer;
    timer = nullptr;
  }

  u32 handle = timerMap.regist(timer);
  if (handle == 0) {
    delete timer;
    return 0;
  }

  timer->start(time);
  info->timer = handle;
  info->object = object;
  info->id = id;
  info->count = 0;
  info->repeat = repeat;
  info->suspended = false;
  timers.push_back(info);
  return handle;
}

void UITimerManager::releaseTimer(u32 timer) {
  if (timer == 0) {
    return;
  }

  for (mm::mtl::IntrusiveList<TimerInfo>::iterator it = timers.begin(); it != timers.end(); ++it) {
    TimerInfo *info = it.get();
    if (info->timer == timer) {
      UITimer *ptr = getTimer(timer);
      timerMap.remove(info->timer);
      delete ptr;
      timers.erase(it);
      delete info;
      return;
    }
  }
}

void UITimerManager::setTimerSpeedFactor(u32 timer, f32 speedFactor) {
  if (timer == 0) {
    return;
  }

  for (mm::mtl::IntrusiveList<TimerInfo>::iterator it = timers.begin(); it != timers.end(); ++it) {
    if (it.get()->timer == timer) {
      getTimer(timer)->speedFactor = speedFactor;
    }
  }
}

u32 UITimerManager::getTimerHandle(u32 object) {
  if (object == 0) {
    return 0;
  }

  for (mm::mtl::IntrusiveList<TimerInfo>::iterator it = timers.begin(); it != timers.end(); ++it) {
    if (it->object == object) {
      return it->timer;
    }
  }
  return 0;
}

void UITimerManager::setRepeatTimer(u32 timer, bool repeat) {
  TimerInfo *info = getTimerInfo(timer);
  if (info != nullptr) {
    info->repeat = repeat;
  }
}

UITimerManager::TimerInfo *UITimerManager::getTimerInfo(u32 timer) {
  if (getTimer(timer) == nullptr) {
    return nullptr;
  }

  for (mm::mtl::IntrusiveList<TimerInfo>::iterator it = timers.begin(); it != timers.end(); ++it) {
    if (it->timer == timer) {
      return it.get();
    }
  }
  return nullptr;
}

void UITimerManager::suspendTimer(u32 timer) {
  TimerInfo *info = getTimerInfo(timer);
  if (info != nullptr) {
    info->suspended = true;
  }
}

void UITimerManager::resumeTimer(u32 timer) {
  TimerInfo *info = getTimerInfo(timer);
  if (info != nullptr) {
    info->suspended = false;
  }
}

bool UITimerManager::isValidTimer(u32 timer) { return getTimer(timer) != nullptr; }

} // namespace ui
