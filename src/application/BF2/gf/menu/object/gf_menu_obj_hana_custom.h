#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {

class GfMenuObjHanaCustom : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;
};

} // namespace gf
