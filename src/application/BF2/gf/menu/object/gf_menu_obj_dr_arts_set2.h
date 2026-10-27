#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace ui {
class UIObjectAcc;
} // namespace ui

namespace gf {

class GfMenuObjDrArtsSet2 : public GfMenuObject {
public:
  static void moveRight(ui::UIObjectAcc &acc);
  static void moveLeft(ui::UIObjectAcc &acc);
  static void sendEvent(u32 handle, u32 type, u32 param);
  void initialize() override;
  void finalize() override;
};

} // namespace gf
