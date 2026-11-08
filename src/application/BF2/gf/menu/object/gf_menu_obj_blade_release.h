#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace mm {
namespace mtl {
class ReferenceObject;
} // namespace mtl
} // namespace mm

namespace ui {
class UICtrlCursorSelect;
class UISelectObjList;
class UIObjectAcc;
} // namespace ui

namespace gf {

class GfMenuBladeList;
class GfMenuCallContext;
class GfMenuDriverList;
class GfMenuIDList;
class GfMenuItemList;
struct GAME_VOICE_HANDLE;

class GfMenuObjBladeRelease : public GfMenuObject {
public:
  GfMenuObjBladeRelease(u32 handle);
  ~GfMenuObjBladeRelease() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  void refreshBladeInfo(ui::UIObjectAcc &acc, u32 type);
  bool seqOpenImage();
  bool seqSubMenuOpen();
  bool seqEffReleaseA();
  bool seqEffReleaseB();
  bool seqConfirmBoosterGet();
  bool seqResumeRelease();
  bool seqEffReleaseC();
  bool seqEffReleaseD();
  bool seqSubMenuEnd();
  bool seqSubMenuOpenCustomize();
  bool seqSubMenuErrorOvdOnly();
  bool seqSubMenuErrorOvdLastOne();
  bool seqSubMenuWaitLoadCustomize();
  bool seqSubMenuWaitEndCustomize();

  u8 _24[0x28 - 0x24];
  mm::mtl::ReferenceObject *unknown28;                // Inferred role: reference-counted object; type and original member name unknown.
  GfMenuBladeList *unknown30;                         // Inferred role: releasable blades; original member name unknown.
  ui::UISelectObjList *unknown38;                     // Inferred role: blade objects; original member name unknown.
  ui::UICtrlCursorSelect *unknown40;                  // Inferred role: blade cursor; original member name unknown.
  GfMenuCallContext *unknown48;                       // Inferred role: call context; original member name unknown.
  GfMenuCallContext *unknown50;                       // Inferred role: call context; original member name unknown.
  GfMenuSequence<GfMenuObjBladeRelease, 8> unknown58; // Inferred role: queued steps; original member name unknown.
  bool unknown2e8;                                    // Role and original member name unknown, cleared by the constructor.
  u8 _2e9[0x2f0 - 0x2e9];
  GfMenuSequence<GfMenuObjBladeRelease, 4> unknown2f0; // Inferred role: queued effect steps; original member name unknown.
  GfMenuItemList *unknown450;                          // Inferred role: items; original member name unknown.
  bool unknown458;                                     // Role and original member name unknown, cleared by the constructor.
  u8 _459[0x460 - 0x459];
  GfMenuIDList *unknown460; // Inferred role: identifiers; original member name unknown.
  bool unknown468;          // Role and original member name unknown, cleared by the constructor.
  u8 _469[0x46c - 0x469];
  int unknown46c;                           // Role and original member name unknown, set to -1 by the constructor.
  GfMenuDriverList *unknown470;             // Inferred role: drivers; original member name unknown.
  mm::mtl::FixedVector<u16, 16> unknown478; // Inferred role: selected blades; original member name unknown.
  bool unknown4a0;                          // Role and original member name unknown, cleared by the constructor.
  u8 _4a1[0x4a4 - 0x4a1];
  u32 unknown4a4; // Role and original member name unknown, cleared by the constructor.
  u32 unknown4a8; // Role and original member name unknown, cleared by the constructor.
  u8 _4ac[0x4b0 - 0x4ac];
  GAME_VOICE_HANDLE *unknown4b0; // Inferred role: playing voice; original member name unknown.
};

static_assert(offsetof(GfMenuObjBladeRelease, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjBladeRelease, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjBladeRelease, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjBladeRelease, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjBladeRelease, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjBladeRelease, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjBladeRelease, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuObjBladeRelease, unknown2e8) == 0x2e8, "");
static_assert(offsetof(GfMenuObjBladeRelease, unknown2f0) == 0x2f0, "");
static_assert(offsetof(GfMenuObjBladeRelease, unknown450) == 0x450, "");
static_assert(offsetof(GfMenuObjBladeRelease, unknown458) == 0x458, "");
static_assert(offsetof(GfMenuObjBladeRelease, unknown460) == 0x460, "");
static_assert(offsetof(GfMenuObjBladeRelease, unknown468) == 0x468, "");
static_assert(offsetof(GfMenuObjBladeRelease, unknown46c) == 0x46c, "");
static_assert(offsetof(GfMenuObjBladeRelease, unknown470) == 0x470, "");
static_assert(offsetof(GfMenuObjBladeRelease, unknown478) == 0x478, "");
static_assert(offsetof(GfMenuObjBladeRelease, unknown4a0) == 0x4a0, "");
static_assert(offsetof(GfMenuObjBladeRelease, unknown4a4) == 0x4a4, "");
static_assert(offsetof(GfMenuObjBladeRelease, unknown4a8) == 0x4a8, "");
static_assert(offsetof(GfMenuObjBladeRelease, unknown4b0) == 0x4b0, "");
static_assert(sizeof(GfMenuObjBladeRelease) == 0x4b8, "");

} // namespace gf
