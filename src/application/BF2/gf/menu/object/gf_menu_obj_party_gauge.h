#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {

class GfMenuObjPartyGauge : public GfMenuObject {
public:
  static void close();
  static void disp(bool isDisp);
  void initialize() override;
  void finalize() override;
};

} // namespace gf
