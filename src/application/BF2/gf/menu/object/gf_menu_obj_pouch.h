#pragma once
#include "gf/menu/gf_menu_object.h"

namespace ui {
class UIObjectAcc;
} // namespace ui

namespace gf {

class GfMenuObjPouch : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;
  void update() override;
  static void setupPouch(ui::UIObjectAcc &);
};

} // namespace gf
