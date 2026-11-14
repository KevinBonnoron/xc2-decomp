#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"
#include "ui/ui_object_acc.h"

namespace mm {
namespace mtl {
class ReferenceObject;
} // namespace mtl
} // namespace mm

namespace ui {
class UICtrlCursorSelect;
class UISelectObjList;
} // namespace ui

namespace gf {
class GfMenuCallContext;
class GfMenuItemList;
class GfMenuReferenceItem;

class GfMenuObjDrEquip : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjDrEquip *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjDrEquip *unknown20; // Inferred role: owner; original member name unknown.
  };

  class ItemListener : public ui::UIObjectListener {
  public:
    ItemListener(GfMenuObjDrEquip *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjDrEquip *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjDrEquip(u32 handle);
  ~GfMenuObjDrEquip() override;

  // Inferred helper: runs a quarter second control on the main layout and waits for its end; original name unknown.
  bool unknown002(u32 method) {
    if (unknown2e0 == -1) {
      ui::UIObjectAcc acc(unknown18, "LAY_main");
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = method;
      param.unknown00 = 0.25f;
      unknown2e0 = GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    }
    if (GfMenuObjUtil::isBusyCtrl(unknown2e0)) {
      return false;
    }
    unknown2e0 = -1;
    return true;
  }

  static bool attach(GfMenuCallContext *context);
  void initialize() override;
  void finalize() override;
  void update() override;
  void suspendInput();
  void resumeInput();
  bool seqStartOpen();
  bool seqEndOpen();
  bool seqStartClose();
  bool seqEndClose();
  bool seqAppearPhase1();
  bool seqLeavePhase1();

  u32 unknown24;                                 // Inferred role: reference driver index; original member name unknown.
  GfMenuItemList *unknown28;                     // Inferred role: equipment items; original member name unknown.
  ui::UISelectObjList *unknown30;                // Inferred role: item objects; original member name unknown.
  ui::UICtrlCursorSelect *unknown38;             // Inferred role: item cursor; original member name unknown.
  GfMenuCallContext *unknown40;                  // Inferred role: call context; original member name unknown.
  mm::mtl::ReferenceObject *unknown48;           // Inferred role: reference-counted object; type and original member name unknown.
  GfMenuSequence<GfMenuObjDrEquip, 8> unknown50; // Inferred role: appear and leave steps; original member name unknown.
  int unknown2e0;                                // Inferred role: control of the appear and leave phases, -1 when idle; original member name unknown.
  u8 _2e4[0x2e8 - 0x2e4];
  mm::mtl::IntrusivePtr<GfMenuReferenceItem> unknown2e8; // Inferred role: reference item; original member name unknown.
};

static_assert(offsetof(GfMenuObjDrEquip, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjDrEquip, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjDrEquip, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjDrEquip, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjDrEquip, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjDrEquip, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjDrEquip, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjDrEquip, unknown2e0) == 0x2e0, "");
static_assert(offsetof(GfMenuObjDrEquip, unknown2e8) == 0x2e8, "");
static_assert(offsetof(GfMenuObjDrEquip::MainListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjDrEquip::ItemListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjDrEquip::MainListener) == 0x28, "");
static_assert(sizeof(GfMenuObjDrEquip::ItemListener) == 0x28, "");

} // namespace gf
