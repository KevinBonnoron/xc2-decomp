#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace ui {
class UIObjectAcc;
} // namespace ui

namespace gf {

class GfMenuObjBlKizunaRing : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;
  static bool isLockPos(int index);
  static bool isScreenLR(u32 screen);
  static void setupCircle(ui::UIObjectAcc &);
};

} // namespace gf
