#pragma once
#include <stddef.h>

#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/intrusive_list.h"
#include "types.h"
#include "ui/input/ui_input_pointer.h"

namespace ui {
class IUIInputSelectionChecker;
class UIListInfoBase;
class UIStr;
struct EventData;
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

  u32 handle;
  u32 flags;
  u32 layer;
};

static_assert(offsetof(GfMenuObject, handle) == 0x18, "");
static_assert(offsetof(GfMenuObject, flags) == 0x1c, "");
static_assert(offsetof(GfMenuObject, layer) == 0x20, "");
static_assert(sizeof(GfMenuObject) == 0x28, "");

} // namespace gf
