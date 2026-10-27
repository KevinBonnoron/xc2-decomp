#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace ui {
class UIObjectAcc;
} // namespace ui

namespace gf {

class GfMenuObjMercenaries : public GfMenuObject {
public:
  static void setupLocationSelect(ui::UIObjectAcc &acc);
  static void sendEvent(u32 handle, u32 type, u32 param);
  void initialize() override;
  void finalize() override;
};

} // namespace gf
