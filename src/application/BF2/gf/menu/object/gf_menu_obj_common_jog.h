#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {

class GfMenuObjCommonJog : public GfMenuObject {
public:
  void initialize() override;
  void update() override;
};

} // namespace gf
