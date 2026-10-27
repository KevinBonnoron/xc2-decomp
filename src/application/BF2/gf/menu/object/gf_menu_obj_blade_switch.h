#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {

class GfMenuObjBladeSwitch : public GfMenuObject {
public:
  static void open();
  static void close();
  void initialize() override;
  void finalize() override;
};

} // namespace gf
