#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {

class GfMenuObjCmnStatus : public GfMenuObject {
public:
  void initialize() override;
  void update() override;
  static bool isOpenDrStatus();
  static bool isOpenBlStatus();

  static bool s_DispFlag[2];
};

} // namespace gf
