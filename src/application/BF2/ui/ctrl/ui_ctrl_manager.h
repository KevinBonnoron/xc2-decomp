#pragma once
#include <stddef.h>

#include "mm_mtl/bitflag.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include "ui/ctrl/ui_ctrl.h"
#include "ui/ctrl/ui_ctrl_curve.h"
#include "ui/ctrl/ui_ctrl_method.h"
#include "ui/ui_displayinfo.h"
#include "ui/ui_transform.h"

namespace fw {
struct UpdateInfo;
}

namespace mm {
struct Col3;
}

namespace ui {

class UICtrlObject;
class UIObject;

class IUICtrlUpdater : public mm::mtl::IntrusiveListNodeBase {
public:
  virtual bool updateCtrl(const fw::UpdateInfo &info) = 0;
};

class UICtrlManager : public mm::mtl::PtrSingleton<UICtrlManager> {
public:
  static const u32 CTRL_SLOT_MAX = 128;

  enum CtrlFlag {
    CTRL_FLAG_CONTROL = 0,
    CTRL_FLAG_TERM = 1,
    CTRL_FLAG_HIDE = 2,
    CTRL_FLAG_RESTORE = 3,
  };

  struct CtrlSlot {
    UICtrlMethodPos pos;
    UICtrlMethodScale scale;
    UICtrlMethodAlpha alpha;
    UICtrlMethodBright bright;
    UICtrlMethodRot rot;
    UICtrlMethodMulColor mulColor;
    UICtrlMethodAddColor addColor;
    UICtrlMethodMotion motion;
    UICtrl ctrl;
    UICtrl::MethodList methods;
    f32 delay;
    u32 object;
    UIObject *objectPtr;
    bool loop;
    mm::mtl::BitFlag<32> flags;
    u32 handler;
    u32 id;
    UITransform defaultTransform;
    UIDisplayInfo defaultDisplayInfo;
  };

  UICtrlManager();
  virtual ~UICtrlManager();
  void update(const fw::UpdateInfo &info);
  void releaseCtrlSlot(int slot);
  void setDefault(int slot);
  void stopAll();
  void stopCtrl(int slot, bool release, bool callback);
  int reserveCtrlSlot(u32 handle, bool loop);
  int getCtrlSlot(u32 handle);
  void changeEventHandleObject(int slot, u32 handler);
  void setDelayTime(int slot, f32 delay);
  void addPositionMethod(int slot, s16 x, s16 y, CURVE_TYPE curve);
  void addScaleMethod(int slot, f32 x, f32 y, CURVE_TYPE curve);
  void addAlphaMethod(int slot, f32 alpha, CURVE_TYPE curve);
  void addBrightMethod(int slot, f32 bright, CURVE_TYPE curve);
  void addRotMethod(int slot, f32 rot, CURVE_TYPE curve);
  void addMulColorMethod(int slot, const mm::Col3 &color, CURVE_TYPE curve);
  void addAddColorMethod(int slot, const mm::Col3 &color, CURVE_TYPE curve);
  void addMotionMethod(int slot, const char *motion, const char *name);
  void addUndoMethod(int slot, CURVE_TYPE curve);
  void startCtrl(int slot, f32 duration, u32 flags, u32 id);
  void getDefaultTransfom(int slot, UITransform &transform);
  void getDefaultDisplayInfo(int slot, UIDisplayInfo &displayInfo);
  void setSpeedFactor(int slot, f32 speedFactor);
  void addCtrlObject(UICtrlObject *object);
  void addUpdater(IUICtrlUpdater &updater);
  void delUpdater(IUICtrlUpdater &updater);
  bool isBusyCtrl(int slot);

  static bool isValidSlot(int slot) { return slot >= 0 && slot <= CTRL_SLOT_MAX; }

  CtrlSlot slots[CTRL_SLOT_MAX];
  mm::mtl::IntrusiveList<UICtrlObject> ctrlObjects;
  mm::mtl::IntrusiveList<IUICtrlUpdater> updaters;
};

static_assert(offsetof(UICtrlManager::CtrlSlot, scale) == 0x10, "");
static_assert(offsetof(UICtrlManager::CtrlSlot, alpha) == 0x40, "");
static_assert(offsetof(UICtrlManager::CtrlSlot, bright) == 0x50, "");
static_assert(offsetof(UICtrlManager::CtrlSlot, rot) == 0x60, "");
static_assert(offsetof(UICtrlManager::CtrlSlot, mulColor) == 0x70, "");
static_assert(offsetof(UICtrlManager::CtrlSlot, addColor) == 0x90, "");
static_assert(offsetof(UICtrlManager::CtrlSlot, motion) == 0xb0, "");
static_assert(offsetof(UICtrlManager::CtrlSlot, ctrl) == 0xf0, "");
static_assert(offsetof(UICtrlManager::CtrlSlot, methods) == 0x178, "");
static_assert(offsetof(UICtrlManager::CtrlSlot, delay) == 0x1d0, "");
static_assert(offsetof(UICtrlManager::CtrlSlot, object) == 0x1d4, "");
static_assert(offsetof(UICtrlManager::CtrlSlot, objectPtr) == 0x1d8, "");
static_assert(offsetof(UICtrlManager::CtrlSlot, loop) == 0x1e0, "");
static_assert(offsetof(UICtrlManager::CtrlSlot, flags) == 0x1e4, "");
static_assert(offsetof(UICtrlManager::CtrlSlot, handler) == 0x1e8, "");
static_assert(offsetof(UICtrlManager::CtrlSlot, id) == 0x1ec, "");
static_assert(offsetof(UICtrlManager::CtrlSlot, defaultTransform) == 0x1f0, "");
static_assert(offsetof(UICtrlManager::CtrlSlot, defaultDisplayInfo) == 0x220, "");
static_assert(sizeof(UICtrlManager::CtrlSlot) == 0x270, "");
static_assert(offsetof(UICtrlManager, slots) == 0x10, "");
static_assert(offsetof(UICtrlManager, ctrlObjects) == 0x13810, "");
static_assert(offsetof(UICtrlManager, updaters) == 0x13828, "");
static_assert(sizeof(UICtrlManager) == 0x13840, "");

} // namespace ui
