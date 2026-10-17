#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/singleton.h"
#include "mm_mtl/type_traits.h"
#include "types.h"
#include "ui/event/ui_event_data.h"

namespace fw {
struct UpdateInfo;
}

namespace ui {

class UIEventCondition;
class UIGameListener;
class UIObjectListener;

class UIEventManager : public mm::mtl::PtrSingleton<UIEventManager> {
public:
  struct EventInfo {
    EventInfo() : handle(0), delay(0.0f) {}

    u32 handle;
    f32 delay;
    EventData data;
  };

  struct ListenerInfo : public mm::mtl::IntrusiveListNode<ListenerInfo> {
    u32 handle;
    UIObjectListener *listener;
    UIEventCondition *conditions;
  };

  UIEventManager();
  virtual ~UIEventManager();
  void update(const fw::UpdateInfo &info);
  void pushObjectEvent(const EventInfo &event);
  bool stepEventInfo(EventInfo &event, f32 time);
  void registObjectListener(u32 handle, UIObjectListener *listener);
  void removeObjectListener(u32 handle);
  void addCondition(u32 handle, UIEventCondition *condition);
  void pushGameEvent(const EventInfo &event);
  void setGameListener(UIGameListener *listener);
  bool isObjectListenerFull();

  mm::mtl::IntrusiveList<ListenerInfo> listeners;
  mm::mtl::FixedVector<EventInfo, 256> objectEvents;
  UIGameListener *gameListener;
  mm::mtl::FixedVector<EventInfo, 256> gameEvents;
};

static_assert(sizeof(UIEventManager::EventInfo) == 0x20, "");
static_assert(offsetof(UIEventManager::ListenerInfo, handle) == 0x10, "");
static_assert(offsetof(UIEventManager::ListenerInfo, listener) == 0x18, "");
static_assert(offsetof(UIEventManager::ListenerInfo, conditions) == 0x20, "");
static_assert(sizeof(UIEventManager::ListenerInfo) == 0x28, "");
static_assert(offsetof(UIEventManager, listeners) == 0x08, "");
static_assert(offsetof(UIEventManager, objectEvents) == 0x20, "");
static_assert(offsetof(UIEventManager, gameListener) == 0x2028, "");
static_assert(offsetof(UIEventManager, gameEvents) == 0x2030, "");
static_assert(sizeof(UIEventManager) == 0x4038, "");

} // namespace ui

namespace mm {
namespace mtl {

template <> struct is_pod<ui::UIEventManager::EventInfo> {
  static const bool value = true;
};

} // namespace mtl
} // namespace mm
