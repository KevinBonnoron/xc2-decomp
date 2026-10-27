#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {

class GfMenuObjMercenaryRoot : public GfMenuObject {
public:
  static void closeBg();
  void initialize() override;
  void finalize() override;
};

} // namespace gf
