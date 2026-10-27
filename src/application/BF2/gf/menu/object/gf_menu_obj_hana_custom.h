#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace ui {
class UIObjectAcc;
} // namespace ui

namespace gf {

class GfMenuObjHanaCustom : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;
  static u32 convPartsId(u32 partsId);
  static bool isExpandParts(u32 partsId);
  static void refreshPlanLine(ui::UIObjectAcc &);
};

} // namespace gf
