#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"

namespace ui {
class UICtrlRevolveSelect;
class UISelectObjList;
} // namespace ui

namespace gf {
class GfMenuBladeList;
class GfMenuCallContext;

class GfMenuObjBlCustomTop : public GfMenuObject {
public:
  GfMenuObjBlCustomTop(u32 handle);
  ~GfMenuObjBlCustomTop() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  void suspendInput();
  void resumeInput();
  bool seqStartOpen();
  bool seqAppearPhase1();
  bool seqAppearPhase2();
  bool seqAppearPhase4();
  bool seqEndOpen();
  bool seqStartAddLayer();
  bool seqAddLayerPhase2();
  bool seqAddLayerPhase3_BlWeapon();
  bool seqAddLayerPhase3_BlOrb();
  bool seqAddLayerPhase4();
  bool seqEndAddLayer();

  u8 _24[0x28 - 0x24];
  GfMenuBladeList *unknown28;                        // Inferred role: blades; original member name unknown.
  ui::UISelectObjList *unknown30;                    // Inferred role: blade objects; original member name unknown.
  ui::UICtrlRevolveSelect *unknown38;                // Inferred role: blade ring control; original member name unknown.
  GfMenuCallContext *unknown40;                      // Inferred role: common jog call context; original member name unknown.
  GfMenuCallContext *unknown48;                      // Inferred role: blade detail call context; original member name unknown.
  GfMenuCallContext *unknown50;                      // Inferred role: call context of the layer being added; original member name unknown.
  GfMenuSequence<GfMenuObjBlCustomTop, 8> unknown58; // Inferred role: queued steps; original member name unknown.
  int unknown2e8;                                    // Inferred role: control of the current step, -1 when idle; original member name unknown.
  u16 unknown2ec;                                    // Inferred role: layer to add; original member name unknown.
};

static_assert(offsetof(GfMenuObjBlCustomTop, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjBlCustomTop, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjBlCustomTop, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjBlCustomTop, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjBlCustomTop, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjBlCustomTop, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjBlCustomTop, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuObjBlCustomTop, unknown2e8) == 0x2e8, "");
static_assert(offsetof(GfMenuObjBlCustomTop, unknown2ec) == 0x2ec, "");

} // namespace gf
