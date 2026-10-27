#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {

class GfMenuObjBladeName : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;
  static void close();
};

} // namespace gf
