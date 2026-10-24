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
    EventInfo() : unknown00(0), unknown04(0.0f) {}

    u32 unknown00;       // Inferred role: handle; original member name unknown.
    f32 unknown04;       // Inferred role: delay; original member name unknown.
    EventData unknown08; // Inferred role: data; original member name unknown.
  };

  struct ListenerInfo : public mm::mtl::IntrusiveListNode<ListenerInfo> {
    u32 unknown10;               // Inferred role: handle; original member name unknown.
    UIObjectListener *unknown18; // Inferred role: listener; original member name unknown.
    UIEventCondition *unknown20; // Inferred role: conditions; original member name unknown.
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

  mm::mtl::IntrusiveList<ListenerInfo> unknown08; // Inferred role: listeners; original member name unknown.
  mm::mtl::FixedVector<EventInfo, 256> unknown20; // Inferred role: object events; original member name unknown.
  UIGameListener *m_gameListener;
  mm::mtl::FixedVector<EventInfo, 256> unknown2030; // Inferred role: game events; original member name unknown.
};

static_assert(sizeof(UIEventManager::EventInfo) == 0x20, "");
static_assert(offsetof(UIEventManager::ListenerInfo, unknown10) == 0x10, "");
static_assert(offsetof(UIEventManager::ListenerInfo, unknown18) == 0x18, "");
static_assert(offsetof(UIEventManager::ListenerInfo, unknown20) == 0x20, "");
static_assert(sizeof(UIEventManager::ListenerInfo) == 0x28, "");
static_assert(offsetof(UIEventManager, unknown08) == 0x08, "");
static_assert(offsetof(UIEventManager, unknown20) == 0x20, "");
static_assert(offsetof(UIEventManager, m_gameListener) == 0x2028, "");
static_assert(offsetof(UIEventManager, unknown2030) == 0x2030, "");
static_assert(sizeof(UIEventManager) == 0x4038, "");

} // namespace ui

namespace mm {
namespace mtl {

template <> struct is_pod<ui::UIEventManager::EventInfo> {
  static const bool value = true;
};

} // namespace mtl
} // namespace mm
