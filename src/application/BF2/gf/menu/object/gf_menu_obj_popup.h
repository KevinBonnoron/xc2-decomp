#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {

class GfMenuObjPopup : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;
  static void closeAll();
};

} // namespace gf
