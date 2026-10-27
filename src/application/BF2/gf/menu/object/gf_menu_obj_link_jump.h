#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {

class GfMenuObjLinkJump : public GfMenuObject {
public:
  void initialize() override;
  void update() override;
  static void close();
};

} // namespace gf
