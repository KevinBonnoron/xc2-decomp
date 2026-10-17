#include "ui/event/ui_event_manager.h"

#include "framework/memory/framework_memory.h"
#include "fw/fw_update_info.h"
#include "mm_mtl/bitflag.h"
#include "ui/event/ui_event_condition.h"
#include "ui/event/ui_object_listener.h"
#include "ui/ui_object.h"
#include "ui/ui_object_base.h"
#include "ui/ui_util.h"

namespace ui {

UIEventManager::UIEventManager() : gameListener(nullptr) {}

void UIEventManager::update(const fw::UpdateInfo &info) {
  if (listeners.size() != 0) {
    for (mm::mtl::IntrusiveList<ListenerInfo>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
      for (UIEventCondition *condition = it->conditions; condition != nullptr; condition = condition->next) {
        int result = condition->update();
        if (result != 0) {
          EventInfo event;
          event.handle = it->handle;
          event.data.type = 13;
          event.data.param0 = result;
          event.data.param1 = condition->event;
          event.data.param2 = condition->value;
          event.data.param3 = condition->getArg();
          objectEvents.push_back(event);
        }
      }
    }

    if (!objectEvents.empty()) {
      for (EventInfo *event = objectEvents.begin(); event != objectEvents.end();) {
        if (stepEventInfo(*event, info.deltaTime)) {
          for (mm::mtl::IntrusiveList<ListenerInfo>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
            u32 handle = event->handle;
            if (handle != it->handle) {
              continue;
            }
            if (!UIUtil::isTerm(handle)) {
              it->listener->reciveEvent(event->data, event->handle);
            }
            break;
          }
          event = objectEvents.erase(event);
        } else {
          ++event;
        }
      }
    }
  }

  if (gameListener != nullptr && !gameEvents.empty()) {
    for (EventInfo *event = gameEvents.begin(); event != gameEvents.end();) {
      if (stepEventInfo(*event, info.deltaTime)) {
        gameListener->reciveEvent(event->data, event->handle);
        event = gameEvents.erase(event);
      } else {
        ++event;
      }
    }
  }
}

void UIEventManager::pushObjectEvent(const EventInfo &event) { objectEvents.push_back(event); }

bool UIEventManager::stepEventInfo(EventInfo &event, f32 time) {
  if (event.delay == 0.0f) {
    return true;
  }

  f32 delay = event.delay - time;
  event.delay = delay < 0.0f ? 0.0f : delay;
  return false;
}

void UIEventManager::registObjectListener(u32 handle, UIObjectListener *listener) {
  if (!UIUtil::isValid(handle)) {
    return;
  }

  for (mm::mtl::IntrusiveList<ListenerInfo>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
    if (it->handle == handle) {
      return;
    }
  }

  listener->addRef();
// __LINE__ is the line argument of the operator new call.
#line 198
  ListenerInfo *info = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) ListenerInfo;
  info->handle = handle;
  info->listener = listener;
  info->conditions = nullptr;
  listeners.push_back(info);
  UIUtil::getObject(handle)->flags.set(UI_OBJECT_FLAG_LISTENER);

  EventInfo event;
  event.handle = handle;
  event.data.type = 1;
  event.data.param0 = 0;
  event.data.param1 = 0;
  event.data.param2 = 0;
  event.data.param3 = 0;
  UIEventManager::get()->pushObjectEvent(event);
}

void UIEventManager::addCondition(u32 handle, UIEventCondition *condition) {
  if (!UIUtil::isValid(handle)) {
    return;
  }

  for (mm::mtl::IntrusiveList<ListenerInfo>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
    if (it->handle == handle) {
      condition->addRef();
      condition->next = it->conditions;
      it->conditions = condition;
    }
  }
}

void UIEventManager::pushGameEvent(const EventInfo &event) {
  if (gameListener != nullptr) {
    gameEvents.push_back(event);
  }
}

void UIEventManager::setGameListener(UIGameListener *listener) { gameListener = listener; }

bool UIEventManager::isObjectListenerFull() { return false; }

} // namespace ui
