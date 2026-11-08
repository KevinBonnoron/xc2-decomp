#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace ui {
class UICtrlRadarGraph;
class UISelectObjList;
} // namespace ui

namespace gf {

class GfMenuObjCmnStatus : public GfMenuObject {
public:
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

  static bool s_DispFlag[2];

  u8 _24[0x28 - 0x24];
  ui::UISelectObjList *unknown28;  // Inferred role: status objects; original member name unknown.
  ui::UISelectObjList *unknown30;  // Inferred role: status objects; original member name unknown.
  ui::UICtrlRadarGraph *unknown38; // Inferred role: status graph; original member name unknown.
};

static_assert(offsetof(GfMenuObjCmnStatus, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjCmnStatus, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjCmnStatus, unknown38) == 0x38, "");
static_assert(sizeof(GfMenuObjCmnStatus) == 0x40, "");

} // namespace gf
