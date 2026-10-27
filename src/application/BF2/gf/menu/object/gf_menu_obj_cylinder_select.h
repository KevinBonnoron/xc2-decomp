#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {

class GfMenuObjCylinderSelect : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;
  void update() override;
};

} // namespace gf
