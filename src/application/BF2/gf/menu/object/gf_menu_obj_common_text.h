#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UICtrlCursorSelect;
class UISelectObjList;
} // namespace ui

namespace gf {

class GfMenuBladeList;
class GfMenuCallContext;
class GfMenuDriverList;
class GfMenuIDList;
class GfMenuItemList;
class GfMenuReferenceNumber;
struct MenuCommonWindowParam;

class GfMenuObjCommonText : public GfMenuObject {
public:
  GfMenuObjCommonText(u32 handle);
  ~GfMenuObjCommonText() override;
  static void sendEvent(u32 handle, u32 type, u32 param, f32 delay);
  static int setFadeIn(u32 handle);
  class DialogListener : public ui::UIObjectListener {
  public:
    DialogListener(GfMenuObjCommonText *owner) : unknown0c(0), _10(), unknown18(0), m_menuObjCommonText(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    int unknown0c; // Inferred role: dialog type, 0 for a single button; original member name unknown.
    u8 _10[0x18 - 0x10];
    int unknown18;                            // Inferred role: open flag; original member name unknown.
    GfMenuObjCommonText *m_menuObjCommonText; // Inferred role: owner; original member name unknown.
  };
  class DrChangeListener : public ui::UIObjectListener {
  public:
    DrChangeListener(GfMenuObjCommonText *owner) : _0c(), unknown18(0), m_menuObjCommonText(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x18 - 0x0c];
    int unknown18;                            // Inferred role: open flag; original member name unknown.
    GfMenuObjCommonText *m_menuObjCommonText; // Inferred role: owner; original member name unknown.
  };
  class ErrorListener : public ui::UIObjectListener {
  public:
    ErrorListener(GfMenuObjCommonText *owner) : _0c(), unknown18(0), m_menuObjCommonText(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x18 - 0x0c];
    int unknown18;                            // Inferred role: open flag; original member name unknown.
    GfMenuObjCommonText *m_menuObjCommonText; // Inferred role: owner; original member name unknown.
  };
  class GetItemListener : public ui::UIObjectListener {
  public:
    GetItemListener(GfMenuObjCommonText *owner) : _0c(), unknown18(0), m_menuObjCommonText(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x18 - 0x0c];
    int unknown18;                            // Inferred role: open flag; original member name unknown.
    GfMenuObjCommonText *m_menuObjCommonText; // Inferred role: owner; original member name unknown.
  };
  // The members that reciveEvent (1.0.0: 0x710043d188) reads or writes, and the owner and the zeroed range that the constructor inlined in GfMenuObjCommonText::initialize (0x710043c558) stores.
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjCommonText *owner) : unknown0c(0), unknown10(0), _14(), m_menuObjCommonText(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u32 unknown0c; // Inferred role: input group priority saved while a window is open; original member name unknown.
    u32 unknown10; // Inferred role: type of the open window, 0xff for none; original member name unknown.
    u8 _14[0x1c - 0x14];
    GfMenuObjCommonText *m_menuObjCommonText; // Inferred role: owner; original member name unknown.
  };
  class NumSelectListener : public ui::UIObjectListener {
  public:
    NumSelectListener(GfMenuObjCommonText *owner) : _0c(), unknown18(0), m_menuObjCommonText(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x18 - 0x0c];
    int unknown18;                            // Inferred role: open flag; original member name unknown.
    GfMenuObjCommonText *m_menuObjCommonText; // Inferred role: owner; original member name unknown.
  };
  class OwnerChangeListener : public ui::UIObjectListener {
  public:
    OwnerChangeListener(GfMenuObjCommonText *owner) : _0c(), unknown18(0), m_menuObjCommonText(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x18 - 0x0c];
    int unknown18;                            // Inferred role: open flag; original member name unknown.
    GfMenuObjCommonText *m_menuObjCommonText; // Inferred role: owner; original member name unknown.
  };
  // The next three listeners are declared for the constructors inlined in GfMenuObjCommonText::initialize (zeroed range 0x0c to 0x1c, owner at 0x20). The members that their reciveEvent read or write
  // are named (open flag at 0x18 in all three, the event parameter at 0x0c in SelectListener); the rest of the zeroed range is only stored by the constructor.
  class MerListener : public ui::UIObjectListener {
  public:
    MerListener(GfMenuObjCommonText *owner) : _0c(), unknown18(0), m_menuObjCommonText(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x18 - 0x0c];
    int unknown18;                            // Inferred role: open flag; original member name unknown.
    GfMenuObjCommonText *m_menuObjCommonText; // Inferred role: owner; original member name unknown.
  };
  class KizunaListener : public ui::UIObjectListener {
  public:
    KizunaListener(GfMenuObjCommonText *owner) : _0c(), unknown18(0), m_menuObjCommonText(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x18 - 0x0c];
    int unknown18;                            // Inferred role: open flag; original member name unknown.
    GfMenuObjCommonText *m_menuObjCommonText; // Inferred role: owner; original member name unknown.
  };
  class SelectListener : public ui::UIObjectListener {
  public:
    SelectListener(GfMenuObjCommonText *owner) : unknown0c(0), _10(), unknown18(0), m_menuObjCommonText(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    int unknown0c; // Inferred role: parameter of the open event, tested against zero by the next events; original member name unknown.
    u8 _10[0x18 - 0x10];
    int unknown18;                            // Inferred role: open flag; original member name unknown.
    GfMenuObjCommonText *m_menuObjCommonText; // Inferred role: owner; original member name unknown.
  };
  static int setFadeOut(u32 handle);
  void initialize() override;
  void finalize() override;
  void update() override;
  struct OpenKizunaParam {
    u8 *unknown00; // Inferred role: bdat; original member name unknown.
    u32 unknown08; // Inferred role: text id; original member name unknown.
    u32 unknown0c; // Inferred role: condition; original member name unknown.
  };
  struct OpenNumSelectParam {
    OpenNumSelectParam() : unknown00(0), unknown04(0), unknown08(0), unknown0c(0) {}

    u32 unknown00; // Inferred role: first value of the number selection; original member name unknown.
    u32 unknown04; // Inferred role: second value of the number selection; original member name unknown.
    u32 unknown08; // Inferred role: third value of the number selection; original member name unknown.
    u32 unknown0c; // Inferred role: fourth value of the number selection; original member name unknown.
  };

  static void close();
  static void setupDialog(u32 handle);
  static void open(GfMenuCallContext *context, const MenuCommonWindowParam &param);
  static void open(GfMenuCallContext *context, u32 window, u32 param);
  static void openError(GfMenuCallContext *context, u32 error, u32 param);
  static void openItem(GfMenuCallContext *context, u32 window, u32 item);
  static void openMissionStop(GfMenuCallContext *context, u32 mission, u32 param);
  static void openSelectItem(GfMenuCallContext *context, const GfMenuItemList *list);
  static void openDrChange(GfMenuCallContext *context, u32 driver, const GfMenuDriverList *list);
  static void openGetItem(GfMenuCallContext *context, const GfMenuItemList *items);
  static void openSubMenu(GfMenuCallContext *context, const GfMenuIDList *list);
  static void openKizunaDialog(GfMenuCallContext *context, const OpenKizunaParam &param);
  static void openOwnerChange(GfMenuCallContext *context, u32 driver, u32 other);
  static void openNumSelect(GfMenuCallContext *context, const OpenNumSelectParam &param);

  static GfMenuItemList *s_pItemList;
  static GfMenuIDList *s_pSubMenuIDList;
  static GfMenuDriverList *s_pChangeDrList;

  u8 _24[0x28 - 0x24];
  ui::UICtrlCursorSelect *unknown28; // Inferred role: dialog cursor; original member name unknown.
  // 0x30, 0x38 and 0x60 are released by the destructor (0x710043bf04). MerListener::reciveEvent stores the UISelectObjList it creates at 0x30 and the cursor created over it at 0x38;
  // KizunaListener::reciveEvent stores its UISelectObjList at 0x60.
  ui::UISelectObjList *unknown30;                         // Inferred role: mercenary dialog objects; original member name unknown.
  ui::UICtrlCursorSelect *unknown38;                      // Inferred role: mercenary dialog cursor; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown40; // Inferred role: reference number; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown48; // Inferred role: reference number; original member name unknown.
  GfMenuBladeList *m_menuBladeList;                       // Inferred role: blade list; original member name unknown.
  GfMenuDriverList *unknown58;                            // Inferred role: driver list; original member name unknown.
  ui::UISelectObjList *unknown60;                         // Inferred role: kizuna dialog objects; original member name unknown.
  ui::UISelectObjList *unknown68;                         // Inferred role: driver change objects; original member name unknown.
  ui::UICtrlCursorSelect *unknown70;                      // Inferred role: driver change cursor; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown78; // Inferred role: selected number; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown80; // Inferred role: total price; original member name unknown.
  int unknown88;                                          // Inferred role: unit price; original member name unknown.
};

static_assert(offsetof(GfMenuObjCommonText::DialogListener, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjCommonText::DialogListener, m_menuObjCommonText) == 0x20, "");
static_assert(offsetof(GfMenuObjCommonText::MainListener, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjCommonText::MainListener, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuObjCommonText::DrChangeListener, m_menuObjCommonText) == 0x20, "");
static_assert(offsetof(GfMenuObjCommonText::ErrorListener, m_menuObjCommonText) == 0x20, "");
static_assert(offsetof(GfMenuObjCommonText::GetItemListener, m_menuObjCommonText) == 0x20, "");
static_assert(offsetof(GfMenuObjCommonText::NumSelectListener, m_menuObjCommonText) == 0x20, "");
static_assert(offsetof(GfMenuObjCommonText::OwnerChangeListener, m_menuObjCommonText) == 0x20, "");
static_assert(offsetof(GfMenuObjCommonText::MerListener, m_menuObjCommonText) == 0x20, "");
static_assert(offsetof(GfMenuObjCommonText::KizunaListener, m_menuObjCommonText) == 0x20, "");
static_assert(offsetof(GfMenuObjCommonText::SelectListener, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjCommonText::SelectListener, m_menuObjCommonText) == 0x20, "");
static_assert(offsetof(GfMenuObjCommonText::MainListener, m_menuObjCommonText) == 0x20, "");
static_assert(offsetof(GfMenuObjCommonText, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjCommonText, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjCommonText, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjCommonText, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjCommonText, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjCommonText, m_menuBladeList) == 0x50, "");
static_assert(offsetof(GfMenuObjCommonText, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuObjCommonText, unknown60) == 0x60, "");
static_assert(offsetof(GfMenuObjCommonText, unknown68) == 0x68, "");
static_assert(offsetof(GfMenuObjCommonText, unknown70) == 0x70, "");
static_assert(offsetof(GfMenuObjCommonText, unknown78) == 0x78, "");
static_assert(offsetof(GfMenuObjCommonText, unknown80) == 0x80, "");
static_assert(offsetof(GfMenuObjCommonText, unknown88) == 0x88, "");

} // namespace gf
