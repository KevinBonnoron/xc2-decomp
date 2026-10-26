#include "ui/event/ui_event_manager.h"

#include "framework/memory/framework_memory.h"
#include "fw/fw_update_info.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/reference_object.h"
#include "ui/event/ui_event_condition.h"
#include "ui/event/ui_object_listener.h"
#include "ui/ui_object.h"
#include "ui/ui_object_base.h"
#include "ui/ui_util.h"

namespace ui {

// Inferred role: releases a listener entry's listener and condition chain; original name unknown.
static inline void unknown001(UIEventManager::ListenerInfo *info) {
  mm::mtl::safeRelease(info->unknown18);
  UIEventCondition *condition = info->unknown20;
  while (condition != nullptr) {
    UIEventCondition *next = condition->unknown18;
    condition->release();
    condition = next;
  }
}

UIEventManager::UIEventManager() : m_gameListener(nullptr) {}

UIEventManager::~UIEventManager() {
  m_gameListener = nullptr;
  for (mm::mtl::IntrusiveList<ListenerInfo>::iterator it = unknown08.begin(); it != unknown08.end();) {
    ListenerInfo *info = it.get();
    unknown001(info);
    it = unknown08.erase(it);
    delete info;
  }
  for (mm::mtl::IntrusiveList<ListenerInfo>::iterator it = unknown08.begin(); it != unknown08.end();) {
    it = unknown08.erase(it);
  }
  unknown20.clear();
  unknown2030.clear();
}

void UIEventManager::update(const fw::UpdateInfo &info) {
  if (unknown08.size() != 0) {
    for (mm::mtl::IntrusiveList<ListenerInfo>::iterator it = unknown08.begin(); it != unknown08.end(); ++it) {
      for (UIEventCondition *condition = it->unknown20; condition != nullptr; condition = condition->unknown18) {
        int result = condition->update();
        if (result != 0) {
          EventInfo event;
          event.unknown00 = it->unknown10;
          event.unknown08.unknown00 = 13;
          event.unknown08.unknown08 = result;
          event.unknown08.unknown0c = condition->unknown0c;
          event.unknown08.unknown10 = condition->unknown10;
          event.unknown08.unknown14 = condition->getArg();
          unknown20.push_back(event);
        }
      }
    }

    if (!unknown20.empty()) {
      for (EventInfo *event = unknown20.begin(); event != unknown20.end();) {
        if (stepEventInfo(*event, info.unknown04)) {
          for (mm::mtl::IntrusiveList<ListenerInfo>::iterator it = unknown08.begin(); it != unknown08.end(); ++it) {
            u32 handle = event->unknown00;
            if (handle != it->unknown10) {
              continue;
            }
            if (!UIUtil::isTerm(handle)) {
              it->unknown18->reciveEvent(event->unknown08, event->unknown00);
            }
            break;
          }
          event = unknown20.erase(event);
        } else {
          ++event;
        }
      }
    }
  }

  if (m_gameListener != nullptr && !unknown2030.empty()) {
    for (EventInfo *event = unknown2030.begin(); event != unknown2030.end();) {
      if (stepEventInfo(*event, info.unknown04)) {
        m_gameListener->reciveEvent(event->unknown08, event->unknown00);
        event = unknown2030.erase(event);
      } else {
        ++event;
      }
    }
  }
}

void UIEventManager::pushObjectEvent(const EventInfo &event) { unknown20.push_back(event); }

bool UIEventManager::stepEventInfo(EventInfo &event, f32 time) {
  if (event.unknown04 == 0.0f) {
    return true;
  }

  f32 delay = event.unknown04 - time;
  event.unknown04 = delay < 0.0f ? 0.0f : delay;
  return false;
}

void UIEventManager::registObjectListener(u32 handle, UIObjectListener *listener) {
  if (!UIUtil::isValid(handle)) {
    return;
  }

  for (mm::mtl::IntrusiveList<ListenerInfo>::iterator it = unknown08.begin(); it != unknown08.end(); ++it) {
    if (it->unknown10 == handle) {
      return;
    }
  }

  listener->addRef();
// __LINE__ is the line argument of the operator new call.
#line 198
  ListenerInfo *info = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) ListenerInfo;
  info->unknown10 = handle;
  info->unknown18 = listener;
  info->unknown20 = nullptr;
  unknown08.push_back(info);
  UIUtil::getObject(handle)->unknown98.set(UI_OBJECT_FLAG_LISTENER);

  EventInfo event;
  event.unknown00 = handle;
  event.unknown08.unknown00 = 1;
  event.unknown08.unknown08 = 0;
  event.unknown08.unknown0c = 0;
  event.unknown08.unknown10 = 0;
  event.unknown08.unknown14 = 0;
  UIEventManager::get()->pushObjectEvent(event);
}

void UIEventManager::removeObjectListener(u32 handle) {
  if (!UIUtil::isValid(handle)) {
    return;
  }

  for (mm::mtl::IntrusiveList<ListenerInfo>::iterator it = unknown08.begin(); it != unknown08.end(); ++it) {
    ListenerInfo *info = it.get();
    if (info->unknown10 == handle) {
      unknown001(info);
      UIUtil::getObject(handle)->unknown98.set(UI_OBJECT_FLAG_LISTENER, false);
      unknown08.erase(it);
      operator delete(info);
      return;
    }
  }
}

void UIEventManager::addCondition(u32 handle, UIEventCondition *condition) {
  if (!UIUtil::isValid(handle)) {
    return;
  }

  for (mm::mtl::IntrusiveList<ListenerInfo>::iterator it = unknown08.begin(); it != unknown08.end(); ++it) {
    if (it->unknown10 == handle) {
      condition->addRef();
      condition->unknown18 = it->unknown20;
      it->unknown20 = condition;
    }
  }
}

void UIEventManager::pushGameEvent(const EventInfo &event) {
  if (m_gameListener != nullptr) {
    unknown2030.push_back(event);
  }
}

void UIEventManager::setGameListener(UIGameListener *listener) { m_gameListener = listener; }

bool UIEventManager::isObjectListenerFull() { return false; }

} // namespace ui
