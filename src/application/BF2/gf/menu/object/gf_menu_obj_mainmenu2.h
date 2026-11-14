#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"
#include "ui/input/ui_input_layer.h"

namespace ui {
class UICtrlCursorSelect;
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

  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjMainMenu2 *owner) : unknown0c(), _10(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    int unknown0c; // Inferred role: fade state of the menu, 1 when faded in; original member name unknown.
    u8 _10[0x1c - 0x10];
    u8 _1c[0x20 - 0x1c];
    GfMenuObjMainMenu2 *unknown20; // Inferred role: owner; original member name unknown.
  };

  class ContentsListener : public ui::UIObjectListener {
  public:
    ContentsListener(GfMenuObjMainMenu2 *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    u8 _1c[0x20 - 0x1c];
    GfMenuObjMainMenu2 *unknown20; // Inferred role: owner; original member name unknown.
  };

  class IndexListener : public ui::UIObjectListener {
  public:
    IndexListener(GfMenuObjMainMenu2 *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    u8 _1c[0x20 - 0x1c];
    GfMenuObjMainMenu2 *unknown20; // Inferred role: owner; original member name unknown.
  };

  class CloseListener : public ui::UIObjectListener {
  public:
    CloseListener(GfMenuObjMainMenu2 *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    u8 _1c[0x20 - 0x1c];
    GfMenuObjMainMenu2 *unknown20; // Inferred role: owner; original member name unknown.
  };

  // Inferred role: open type and value kept for the next opening; original type name unknown.
  struct unknown007 {
    unknown007() : unknown00(0), unknown04(0) {}
    unknown007(int type, u32 value) : unknown00(type), unknown04(value) {}

    int unknown00; // Inferred role: open type, -1 at start; original member name unknown.
    u32 unknown04; // Inferred role: value returned by openChrChangeSub; original member name unknown.
  };

  class ChrChangeListener : public ui::UIObjectListener {
  public:
    ChrChangeListener(GfMenuObjMainMenu2 *owner) : unknown0c(), unknown10(), _18(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    int unknown0c;        // Inferred role: 1 while the change menu is open; original member name unknown.
    unknown007 unknown10; // Inferred role: open type and kept value; original member name unknown.
    u8 _18[0x1c - 0x18];
    u8 _1c[0x20 - 0x1c];
    GfMenuObjMainMenu2 *unknown20; // Inferred role: owner; original member name unknown.
  };

  struct ChrChangeParam {
    ChrChangeParam() : unknown00(0), unknown04(false), unknown08(0), unknown0c(false), unknown10(0), unknown18(nullptr), unknown20(nullptr), unknown28(0), unknown2c(true), unknown30(0) {}

    int unknown00;               // Inferred role: open type, 0 for drivers and 1 or 2 for blades; original member name unknown.
    bool unknown04;              // Inferred role: open event flag; original member name unknown.
    int unknown08;               // Inferred role: previous open type; original member name unknown.
    bool unknown0c;              // Inferred role: change menu was open; original member name unknown.
    u32 unknown10;               // Inferred role: object receiving the selection events; original member name unknown.
    GfMenuDriverList *unknown18; // Inferred role: driver list; original member name unknown.
    GfMenuBladeList *unknown20;  // Inferred role: blade list; original member name unknown.
    u32 unknown28;               // Inferred role: reference driver; original member name unknown.
    bool unknown2c;              // Inferred role: show the change menu; original member name unknown.
    u32 unknown30;               // Inferred role: value kept between openings; original member name unknown.
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
  static void setSubIndexText(u32 text);
  static void dispGuide(bool isDisp);
  static void setupMainMenu(ui::UIObjectAcc &acc);
  static void setSystemKeyEnable(bool enable);
  static void cancelEnableMainMenu(bool enable);
  static void setDispGold(bool isDisp);
  static void setContentsSubText(u32 handle, u32 index, u32 child);
  static void dispCloseButton();
  static bool isOpenCharMenu();
  static void execMapJump();
  static void setContentsText(u32 handle, u32 index);
  static void getContentsText(u32 index, u8 *&bdat, u32 &text);
  static void initChrChangeDr(ui::UIObjectAcc &acc, GfMenuDriverList *list);
  static void initChrChangeBl(ui::UIObjectAcc &acc, GfMenuBladeList *list);
  static int moveMainMenu(ui::UIObjectAcc &acc, u32 index, bool);
  static void refreshCharChangeDr(ui::UIObjectAcc &acc, GfMenuDriverList *list);
  static void refreshCharChangeBl(ui::UIObjectAcc &acc, GfMenuBladeList *list);
  static void inputChrChangeSub(ui::UIObjectAcc &acc, ChrChangeParam &param, int index);
  static bool openChrChangeSub(ui::UIObjectAcc &acc, ChrChangeParam &param, u32 &value);
  static void openChrChange2Sub(ui::UIObjectAcc &acc, ChrChangeParam &param);
  static void closeChrChangeSub(ui::UIObjectAcc &acc, ChrChangeParam &param);
  void initialize() override;
  void finalize() override;
  void update() override;
  bool seqExecTerm();

  static u32 s_openMenuID;
  static bool s_cancelEnable;

  u8 _24[0x28 - 0x24];
  ui::UICtrlCursorSelect *unknown28; // Inferred role: contents cursor; original member name unknown.
  GfMenuCallContext *unknown30;      // Inferred role: call context; original member name unknown.
  u16 unknown38;                     // Inferred role: unused; original member name unknown.
  u8 _3a[0x3c - 0x3a];
  int unknown3c;                                   // Inferred role: unused, -1 at start; original member name unknown.
  int unknown40;                                   // Inferred role: unused, -1 at start; original member name unknown.
  u32 unknown44;                                   // Inferred role: open menu; original member name unknown.
  GfMenuDriverList *unknown48;                     // Inferred role: driver list; original member name unknown.
  GfMenuBladeList *unknown50;                      // Inferred role: blade list; original member name unknown.
  SelectionChecker *unknown58;                     // Inferred role: selection checker; original member name unknown.
  mm::mtl::FixedVector<u32, 7> unknown60;          // Inferred role: main menu order entries; original member name unknown.
  u32 unknown88;                                   // Inferred role: object receiving the character change selection; original member name unknown.
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
static_assert(offsetof(GfMenuObjMainMenu2::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjMainMenu2::MainListener) == 0x28, "");
static_assert(offsetof(GfMenuObjMainMenu2::ContentsListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjMainMenu2::ContentsListener) == 0x28, "");
static_assert(offsetof(GfMenuObjMainMenu2::IndexListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjMainMenu2::IndexListener) == 0x28, "");
static_assert(offsetof(GfMenuObjMainMenu2::CloseListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjMainMenu2::CloseListener) == 0x28, "");
static_assert(offsetof(GfMenuObjMainMenu2::ChrChangeListener, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjMainMenu2::ChrChangeListener, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuObjMainMenu2::unknown007, unknown00) == 0x00, "");
static_assert(offsetof(GfMenuObjMainMenu2::unknown007, unknown04) == 0x04, "");
static_assert(sizeof(GfMenuObjMainMenu2::unknown007) == 0x08, "");
static_assert(offsetof(GfMenuObjMainMenu2::ChrChangeListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjMainMenu2::ChrChangeListener) == 0x28, "");
static_assert(offsetof(GfMenuObjMainMenu2::ChrChangeParam, unknown00) == 0x00, "");
static_assert(offsetof(GfMenuObjMainMenu2::ChrChangeParam, unknown04) == 0x04, "");
static_assert(offsetof(GfMenuObjMainMenu2::ChrChangeParam, unknown08) == 0x08, "");
static_assert(offsetof(GfMenuObjMainMenu2::ChrChangeParam, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjMainMenu2::ChrChangeParam, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuObjMainMenu2::ChrChangeParam, unknown18) == 0x18, "");
static_assert(offsetof(GfMenuObjMainMenu2::ChrChangeParam, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjMainMenu2::ChrChangeParam, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjMainMenu2::ChrChangeParam, unknown2c) == 0x2c, "");
static_assert(offsetof(GfMenuObjMainMenu2::ChrChangeParam, unknown30) == 0x30, "");
static_assert(sizeof(GfMenuObjMainMenu2::ChrChangeParam) == 0x38, "");

class SelectionChecker : public ui::IUIInputSelectionChecker {
public:
  bool isEnableSelect(u32 handle, int index) override;
};

} // namespace gf
