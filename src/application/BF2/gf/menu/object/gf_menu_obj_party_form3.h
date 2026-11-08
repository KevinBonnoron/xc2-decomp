#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace ui {
class UIObjectAcc;
} // namespace ui

namespace gf {
class GfMenuCallContext;
class GfMenuDriverList;
class GfMenuReferenceNumber;

class GfMenuObjPartyForm3 : public GfMenuObject {
public:
  bool seqWaitOpenEnd();
  struct OpenParam {
    u16 unknown00; // Role and original member name unknown.
  };

  GfMenuObjPartyForm3(u32 handle);
  ~GfMenuObjPartyForm3() override;
  static void registOpenParam(const OpenParam &param);
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle);
  static int setFadeOut(u32 handle);
  void initialize() override;
  void finalize() override;
  void update() override;
  static void setupBGLayout(ui::UIObjectAcc &, u32, bool);
  void refreshRemoveAddOperation(u32 handle, int index);
  bool seqAnnounceChange();

  u8 _24[0x28 - 0x24];
  GfMenuDriverList *unknown28; // Inferred role: drivers; original member name unknown.
  u16 unknown30;               // Role and original member name unknown, cleared by the constructor.
  u8 _32[0x34 - 0x32];
  u32 unknown34;  // Inferred role: party member count; original member name unknown.
  u32 unknown38;  // Role and original member name unknown, cleared by the constructor.
  u32 unknown3c;  // Role and original member name unknown, cleared by the constructor.
  int unknown40;  // Inferred role: pending slot, -1 when none; original member name unknown.
  bool unknown44; // Role and original member name unknown, cleared by the constructor.
  u8 _45[0x48 - 0x45];
  mm::mtl::FixedArray<mm::mtl::IntrusivePtr<GfMenuReferenceNumber>, 7> unknown48; // Inferred role: party member numbers; original member name unknown.
  GfMenuSequence<GfMenuObjPartyForm3, 8> unknown80;                               // Inferred role: queued steps; original member name unknown.
  GfMenuCallContext *unknown310;                                                  // Inferred role: announce call context; original member name unknown.
  bool unknown318;                                                                // Inferred role: unused, true at start; original member name unknown.
  bool unknown319;                                                                // Role and original member name unknown, cleared by the constructor.
  u8 _31a[0x320 - 0x31a];
};

static_assert(offsetof(GfMenuObjPartyForm3, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjPartyForm3, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjPartyForm3, unknown34) == 0x34, "");
static_assert(offsetof(GfMenuObjPartyForm3, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjPartyForm3, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjPartyForm3, unknown44) == 0x44, "");
static_assert(offsetof(GfMenuObjPartyForm3, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjPartyForm3, unknown80) == 0x80, "");
static_assert(offsetof(GfMenuObjPartyForm3, unknown310) == 0x310, "");
static_assert(offsetof(GfMenuObjPartyForm3, unknown318) == 0x318, "");
static_assert(sizeof(GfMenuObjPartyForm3) == 0x320, "");

} // namespace gf
