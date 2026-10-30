#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {

class GfMenuObjComboRoute : public GfMenuObject {
public:
  static void close();
  static void disp(bool isDisp);
  static void open();
  void initialize() override;
  void finalize() override;
  void update() override;
};

} // namespace gf
