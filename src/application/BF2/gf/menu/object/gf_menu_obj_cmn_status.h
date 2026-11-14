#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UICtrlRadarGraph;
class UISelectObjList;
} // namespace ui

namespace gf {

class GfMenuObjCmnStatus : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjCmnStatus *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjCmnStatus *unknown20; // Inferred role: owner; original member name unknown.
  };

  class CharStatusListener : public ui::UIObjectListener {
  public:
    CharStatusListener(GfMenuObjCmnStatus *owner) : unknown0c(0), unknown10(0), unknown14(0), unknown18(0), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    int unknown0c; // Inferred role: shown flag; original member name unknown.
    int unknown10; // Inferred role: status type, 0 for the driver and 1 for the blade; original member name unknown.
    u32 unknown14; // Inferred role: side the status slides from; original member name unknown.
    int unknown18; // Inferred role: no selected page flag; original member name unknown.
    u8 _1c[0x20 - 0x1c];
    GfMenuObjCmnStatus *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjCmnStatus(u32 handle);
  ~GfMenuObjCmnStatus() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static bool isOpenDrStatus();
  static bool isOpenBlStatus();
  static void setInputEnable();
  static void setInputDisable();
  static void openDrStatus(u32 driver, int page);
  static void closeDrStatus();
  static void openBlStatus(u32 blade, int page);
  static void closeBlStatus();
  static bool swapDrStatus();
  static bool swapBlStatus();
  void updateBladeBase(u32 page);
  void setBlPageParam(u32 handle);

  static bool s_DispFlag[2];

  u8 _24[0x28 - 0x24];
  ui::UISelectObjList *unknown28[2]; // Inferred role: status objects of the driver and of the blade; original member name unknown.
  ui::UICtrlRadarGraph *unknown38;   // Inferred role: status graph; original member name unknown.
};

static_assert(offsetof(GfMenuObjCmnStatus::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjCmnStatus::MainListener) == 0x28, "");
static_assert(offsetof(GfMenuObjCmnStatus::CharStatusListener, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjCmnStatus::CharStatusListener, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuObjCmnStatus::CharStatusListener, unknown14) == 0x14, "");
static_assert(offsetof(GfMenuObjCmnStatus::CharStatusListener, unknown18) == 0x18, "");
static_assert(offsetof(GfMenuObjCmnStatus::CharStatusListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjCmnStatus::CharStatusListener) == 0x28, "");
static_assert(offsetof(GfMenuObjCmnStatus, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjCmnStatus, unknown38) == 0x38, "");
static_assert(sizeof(GfMenuObjCmnStatus) == 0x40, "");

} // namespace gf
