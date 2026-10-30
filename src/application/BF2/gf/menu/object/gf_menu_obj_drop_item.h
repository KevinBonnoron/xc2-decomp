#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {

class GfMenuObjDropItem : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;
  void update() override;
  static void closeAll();
};

} // namespace gf
