#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"
#include "ui/ui_object_acc.h"

namespace ui {
class UICtrlCursorSelect;
class UISelectObjList;
} // namespace ui

namespace gf {
class GfMenuCallContext;
class GfMenuItemList;
class GfMenuReferenceNumber;

class GfMenuObjBlOrb : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjBlOrb *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];       // Actively zero-initialized unknown byte range, NOT padding; original name/role unknown.
    GfMenuObjBlOrb *unknown20; // Inferred role: owner; original member name unknown.
  };

  class SlotListener : public ui::UIObjectListener {
  public:
    SlotListener(GfMenuObjBlOrb *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];       // Actively zero-initialized unknown byte range, NOT padding; original name/role unknown.
    GfMenuObjBlOrb *unknown20; // Inferred role: owner; original member name unknown.
  };

  class ItemListener : public ui::UIObjectListener {
  public:
    ItemListener(GfMenuObjBlOrb *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];       // Actively zero-initialized unknown byte range, NOT padding; original name/role unknown.
    GfMenuObjBlOrb *unknown20; // Inferred role: owner; original member name unknown.
  };

  // Inferred helper: runs a quarter second control on the main layout and waits for its end; original name unknown.
  bool unknown002(u32 method) {
    if (unknown2e8 == -1) {
      ui::UIObjectAcc acc(unknown18, "LAY_main");
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = method;
      param.unknown00 = 0.25f;
      unknown2e8 = GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    }
    if (GfMenuObjUtil::isBusyCtrl(unknown2e8)) {
      return false;
    }
    unknown2e8 = -1;
    return true;
  }

  GfMenuObjBlOrb(u32 handle);
  ~GfMenuObjBlOrb() override;
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

  u32 unknown24;                                          // Inferred role: blade; original member name unknown.
  ui::UISelectObjList *unknown28;                         // Inferred role: slot objects; original member name unknown.
  ui::UICtrlCursorSelect *unknown30;                      // Inferred role: slot cursor; original member name unknown.
  GfMenuItemList *unknown38;                              // Inferred role: item list; original member name unknown.
  ui::UISelectObjList *unknown40;                         // Inferred role: item objects; original member name unknown.
  ui::UICtrlCursorSelect *unknown48;                      // Inferred role: item cursor; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown50; // Inferred role: reference orb; original member name unknown.
  GfMenuSequence<GfMenuObjBlOrb, 8> unknown58;            // Inferred role: appear and leave steps; original member name unknown.
  int unknown2e8;                                         // Inferred role: control of the appear and leave phases, -1 when idle; original member name unknown.
  GfMenuCallContext *unknown2f0;                          // Inferred role: call context; original member name unknown.
};

static_assert(offsetof(GfMenuObjBlOrb::MainListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjBlOrb::SlotListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjBlOrb::SlotListener) == 0x28, "");
static_assert(offsetof(GfMenuObjBlOrb::ItemListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjBlOrb::ItemListener) == 0x28, "");
static_assert(offsetof(GfMenuObjBlOrb, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjBlOrb, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjBlOrb, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjBlOrb, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjBlOrb, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjBlOrb, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjBlOrb, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjBlOrb, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuObjBlOrb, unknown2e8) == 0x2e8, "");
static_assert(offsetof(GfMenuObjBlOrb, unknown2f0) == 0x2f0, "");
static_assert(sizeof(GfMenuObjBlOrb) == 0x2f8, "");

} // namespace gf
