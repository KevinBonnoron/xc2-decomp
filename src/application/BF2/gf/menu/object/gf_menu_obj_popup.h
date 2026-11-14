#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_many_objects.h"
#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"
#include "ui/ui_object_acc.h"

namespace ui {
class UIObjectNumberPlugin;
} // namespace ui

namespace gf {

class DataParamAcc;

class GfMenuObjPopup : public GfMenuObject {
public:
  // Inferred role: kind of popup (1 arts, 2 pouch, 3 idea, 4 achievement, 5 affinity, 6 develop, 7 mercenary add, 8 mercenary return,
  // 9 quest, 10 crystal); original enum and enumerator names unknown.
  enum unknown005 {
    unknown005_1 = 1,
    unknown005_2 = 2,
    unknown005_3 = 3,
    unknown005_4 = 4,
    unknown005_5 = 5,
    unknown005_6 = 6,
    unknown005_7 = 7,
    unknown005_8 = 8,
    unknown005_9 = 9,
    unknown005_10 = 10,
  };

  // Layout from SCOM_POPUP::SCOM_POPUP (0x71005d1208), which copies it in two 8-byte moves, and the SCOM_POPUP::create* functions.
  struct OpenParam {
    unknown005 unknown00; // Inferred role: kind of popup; original member name unknown.
    u32 unknown04;        // Inferred role: first value, depends on the kind; original member name unknown.
    u32 unknown08;        // Inferred role: second value, depends on the kind; original member name unknown.
    u32 unknown0c;        // Inferred role: third value, depends on the kind; original member name unknown.
  };

  // Queued by GfMenuManyObjects; the game gives it its own vtable, inheriting the dispose of the base. The Queue::erase and push_back
  // instances copy the open parameter in one 16-byte move at 0xc, in the tail padding of the base.
  struct PopupInfo : GfMenuManyObjects::InfoType {
    OpenParam unknown0c; // Inferred role: open parameter of the queued popup; original member name unknown.
  };

  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjPopup *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjPopup *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjPopup(u32 handle);
  ~GfMenuObjPopup() override;
  static void open(const OpenParam &param);
  static void pausePickup();
  static void continuePickup(u32 type);
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle, u32 type);
  static int setFadeOut(u32 handle, u32 type);
  void initialize() override;
  void finalize() override;
  void update() override;
  static void closeAll();
  static void close(u32 handle);
  static void sendOpen(u32 handle, const PopupInfo &info);
  static void setFaceIcon(ui::UIObjectAcc &acc, const DataParamAcc &param);
  static void setFlagIcon(ui::UIObjectAcc &acc, u32 flag);
  static void removeObject(ui::UIObjectAcc acc);

  bool unknown24; // Role and original member name unknown, cleared by the constructor.
  u8 _25[0x28 - 0x25];
  u32 unknown28;                               // Role and original member name unknown, cleared by the constructor.
  ui::UIObjectNumberPlugin *unknown30;         // Inferred role: number plugin of TXT_text@05_1; original member name unknown.
  ui::UIObjectNumberPlugin *unknown38;         // Inferred role: number plugin of TXT_text@05_2; original member name unknown.
  ui::UIObjectNumberPlugin *unknown40;         // Inferred role: number plugin of TXT_text@05_3; original member name unknown.
  ui::UIObjectNumberPlugin *unknown48;         // Inferred role: number plugin of TXT_text@05_4; original member name unknown.
  ui::UIObjectNumberPlugin *unknown50;         // Inferred role: number plugin of TXT_text@09; original member name unknown.
  ui::UIObjectNumberPlugin *unknown58;         // Inferred role: number plugin of TXT_text@11; original member name unknown.
  GfMenuSequence<GfMenuObjPopup, 8> unknown60; // Inferred role: popup steps; original member name unknown.
};

static_assert(offsetof(GfMenuObjPopup::OpenParam, unknown04) == 0x04, "");
static_assert(offsetof(GfMenuObjPopup::OpenParam, unknown08) == 0x08, "");
static_assert(offsetof(GfMenuObjPopup::OpenParam, unknown0c) == 0x0c, "");
static_assert(sizeof(GfMenuObjPopup::OpenParam) == 0x10, "");
static_assert(offsetof(GfMenuObjPopup::PopupInfo, unknown0c) == 0x0c, "");
static_assert(sizeof(GfMenuObjPopup::PopupInfo) == 0x20, "");
static_assert(offsetof(GfMenuObjPopup::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjPopup::MainListener) == 0x28, "");
static_assert(offsetof(GfMenuObjPopup, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjPopup, unknown60) == 0x60, "");
static_assert(sizeof(GfMenuObjPopup) == 0x2f0, "");

} // namespace gf
