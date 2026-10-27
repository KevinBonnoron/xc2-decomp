#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace ui {
class UIObjectAcc;
} // namespace ui

namespace gf {

class GfMenuObjSkipTime : public GfMenuObject {
public:
  static void rotHand(ui::UIObjectAcc &acc, u32 value);
  static void sendEvent(u32 handle, u32 type, u32 param);
  void initialize() override;
  void finalize() override;
  void update() override;
};

} // namespace gf
