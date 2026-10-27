#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace ui {
class UIObjectAcc;
} // namespace ui

namespace gf {

class GfMenuObjPartyForm3 : public GfMenuObject {
public:
  bool seqWaitOpenEnd();
  struct OpenParam {
    u16 unknown00; // Role and original member name unknown.
  };

  static void registOpenParam(const OpenParam &param);
  static void sendEvent(u32 handle, u32 type, u32 param);
  void initialize() override;
  void finalize() override;
  static void setupBGLayout(ui::UIObjectAcc &, u32, bool);
};

} // namespace gf
