#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UICtrlCursorSelect;
class UIObjectAcc;
} // namespace ui

namespace gf {
class GfMenuBladeList;
class GfMenuCallContext;

class GfMenuObjBladeSet : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjBladeSet *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjBladeSet *unknown20; // Inferred role: owner; original member name unknown.
  };

  class BladeSelectListener : public ui::UIObjectListener {
  public:
    BladeSelectListener(GfMenuObjBladeSet *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjBladeSet *unknown20; // Inferred role: owner; original member name unknown.
  };

  class FormListener : public ui::UIObjectListener {
  public:
    FormListener(GfMenuObjBladeSet *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjBladeSet *unknown20; // Inferred role: owner; original member name unknown.
  };

  class FormSlotListener : public ui::UIObjectListener {
  public:
    FormSlotListener(GfMenuObjBladeSet *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjBladeSet *unknown20; // Inferred role: owner; original member name unknown.
  };

  class PreviewListener : public ui::UIObjectListener {
  public:
    PreviewListener(GfMenuObjBladeSet *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjBladeSet *unknown20; // Inferred role: owner; original member name unknown.
  };

  class ReleaseListener : public ui::UIObjectListener {
  public:
    ReleaseListener(GfMenuObjBladeSet *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjBladeSet *unknown20; // Inferred role: owner; original member name unknown.
  };

  class ReleaseSlotListener : public ui::UIObjectListener {
  public:
    ReleaseSlotListener(GfMenuObjBladeSet *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjBladeSet *unknown20; // Inferred role: owner; original member name unknown.
  };

  class MercenariesListener : public ui::UIObjectListener {
  public:
    MercenariesListener(GfMenuObjBladeSet *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjBladeSet *unknown20; // Inferred role: owner; original member name unknown.
  };

  class MercenariesSlotListener : public ui::UIObjectListener {
  public:
    MercenariesSlotListener(GfMenuObjBladeSet *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjBladeSet *unknown20; // Inferred role: owner; original member name unknown.
  };

  class MercenariesSlotBlListener : public ui::UIObjectListener {
  public:
    MercenariesSlotBlListener(GfMenuObjBladeSet *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjBladeSet *unknown20; // Inferred role: owner; original member name unknown.
  };

  class MercenariesSlotMenuListener : public ui::UIObjectListener {
  public:
    MercenariesSlotMenuListener(GfMenuObjBladeSet *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjBladeSet *unknown20; // Inferred role: owner; original member name unknown.
  };

  class MercenariesPreviewListener : public ui::UIObjectListener {
  public:
    MercenariesPreviewListener(GfMenuObjBladeSet *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjBladeSet *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjBladeSet(u32 handle);
  ~GfMenuObjBladeSet() override;
  enum eMode {
    eMode_UNKNOWN_0,
    eMode_UNKNOWN_1,
    eMode_UNKNOWN_2,
  };

  static bool checkBladeRelease(u32 blade);
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle);
  static int setFadeOut(u32 handle);
  static u32 setEmptyTeamId();
  static bool isMenuBtnEnable(int menu, u32 blade, const GfMenuBladeList *list);
  static bool checkBladeSet(u32 unknown, u32 blade, GfMenuBladeList *list);
  static void setupFormSlot(ui::UIObjectAcc &acc, const GfMenuBladeList *list);
  static void setMenuBtnStat(int menu, u32 blade, const GfMenuBladeList *list);
  static void setupMercenaries(ui::UIObjectAcc &acc);
  static void createBladeList(eMode mode, int driver, GfMenuBladeList *list);
  static void setupReleaseSlot(ui::UIObjectAcc &acc, const GfMenuBladeList *list);
  static void detailOpen(GfMenuObjBladeSet *object, ui::UIObjectAcc &acc, const char *layout, u32 unknown);
  static void setupMercenariesSlotMenu(ui::UIObjectAcc &acc);
  static void setupMercenariesCondParam(ui::UIObjectAcc &acc, u32 mission, int task, u32 type, const char *format, const char *layoutFormat);
  static void setupMercenariesSlotBl(ui::UIObjectAcc &acc, const GfMenuBladeList *list);
  static void setupBladePreview(ui::UIObjectAcc &acc);
  static bool checkMercenaries(u32 blade, GfMenuBladeList *list);
  static void setCompleteBtnStat(int menu, u32 mission, const GfMenuBladeList *list);
  static void setupBladeSelect(ui::UIObjectAcc &acc, const GfMenuBladeList *list, GfMenuBladeList *slotList);
  static void setupMercenariesPreview(ui::UIObjectAcc &acc, GfMenuBladeList *list);
  static void setupMercenariesCond(ui::UIObjectAcc &acc, u32 mission, GfMenuBladeList *list);
  void initialize() override;
  void finalize() override;
  void update() override;
  struct OpenParam {
    u32 unknown00; // Inferred role: mode; original member name unknown.
    int unknown04; // Role and original member name unknown.
  };

  static void registOpenParam(const OpenParam &);

  int unknown24;  // Role and original member name unknown, cleared by the constructor.
  u32 unknown28;  // Role and original member name unknown, cleared by the constructor.
  u32 unknown2c;  // Role and original member name unknown, cleared by the constructor.
  u32 unknown30;  // Role and original member name unknown, cleared by the constructor.
  bool unknown34; // Role and original member name unknown, cleared by the constructor.
  bool unknown35; // Role and original member name unknown, set by the constructor.
  u8 _36[0x38 - 0x36];
  u32 unknown38; // Role and original member name unknown, cleared by the constructor.
  u8 _3c[0x40 - 0x3c];
  GfMenuCallContext *unknown40;      // Inferred role: call context; original member name unknown.
  GfMenuCallContext *unknown48;      // Inferred role: call context; original member name unknown.
  GfMenuBladeList *unknown50;        // Inferred role: blades; original member name unknown.
  ui::UICtrlCursorSelect *unknown58; // Inferred role: blade cursor; original member name unknown.
  GfMenuBladeList *unknown60;        // Inferred role: blades; original member name unknown.
  ui::UICtrlCursorSelect *unknown68; // Inferred role: blade cursor; original member name unknown.
  GfMenuBladeList *unknown70;        // Inferred role: blades; original member name unknown.
  ui::UICtrlCursorSelect *unknown78; // Inferred role: blade cursor; original member name unknown.
  GfMenuBladeList *unknown80;        // Inferred role: blades; original member name unknown.
  ui::UICtrlCursorSelect *unknown88; // Inferred role: blade cursor; original member name unknown.
};

static_assert(offsetof(GfMenuObjBladeSet::MainListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjBladeSet::MercenariesPreviewListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjBladeSet::ReleaseListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjBladeSet::FormListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjBladeSet::BladeSelectListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjBladeSet::FormSlotListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjBladeSet::PreviewListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjBladeSet::ReleaseSlotListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjBladeSet::MercenariesSlotBlListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjBladeSet::MainListener) == 0x28, "");
static_assert(sizeof(GfMenuObjBladeSet::PreviewListener) == 0x28, "");
static_assert(sizeof(GfMenuObjBladeSet::BladeSelectListener) == 0x28, "");
static_assert(sizeof(GfMenuObjBladeSet::FormListener) == 0x28, "");
static_assert(sizeof(GfMenuObjBladeSet::FormSlotListener) == 0x28, "");
static_assert(sizeof(GfMenuObjBladeSet::ReleaseListener) == 0x28, "");
static_assert(sizeof(GfMenuObjBladeSet::ReleaseSlotListener) == 0x28, "");
static_assert(sizeof(GfMenuObjBladeSet::MercenariesListener) == 0x28, "");
static_assert(sizeof(GfMenuObjBladeSet::MercenariesSlotListener) == 0x28, "");
static_assert(sizeof(GfMenuObjBladeSet::MercenariesSlotBlListener) == 0x28, "");
static_assert(sizeof(GfMenuObjBladeSet::MercenariesSlotMenuListener) == 0x28, "");
static_assert(sizeof(GfMenuObjBladeSet::MercenariesPreviewListener) == 0x28, "");
static_assert(offsetof(GfMenuObjBladeSet::MercenariesSlotListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjBladeSet::MercenariesListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjBladeSet::MercenariesSlotMenuListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjBladeSet::OpenParam, unknown04) == 0x04, "");
static_assert(offsetof(GfMenuObjBladeSet, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjBladeSet, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjBladeSet, unknown2c) == 0x2c, "");
static_assert(offsetof(GfMenuObjBladeSet, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjBladeSet, unknown34) == 0x34, "");
static_assert(offsetof(GfMenuObjBladeSet, unknown35) == 0x35, "");
static_assert(offsetof(GfMenuObjBladeSet, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjBladeSet, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjBladeSet, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjBladeSet, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjBladeSet, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuObjBladeSet, unknown60) == 0x60, "");
static_assert(offsetof(GfMenuObjBladeSet, unknown68) == 0x68, "");
static_assert(offsetof(GfMenuObjBladeSet, unknown70) == 0x70, "");
static_assert(offsetof(GfMenuObjBladeSet, unknown78) == 0x78, "");
static_assert(offsetof(GfMenuObjBladeSet, unknown80) == 0x80, "");
static_assert(offsetof(GfMenuObjBladeSet, unknown88) == 0x88, "");

} // namespace gf
