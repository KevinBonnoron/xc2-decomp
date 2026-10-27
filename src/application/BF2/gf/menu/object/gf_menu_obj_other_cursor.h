#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {

class GfMenuObjOtherCursor : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;
  static void disp(bool disp);
};

} // namespace gf
