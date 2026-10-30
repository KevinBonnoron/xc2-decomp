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
    UICtrlMethodPos unknown00;          // Inferred role: pos; original member name unknown.
    UICtrlMethodScale unknown10;        // Inferred role: scale; original member name unknown.
    UICtrlMethodAlpha unknown40;        // Inferred role: alpha; original member name unknown.
    UICtrlMethodBright unknown50;       // Inferred role: bright; original member name unknown.
    UICtrlMethodRot unknown60;          // Inferred role: rot; original member name unknown.
    UICtrlMethodMulColor unknown70;     // Inferred role: mul color; original member name unknown.
    UICtrlMethodAddColor unknown90;     // Inferred role: add color; original member name unknown.
    UICtrlMethodMotion unknownb0;       // Inferred role: motion; original member name unknown.
    UICtrl unknownf0;                   // Inferred role: ctrl; original member name unknown.
    UICtrl::MethodList unknown178;      // Inferred role: methods; original member name unknown.
    f32 unknown1d0;                     // Inferred role: delay; original member name unknown.
    u32 unknown1d4;                     // Inferred role: object; original member name unknown.
    UIObject *unknown1d8;               // Inferred role: object ptr; original member name unknown.
    bool unknown1e0;                    // Inferred role: loop; original member name unknown.
    mm::mtl::unknown027<32> unknown1e4; // Inferred role: flags; original member name unknown.
    u32 unknown1e8;                     // Inferred role: handler; original member name unknown.
    u32 unknown1ec;                     // Inferred role: id; original member name unknown.
    UITransform unknown1f0;             // Inferred role: default transform; original member name unknown.
    UIDisplayInfo unknown220;           // Inferred role: default display info; original member name unknown.
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

  CtrlSlot unknown10[CTRL_SLOT_MAX];                   // Inferred role: slots; original member name unknown.
  mm::mtl::IntrusiveList<UICtrlObject> unknown13810;   // Inferred role: ctrl objects; original member name unknown.
  mm::mtl::IntrusiveList<IUICtrlUpdater> unknown13828; // Inferred role: updaters; original member name unknown.
};

static_assert(offsetof(UICtrlManager::CtrlSlot, unknown10) == 0x10, "");
static_assert(offsetof(UICtrlManager::CtrlSlot, unknown40) == 0x40, "");
static_assert(offsetof(UICtrlManager::CtrlSlot, unknown50) == 0x50, "");
static_assert(offsetof(UICtrlManager::CtrlSlot, unknown60) == 0x60, "");
static_assert(offsetof(UICtrlManager::CtrlSlot, unknown70) == 0x70, "");
static_assert(offsetof(UICtrlManager::CtrlSlot, unknown90) == 0x90, "");
static_assert(offsetof(UICtrlManager::CtrlSlot, unknownb0) == 0xb0, "");
static_assert(offsetof(UICtrlManager::CtrlSlot, unknownf0) == 0xf0, "");
static_assert(offsetof(UICtrlManager::CtrlSlot, unknown178) == 0x178, "");
static_assert(offsetof(UICtrlManager::CtrlSlot, unknown1d0) == 0x1d0, "");
static_assert(offsetof(UICtrlManager::CtrlSlot, unknown1d4) == 0x1d4, "");
static_assert(offsetof(UICtrlManager::CtrlSlot, unknown1d8) == 0x1d8, "");
static_assert(offsetof(UICtrlManager::CtrlSlot, unknown1e0) == 0x1e0, "");
static_assert(offsetof(UICtrlManager::CtrlSlot, unknown1e4) == 0x1e4, "");
static_assert(offsetof(UICtrlManager::CtrlSlot, unknown1e8) == 0x1e8, "");
static_assert(offsetof(UICtrlManager::CtrlSlot, unknown1ec) == 0x1ec, "");
static_assert(offsetof(UICtrlManager::CtrlSlot, unknown1f0) == 0x1f0, "");
static_assert(offsetof(UICtrlManager::CtrlSlot, unknown220) == 0x220, "");
static_assert(sizeof(UICtrlManager::CtrlSlot) == 0x270, "");
static_assert(offsetof(UICtrlManager, unknown10) == 0x10, "");
static_assert(offsetof(UICtrlManager, unknown13810) == 0x13810, "");
static_assert(offsetof(UICtrlManager, unknown13828) == 0x13828, "");
static_assert(sizeof(UICtrlManager) == 0x13840, "");

} // namespace ui
