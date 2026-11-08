#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"
#include "ui/input/ui_input_layer.h"

namespace ui {
class UIObjectNumberPlugin;
class UIObjectAcc;
} // namespace ui

namespace gf {

class GfMenuBladeList;
class GfMenuCallContext;
class GfMenuDriverList;
class SelectionChecker;

class GfMenuObjMainMenu2 : public GfMenuObject {
public:
  struct OpenParam {
    u32 unknown00; // Inferred role: page; original member name unknown.
  };

  GfMenuObjMainMenu2(u32 handle);
  ~GfMenuObjMainMenu2() override;
  static void registOpenParam(const OpenParam &param);
  static void sendEvent(u32 handle, u32 type, u32 param);
  static void setCloseKeyEnable(bool enable);
  static void openCharChange(u32 handle, u32 type, bool flag);
  static void closeCharChange();
  static void openMainMenu();
  static void setContentsIcon(ui::UIObjectNumberPlugin *plugin, u32 icon);
  static void disableCharChange();
  static void setSubLayer(u32 layer);
  static void setGuideText(u32 text);
  static void setSystemKeyEnable(bool enable);
  static void cancelEnableMainMenu(bool enable);
  static void setDispGold(bool isDisp);
  static void setContentsSubText(u32 handle, u32 index, u32 child);
  static void dispCloseButton();
  static bool isOpenCharMenu();
  static void execMapJump();
  static void setContentsText(u32 handle, u32 index);
  static void initChrChangeDr(ui::UIObjectAcc &acc, GfMenuDriverList *list);
  static void initChrChangeBl(ui::UIObjectAcc &acc, GfMenuBladeList *list);
  static int moveMainMenu(ui::UIObjectAcc &acc, u32 index, bool);
  static void refreshCharChangeDr(ui::UIObjectAcc &acc, GfMenuDriverList *list);
  void initialize() override;
  void finalize() override;
  void update() override;
  bool seqExecTerm();

  static u32 s_openMenuID;
  static bool s_cancelEnable;

  u8 _24[0x28 - 0x24];
  GfMenuCallContext *unknown28; // Inferred role: call context; original member name unknown.
  GfMenuCallContext *unknown30; // Inferred role: call context; original member name unknown.
  u16 unknown38;                // Inferred role: unused; original member name unknown.
  u8 _3a[0x3c - 0x3a];
  int unknown3c;                                   // Inferred role: unused, -1 at start; original member name unknown.
  int unknown40;                                   // Inferred role: unused, -1 at start; original member name unknown.
  u32 unknown44;                                   // Inferred role: open menu; original member name unknown.
  GfMenuDriverList *unknown48;                     // Inferred role: driver list; original member name unknown.
  GfMenuBladeList *unknown50;                      // Inferred role: blade list; original member name unknown.
  SelectionChecker *unknown58;                     // Inferred role: selection checker; original member name unknown.
  mm::mtl::FixedVector<u32, 8> unknown60;          // Inferred role: unused; element type inferred from the size of the storage; original member name unknown.
  u32 unknown88;                                   // Inferred role: unused; original member name unknown.
  bool unknown8c;                                  // Inferred role: unused; original member name unknown.
  GfMenuSequence<GfMenuObjMainMenu2, 8> unknown90; // Inferred role: menu steps; original member name unknown.
  bool unknown320;                                 // Inferred role: skip the popup pickup resume once; original member name unknown.
};

static_assert(offsetof(GfMenuObjMainMenu2, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjMainMenu2, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjMainMenu2, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjMainMenu2, unknown3c) == 0x3c, "");
static_assert(offsetof(GfMenuObjMainMenu2, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjMainMenu2, unknown44) == 0x44, "");
static_assert(offsetof(GfMenuObjMainMenu2, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjMainMenu2, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjMainMenu2, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuObjMainMenu2, unknown60) == 0x60, "");
static_assert(offsetof(GfMenuObjMainMenu2, unknown88) == 0x88, "");
static_assert(offsetof(GfMenuObjMainMenu2, unknown8c) == 0x8c, "");
static_assert(offsetof(GfMenuObjMainMenu2, unknown90) == 0x90, "");
static_assert(offsetof(GfMenuObjMainMenu2, unknown320) == 0x320, "");
static_assert(sizeof(GfMenuObjMainMenu2) == 0x328, "");

class SelectionChecker : public ui::IUIInputSelectionChecker {
public:
  bool isEnableSelect(u32 handle, int index) override;
};

} // namespace gf
