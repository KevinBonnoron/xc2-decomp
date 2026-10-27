#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {

class GfMenuObjBladeChange : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;
  static void enableAwakening(bool);
  static void pushBladeChange(unsigned int blade);
};

} // namespace gf
