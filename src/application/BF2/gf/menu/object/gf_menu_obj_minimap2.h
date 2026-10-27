#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {

class GfMenuObjMinimap2 : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;
};

} // namespace gf
