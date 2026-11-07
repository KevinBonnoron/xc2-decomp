#pragma once
#include <stddef.h>

#include "gf/menu/call/gf_menu_call_manager.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/intrusive_list.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/input/ui_input_pointer.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"

namespace ui {
class IUIInputSelectionChecker;
class UIListInfoBase;
class UIStr;
} // namespace ui

namespace gf {

class GfMenuCallContext;

namespace GfMenuTypes {
struct Param;
} // namespace GfMenuTypes

class GfMenuObject : public mm::mtl::IntrusiveListNode<GfMenuObject> {
public:
  enum FLAG {
    FLAG_INITIALIZED = 1 << 0,
    FLAG_FINALIZED = 1 << 1,
  };

  GfMenuObject(u32 handle);
  virtual ~GfMenuObject();
  virtual void initialize();
  virtual void finalize();
  virtual void update();
  virtual void reloadParam();
  static void attachExternalCall(u32 call, u32 object);
  static void detachExternalCall(u32 call);
  static bool existAttachedObject(u32 call);
  static u32 getAttachedObject(u32 call);
  static u16 registString(const ui::UIStr &string);
  static void releaseString(u16 id);
  static const ui::UIStr &getString(u16 id);
  static void startCallContext(GfMenuCallContext *context, u32 menu, u32 object);
  static void nextCallContext(GfMenuCallContext *context, u32 menu);
  static void addResultCallContext(u32 handle, u32 type, int value);
  static void termCallContext(u32 handle);
  static void setCallContextEventHandler(GfMenuCallContext *context, u32 handler);
  static void setupInputSelection(u32 handle, int index, u32 size);
  static void resetInputSelection(u32 handle);
  static void setupInputSelectionFromList(u32 handle, const ui::UIListInfoBase &list);
  static void setInputSelectionChecker(u32 handle, ui::IUIInputSelectionChecker *checker);
  static void setupPadLineSelection(u32 handle, u32 line);
  static void setPadLineSelectionLoop(u32 handle, bool loop);
  static void setPadLoopSetting(u32 handle, bool loop);
  static void setupPointerSelection(u32 handle, const ui::UIInputPointer::SelectionSetup &setup);
  static void changePointerPos(u32 handle, const mm::Pnt<s16> &pos);
  static void changePointerPosFromObject(u32 handle, u32 object);
  static void changePointerRegionScale(u32 handle, f32 scale);
  static void changePointerRegionRect(u32 handle, const mm::Rect<s16> &rect);
  static void migrateInput(u32 handle, u32 target);
  static void enableInput(u32 handle);
  static void disableInput(u32 handle);
  static bool setFSInputObject(u32 layer, u32 object);
  static u32 getFSInputObject(u32 layer);
  static void enableFSInput(u32 layer);
  static void disableFSInput();
  static bool isActiveFSInput(u32 layer);
  static void setInputActionEnable(u32 handle, u32 action, bool enable);
  static void setInputSelectEnable(u32 handle, bool enable);
  static void sendEvent(u32 handle, const ui::EventData &event, f32 delay);
  static void sendOpenEvent(u32 handle, int type, f32 delay);
  static void sendCloseEvent(u32 handle, int type, f32 delay);
  static void sendEventToChild(u32 handle, const ui::EventData &event, const char *name, f32 delay);
  static void sendEventToParent(u32 handle, const ui::EventData &event, const char *name, f32 delay);
  static void sendEventToParent(u32 handle, const ui::EventData &event, f32 delay);
  static void addNumberEventCondition(u32 handle, const char *name, u32 event, u32 value, f32 time);
  static void addNumberEventCondition(u32 handle, const char *name, u32 event, u32 value);
  static void addDispEventCondition(u32 handle, const char *name, u32 event, u32 value, bool duplicated);
  static void addPosEventCondition(u32 handle, const char *name, u32 event, u32 value);
  static void hookCtrlEvent(u32 handle, int ctrl);
  static void hookAnimationEvent(u32 handle, u32 object);
  static void changeFSLayer(u32 handle, u16 layer, bool keep);
  static void returnFSLayer(u32 handle);
  static void closeFSLayer(u32 handle, bool fade, bool keep);
  static u32 getMenuLayerID(u32 id);
  static u32 getMenuIconID(u32 id);
  static bool getMenuText(u32 id, u8 *&bdat, u32 &textId);
  static bool getMenuDesc(u32 id, u8 *&bdat, u32 &textId);
  static void changeFSSubLayer(u32 handle, u16 group, u16 layer, bool keep);
  static void returnFSSubLayer(u32 handle, u16 group);
  static void returnFSSubLayer(GfMenuObject *object);
  static void registFSLayerObject(u32 layer, u32 object);
  static void setFSShadowLayer(u32 layer, bool shadow);
  static void registFSLayerParam(u32 layer, const GfMenuTypes::Param &param);
  static bool getFSLayerParam(u32 layer, GfMenuTypes::Param &param);
  static void removeFSLayerParam(u32 layer);
  static void enableFSSwitching();
  static void disableFSSwitching();
  static void overrideFadeOutTime(u32 frame);
  static void clearLayerStatck(u32 handle, u16 group);
  static void registTimer(u32 handle, u16 id, f32 time, bool repeat);
  static void releaseTimer(u32 handle);
  static void setTimerSpeedFactor(u32 handle, f32 speedFactor);
  static void setText(u32 handle, u16 id);
  static void setTextWithStyle(u32 handle, u16 id);
  virtual void eventHudSceneChange(u32 scene);

  u32 unknown18; // Inferred role: handle; original member name unknown.
  u32 unknown1c; // Inferred role: flags; original member name unknown.
  u32 unknown20; // Inferred role: layer; original member name unknown.
};

static_assert(offsetof(GfMenuObject, unknown18) == 0x18, "");
static_assert(offsetof(GfMenuObject, unknown1c) == 0x1c, "");
static_assert(offsetof(GfMenuObject, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObject) == 0x28, "");

// Inferred helper: requests an event with a parameter on a UI object after a delay; original name unknown.
inline void unknown140(u32 handle, u16 type, u32 param, f32 delay) {
  ui::EventData event;
  event.unknown08 = param;
  event.unknown0c = 0;
  event.unknown00 = type;
  ui::UIManager::get()->requestObjectEvent(handle, event, delay);
}

// Inferred helper: sends an event with two parameters to the object attached to a call; original name unknown.
inline void unknown141(u32 call, u16 type, u32 param0, u32 param1) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(call));
  if (acc.isValid()) {
    ui::EventData event;
    event.unknown00 = type;
    event.unknown08 = param0;
    event.unknown0c = param1;
    GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
  }
}

// Requests an event on the object attached to a call unless it is terminating, after the given assignments to the event
// (event_) have set its parameters; the callers use the wrappers below. Inferred macro names; macros leave no trace in the
// binary. Macros rather than inline functions: the game expands this block in every caller, and as a function its inline
// cost reaches Clang 3.9's threshold once ui::EventData has its 8-aligned 64-bit slot at 0x10.
#define GF_MENU_REQUEST_EVENT_WITH(call, type, assignments)                                                                                                                                            \
  do {                                                                                                                                                                                                 \
    u32 handle_ = ::gf::GfMenuObject::getAttachedObject(call);                                                                                                                                         \
    if (::ui::UIObjectAcc(handle_).isValid()) {                                                                                                                                                        \
      if (!::ui::UIObjectAcc(handle_).isTerm()) {                                                                                                                                                      \
        ::ui::EventData event_;                                                                                                                                                                        \
        event_.unknown00 = type;                                                                                                                                                                       \
        assignments ::ui::UIManager::get()->requestObjectEvent(handle_, event_, 0.0f);                                                                                                                 \
      }                                                                                                                                                                                                \
    }                                                                                                                                                                                                  \
  } while (0)

// The event with only its type, or with its first N parameters set (the others keep the constructor's zero).
#define GF_MENU_REQUEST_EVENT(call, type) GF_MENU_REQUEST_EVENT_WITH(call, type, )
#define GF_MENU_REQUEST_EVENT1(call, type, p0) GF_MENU_REQUEST_EVENT_WITH(call, type, event_.unknown08 = p0;)
#define GF_MENU_REQUEST_EVENT2(call, type, p0, p1) GF_MENU_REQUEST_EVENT_WITH(call, type, event_.unknown08 = p0; event_.unknown0c = p1;)
#define GF_MENU_REQUEST_EVENT3(call, type, p0, p1, p2) GF_MENU_REQUEST_EVENT_WITH(call, type, event_.unknown08 = p0; event_.unknown0c = p1; event_.unknown10 = p2;)
#define GF_MENU_REQUEST_EVENT4(call, type, p0, p1, p2, p3) GF_MENU_REQUEST_EVENT_WITH(call, type, event_.unknown08 = p0; event_.unknown0c = p1; event_.unknown10 = p2; event_.unknown14 = p3;)

// Inferred helper: sends an event to the object attached to a call unless it is terminating, true when sent; original name unknown.
inline bool unknown143(u32 call, u16 type) {
  u32 handle = GfMenuObject::getAttachedObject(call);
  if (ui::UIObjectAcc(handle).isValid()) {
    if (!ui::UIObjectAcc(handle).isTerm()) {
      ui::EventData event;
      event.unknown00 = type;
      GfMenuObject::sendEvent(handle, event, 0.0f);
      return true;
    }
  }
  return false;
}

// Inferred helper: sends an event to the object attached to a call; original name unknown.
inline void unknown144(u32 call, u16 type) { unknown141(call, type, 0, 0); }

// Inferred helper: sends an event with only its type to the object attached to a call (parameters left to the event's
// constructor, unlike unknown144); original name unknown.
inline void unknown155(u32 call, u16 type) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(call));
  if (acc.isValid()) {
    ui::EventData event;
    event.unknown00 = type;
    GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
  }
}

// Inferred helper: requests an event on the object attached to a call unless it is terminating; original name unknown.
inline void unknown145(u32 call, u16 type) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(call));
  if (acc.isValid() && !acc.isTerm()) {
    ui::EventData event;
    event.unknown00 = type;
    ui::UIManager::get()->requestObjectEvent(acc.unknown10, event, 0.0f);
  }
}

// Inferred helper: sends an event to the object attached to a call unless it is terminating; original name unknown.
inline void unknown146(u32 call, u16 type) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(call));
  if (acc.isValid() && !acc.isTerm()) {
    ui::EventData event;
    event.unknown00 = type;
    GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
  }
}

// Inferred helper: sends an event to a named child of the object attached to a call; original name unknown.
inline void unknown147(u32 call, const char *name, u16 type) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(call));
  if (acc.isValid()) {
    ui::EventData event;
    event.unknown00 = type;
    GfMenuObject::sendEvent(acc.searchChild(name), event, 0.0f);
  }
}

// Inferred helper: sends an event to a named child of the object attached to a call through an accessor; original name unknown.
inline void unknown148(u32 call, const char *name, u16 type) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(call));
  if (acc.isValid()) {
    ui::UIObjectAcc child(acc.searchChild(name));
    ui::EventData event;
    event.unknown00 = type;
    GfMenuObject::sendEvent(child.unknown10, event, 0.0f);
  }
}

// Inferred helper: sends an event with a parameter to the object attached to a call, parameter stored first; original name unknown.
inline void unknown149(u32 call, u16 type, u32 param) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(call));
  if (acc.isValid()) {
    ui::EventData event;
    event.unknown08 = param;
    event.unknown0c = 0;
    event.unknown00 = type;
    GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
  }
}

// Inferred helper: sends an event with a flag parameter to the object attached to a call; original name unknown.
inline void unknown150(u32 call, u16 type, bool param) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(call));
  if (acc.isValid()) {
    ui::EventData event;
    event.unknown00 = type;
    event.unknown08 = param;
    event.unknown0c = 0;
    GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
  }
}

// Inferred helper: sends an event with a 16-bit parameter to the object attached to a call; original name unknown.
inline void unknown156(u32 call, u16 type, u16 param) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(call));
  if (acc.isValid()) {
    ui::EventData event;
    event.unknown0c = 0;
    event.unknown00 = type;
    event.unknown08_u16 = param;
    event.unknown0a = 0;
    GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
  }
}

// Inferred helper: sends an event with its first parameter to the object attached to a call (second parameter left to the
// event's constructor, unlike unknown141); original name unknown.
inline void unknown157(u32 call, u16 type, u32 param) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(call));
  if (acc.isValid()) {
    ui::EventData event;
    event.unknown00 = type;
    event.unknown08 = param;
    GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
  }
}

// Inferred helper: requests an event with its first parameter on a UI object after a delay (second parameter left to the
// event's constructor, unlike unknown140); original name unknown.
inline void unknown158(u32 handle, u16 type, u32 param, f32 delay) {
  ui::EventData event;
  event.unknown00 = type;
  event.unknown08 = param;
  ui::UIManager::get()->requestObjectEvent(handle, event, delay);
}

// Inferred helper: requests an event with a parameter on the object attached to a call unless it is terminating; original name unknown.
inline void unknown159(u32 call, u16 type, u32 param) {
  u32 handle = GfMenuObject::getAttachedObject(call);
  if (ui::UIObjectAcc(handle).isValid()) {
    if (!ui::UIObjectAcc(handle).isTerm()) {
      unknown140(handle, type, param, 0.0f);
    }
  }
}

// Inferred helper: starts a call context on the object attached to a call, true when the object exists; original name unknown.
inline bool unknown151(GfMenuCallContext *context, u32 call) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(call));
  if (acc.isValid()) {
    GfMenuObject::startCallContext(context, call, acc.unknown10);
    return true;
  }
  return false;
}

// Inferred helper: starts a call context on the object attached to a call unless it is terminating; original name unknown.
inline void unknown152(GfMenuCallContext *context, u32 call) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(call));
  if (acc.isValid() && !acc.isTerm()) {
    GfMenuObject::startCallContext(context, call, acc.unknown10);
  }
}

// Inferred helper: starts a call context on the object attached to a call when the call can start, true when started; original name unknown.
inline bool unknown153(GfMenuCallContext *context, u32 call) {
  if (GfMenuObjUtil::checkCCStart(context) && GfMenuCallManager::get()->canCall(call)) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(call));
    if (acc.isValid()) {
      GfMenuObject::startCallContext(context, call, acc.unknown10);
      return true;
    }
  }
  return false;
}

// Inferred helper: shows or hides the object attached to a call unless it is terminating; original name unknown.
static inline void unknown154(u32 call, bool isDisp) {
  u32 handle = GfMenuObject::getAttachedObject(call);
  if (ui::UIObjectAcc(handle).isValid()) {
    if (!ui::UIObjectAcc(handle).isTerm()) {
      ui::UIObjectAcc(handle).setDisp(isDisp);
    }
  }
}

} // namespace gf
