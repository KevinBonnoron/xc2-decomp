#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjBladeName : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;
  static void open(GfMenuCallContext *context);
  static void close();
};

} // namespace gf
