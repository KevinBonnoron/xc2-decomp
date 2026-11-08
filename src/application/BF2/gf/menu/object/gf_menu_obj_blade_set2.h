#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"

namespace mm {
namespace mtl {
class ReferenceObject;
} // namespace mtl
} // namespace mm

namespace ui {
class UICtrlCursorSelect;
class UIObjectAcc;
} // namespace ui

namespace gf {
struct GF_SCOM_HANDLE;
class GfMenuBladeList;
class GfMenuCallContext;
class GfMenuDriverList;

class GfMenuObjBladeSet2 : public GfMenuObject {
public:
  GfMenuObjBladeSet2(u32 handle);
  ~GfMenuObjBladeSet2() override;
  static void sendEvent(u32 handle, u32 type, u32 param, f32 delay);
  static int setFadeIn(u32 handle);
  static int setFadeOut(u32 handle);
  void initialize() override;
  void finalize() override;
  void update() override;
  static void setupMain(ui::UIObjectAcc &acc);
  static void createDriverList(u32 driver, GfMenuDriverList *list);
  static bool checkInSlot(u32 blade, GfMenuBladeList *list);
  static void setCloseToReturn();
  static void setCloseToFSClose();
  bool seqWaitCommand();
  bool seqReturnBlSlot();
  static void refreshBladeSlot(GfMenuBladeList *list);
  void refreshBladeList();

  u8 _24[0x28 - 0x24];
  GfMenuBladeList *unknown28;          // Inferred role: blades; original member name unknown.
  ui::UICtrlCursorSelect *unknown30;   // Inferred role: blade cursor; original member name unknown.
  GfMenuBladeList *unknown38;          // Inferred role: blades; original member name unknown.
  ui::UICtrlCursorSelect *unknown40;   // Inferred role: blade cursor; original member name unknown.
  GfMenuDriverList *unknown48;         // Inferred role: drivers; original member name unknown.
  mm::mtl::ReferenceObject *unknown50; // Inferred role: reference-counted object; type and original member name unknown.
  u32 unknown58;                       // Role and original member name unknown, cleared by the constructor.
  u8 _5c[0x60 - 0x5c];
  GfMenuCallContext *unknown60; // Inferred role: call context; original member name unknown.
  u32 unknown68;                // Role and original member name unknown, cleared by the constructor.
  u8 _6c[0x78 - 0x6c];
  bool unknown78; // Role and original member name unknown, cleared by the constructor.
  u8 _79[0x80 - 0x79];
  GfMenuCallContext *unknown80; // Inferred role: call context; original member name unknown.
  bool unknown88;               // Role and original member name unknown, cleared by the constructor.
  u8 _89[0x8c - 0x89];
  u32 unknown8c; // Role and original member name unknown, cleared by the constructor.
  u32 unknown90; // Inferred role: sort type; original member name unknown, cleared by the constructor.
  u32 unknown94; // Role and original member name unknown, cleared by the constructor.
  u32 unknown98; // Role and original member name unknown, cleared by the constructor.
  u8 _9c[0xa0 - 0x9c];
  GfMenuSequence<GfMenuObjBladeSet2, 8> unknowna0;  // Inferred role: blade set steps; original member name unknown.
  GF_SCOM_HANDLE *unknown330;                       // Inferred role: pending blade set command; original member name unknown.
  GfMenuSequence<GfMenuObjBladeSet2, 4> unknown338; // Inferred role: image steps; original member name unknown.
};

static_assert(offsetof(GfMenuObjBladeSet2, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjBladeSet2, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjBladeSet2, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjBladeSet2, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjBladeSet2, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjBladeSet2, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjBladeSet2, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuObjBladeSet2, unknown60) == 0x60, "");
static_assert(offsetof(GfMenuObjBladeSet2, unknown68) == 0x68, "");
static_assert(offsetof(GfMenuObjBladeSet2, unknown78) == 0x78, "");
static_assert(offsetof(GfMenuObjBladeSet2, unknown80) == 0x80, "");
static_assert(offsetof(GfMenuObjBladeSet2, unknown88) == 0x88, "");
static_assert(offsetof(GfMenuObjBladeSet2, unknown8c) == 0x8c, "");
static_assert(offsetof(GfMenuObjBladeSet2, unknown90) == 0x90, "");
static_assert(offsetof(GfMenuObjBladeSet2, unknown94) == 0x94, "");
static_assert(offsetof(GfMenuObjBladeSet2, unknown98) == 0x98, "");
static_assert(offsetof(GfMenuObjBladeSet2, unknowna0) == 0xa0, "");
static_assert(offsetof(GfMenuObjBladeSet2, unknown330) == 0x330, "");
static_assert(offsetof(GfMenuObjBladeSet2, unknown338) == 0x338, "");
static_assert(sizeof(GfMenuObjBladeSet2) == 0x498, "");

} // namespace gf
