#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {

class GfMenuObjSort : public GfMenuObject {
public:
  static void close();
  void initialize() override;
  void finalize() override;
};

} // namespace gf
