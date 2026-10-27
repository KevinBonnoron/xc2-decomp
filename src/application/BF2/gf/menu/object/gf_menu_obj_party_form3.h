#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace ui {
class UIObjectAcc;
} // namespace ui

namespace gf {

class GfMenuObjPartyForm3 : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;
  static void setupBGLayout(ui::UIObjectAcc &, u32, bool);
};

} // namespace gf
