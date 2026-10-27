#pragma once
#include "gf/menu/gf_menu_object.h"

namespace ui {
class UIObjectAcc;
} // namespace ui

namespace gf {

class GfMenuObjMainMenu2BG : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;
  static void setupMainMenuBG(ui::UIObjectAcc &);
};

} // namespace gf
