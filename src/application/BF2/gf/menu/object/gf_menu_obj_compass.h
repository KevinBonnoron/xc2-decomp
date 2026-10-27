#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {

class GfMenuObjCompass : public GfMenuObject {
public:
  static void close();
  static void open();
  void initialize() override;
  void finalize() override;
};

} // namespace gf
