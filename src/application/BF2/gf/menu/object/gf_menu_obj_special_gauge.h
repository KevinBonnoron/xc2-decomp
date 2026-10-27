#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {

class GfMenuObjSpecialGauge : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;
  static void push();
};

} // namespace gf
