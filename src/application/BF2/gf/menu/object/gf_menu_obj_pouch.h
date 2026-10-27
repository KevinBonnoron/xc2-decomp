#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace ui {
class UIObjectAcc;
} // namespace ui

namespace gf {

class GfMenuObjPouch : public GfMenuObject {
public:
  static void sendEvent(u32 handle, u32 type, u32 param);
  void initialize() override;
  void finalize() override;
  void update() override;
  static void setupPouch(ui::UIObjectAcc &);
};

} // namespace gf
