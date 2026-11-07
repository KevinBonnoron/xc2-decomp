#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"
#include "ui/input/ui_input_layer.h"

namespace ui {
class UIObjectNumberPlugin;
} // namespace ui

namespace gf {

class GfMenuObjMainMenu2 : public GfMenuObject {
public:
  struct OpenParam {
    u32 unknown00; // Inferred role: page; original member name unknown.
  };

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
  void initialize() override;
  void finalize() override;
  void update() override;
  bool seqExecTerm();

  static u32 s_openMenuID;
  static bool s_cancelEnable;

  u8 _24[0x44 - 0x24];
  u32 unknown44; // Inferred role: open menu; original member name unknown.
  u8 _48[0x90 - 0x48];
  GfMenuSequence<GfMenuObjMainMenu2, 8> unknown90; // Inferred role: menu steps; original member name unknown.
  bool unknown320;                                 // Inferred role: skip the popup pickup resume once; original member name unknown.
};

static_assert(offsetof(GfMenuObjMainMenu2, unknown44) == 0x44, "");
static_assert(offsetof(GfMenuObjMainMenu2, unknown90) == 0x90, "");
static_assert(offsetof(GfMenuObjMainMenu2, unknown320) == 0x320, "");
static_assert(sizeof(GfMenuObjMainMenu2) == 0x328, "");

class SelectionChecker : public ui::IUIInputSelectionChecker {
public:
  bool isEnableSelect(u32 handle, int index) override;
};

} // namespace gf
