#pragma once
#include <stddef.h>

#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/reference_object.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace ui {

struct EventData;

union uiEventParam {
  s32 valueS32;
  u32 valueU32;
  f32 valueF32;
};

class UICtrlObject : public mm::mtl::ReferenceObject, public mm::mtl::IntrusiveListNode<UICtrlObject> {
public:
  UICtrlObject(u32 object);
  virtual ~UICtrlObject();
  virtual void update(const fw::UpdateInfo &info) = 0;
  bool isTerm();
  void setupEventHanding(u32 handler, u16 id);
  static u16 getEventCtrlObjID(const EventData &event);
  static u16 getEventType(const EventData &event);
  static void getEventParam(const EventData &event, u32 index, uiEventParam &param);
  void sendEvent(u16 type, const uiEventParam *param0, const uiEventParam *param1, const uiEventParam *param2);

  u32 object;
  u32 eventHandler;
  u16 id;
};

static_assert(offsetof(UICtrlObject, object) == 0x20, "");
static_assert(offsetof(UICtrlObject, eventHandler) == 0x24, "");
static_assert(offsetof(UICtrlObject, id) == 0x28, "");

} // namespace ui
