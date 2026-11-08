#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"

namespace ui {
class UISelectObjList;
} // namespace ui

namespace gf {
class GfMenuCallContext;

class GfMenuObjPartyForm2 : public GfMenuObject {
public:
  struct OpenParam {
    u16 unknown00; // Role and original member name unknown.
  };

  GfMenuObjPartyForm2(u32 handle);
  ~GfMenuObjPartyForm2() override;
  void update() override;
  static void registOpenParam(const OpenParam &param);
  u32 getCursorID(u32 index);
  void changeCursorMode(u32 mode);
  bool seqStartOpen();
  bool seqAppearTitle();
  bool seqAppearFrame();
  bool seqAppearPlate();
  bool seqAnnounceChange();
  bool seqWaitOpenEnd();
  bool seqStartSwap();
  bool seqTakePlate();
  bool seqMovePlate();
  bool seqWaitSwapEnd();

  // Inferred role: the object ring of a driver list and a second word; original type name unknown.
  struct unknown001 {
    ui::UISelectObjList *unknown00; // Inferred role: driver objects; original member name unknown.
    u64 unknown08;                  // Role and original member name unknown, cleared by the constructor.
  };

  u8 _24[0x38 - 0x24];
  bool unknown38; // Role and original member name unknown, cleared by the constructor.
  u8 _39[0x40 - 0x39];
  unknown001 unknown40[2];                          // Inferred role: the two driver rings; original member name unknown.
  u32 unknown60;                                    // Inferred role: ring of the cursor, 0xff at start; original member name unknown.
  u32 unknown64;                                    // Inferred role: ring the cursor came from, 0xff at start; original member name unknown.
  GfMenuSequence<GfMenuObjPartyForm2, 8> unknown68; // Inferred role: queued steps; original member name unknown.
  u16 unknown2f8;                                   // Role and original member name unknown, cleared by the constructor.
  u8 _2fa[0x2fc - 0x2fa];
  int unknown2fc; // Inferred role: control of the current step, -1 when idle; original member name unknown.
  int unknown300; // Inferred role: control of the first plate, -1 when idle; original member name unknown.
  int unknown304; // Inferred role: control of the second plate, -1 when idle; original member name unknown.
  u32 unknown308; // Inferred role: display priority of the plate; original member name unknown.
  u8 _30c[0x310 - 0x30c];
  GfMenuCallContext *unknown310; // Inferred role: announce call context; original member name unknown.
  u64 unknown318;                // Role and original member name unknown, cleared by the constructor.
};

static_assert(offsetof(GfMenuObjPartyForm2, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjPartyForm2, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjPartyForm2, unknown60) == 0x60, "");
static_assert(offsetof(GfMenuObjPartyForm2, unknown64) == 0x64, "");
static_assert(offsetof(GfMenuObjPartyForm2, unknown68) == 0x68, "");
static_assert(offsetof(GfMenuObjPartyForm2, unknown2f8) == 0x2f8, "");
static_assert(offsetof(GfMenuObjPartyForm2, unknown2fc) == 0x2fc, "");
static_assert(offsetof(GfMenuObjPartyForm2, unknown300) == 0x300, "");
static_assert(offsetof(GfMenuObjPartyForm2, unknown304) == 0x304, "");
static_assert(offsetof(GfMenuObjPartyForm2, unknown308) == 0x308, "");
static_assert(offsetof(GfMenuObjPartyForm2, unknown310) == 0x310, "");
static_assert(offsetof(GfMenuObjPartyForm2, unknown318) == 0x318, "");

} // namespace gf
