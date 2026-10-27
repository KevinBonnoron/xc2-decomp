#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjBlKizunaRing : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;
  static bool isLockPos(int index);
  static bool isScreenLR(u32 screen);
};

} // namespace gf
