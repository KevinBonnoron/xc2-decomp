#include "ui/timer/ui_timer_manager.h"

#include "framework/memory/framework_memory.h"
#include "ui/timer/ui_timer.h"
#include "ui/ui_util.h"

namespace ui {

UITimerManager::UITimerManager() : unknown58(false) { unknown08.reserve(UIUtil::getProgAllocator(), 64); }

UITimer *UITimerManager::getTimer(u32 timer) const { return static_cast<UITimer *>(unknown08.getPtr(timer)); }

void UITimerManager::suspend() { unknown58 = true; }

void UITimerManager::resume() { unknown58 = false; }

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

  u32 handle = unknown08.regist(timer);
  if (handle == 0) {
    delete timer;
    return 0;
  }

  timer->start(time);
  info->unknown10 = handle;
  info->unknown14 = object;
  info->unknown18 = id;
  info->unknown1a = 0;
  info->unknown1d = repeat;
  info->unknown1c = false;
  unknown40.push_back(info);
  return handle;
}

void UITimerManager::releaseTimer(u32 timer) {
  if (timer == 0) {
    return;
  }

  for (mm::mtl::IntrusiveList<TimerInfo>::iterator it = unknown40.begin(); it != unknown40.end(); ++it) {
    TimerInfo *info = it.get();
    if (info->unknown10 == timer) {
      UITimer *ptr = getTimer(timer);
      unknown08.remove(info->unknown10);
      delete ptr;
      unknown40.erase(it);
      delete info;
      return;
    }
  }
}

void UITimerManager::setTimerSpeedFactor(u32 timer, f32 speedFactor) {
  if (timer == 0) {
    return;
  }

  for (mm::mtl::IntrusiveList<TimerInfo>::iterator it = unknown40.begin(); it != unknown40.end(); ++it) {
    if (it.get()->unknown10 == timer) {
      getTimer(timer)->unknown18 = speedFactor;
    }
  }
}

u32 UITimerManager::getTimerHandle(u32 object) {
  if (object == 0) {
    return 0;
  }

  for (mm::mtl::IntrusiveList<TimerInfo>::iterator it = unknown40.begin(); it != unknown40.end(); ++it) {
    if (it->unknown14 == object) {
      return it->unknown10;
    }
  }
  return 0;
}

void UITimerManager::setRepeatTimer(u32 timer, bool repeat) {
  TimerInfo *info = getTimerInfo(timer);
  if (info != nullptr) {
    info->unknown1d = repeat;
  }
}

UITimerManager::TimerInfo *UITimerManager::getTimerInfo(u32 timer) {
  if (getTimer(timer) == nullptr) {
    return nullptr;
  }

  for (mm::mtl::IntrusiveList<TimerInfo>::iterator it = unknown40.begin(); it != unknown40.end(); ++it) {
    if (it->unknown10 == timer) {
      return it.get();
    }
  }
  return nullptr;
}

void UITimerManager::suspendTimer(u32 timer) {
  TimerInfo *info = getTimerInfo(timer);
  if (info != nullptr) {
    info->unknown1c = true;
  }
}

void UITimerManager::resumeTimer(u32 timer) {
  TimerInfo *info = getTimerInfo(timer);
  if (info != nullptr) {
    info->unknown1c = false;
  }
}

bool UITimerManager::isValidTimer(u32 timer) { return getTimer(timer) != nullptr; }

} // namespace ui
