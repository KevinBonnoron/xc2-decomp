#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjEvTheater : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;
  void update() override;
  static void fadeout(GfMenuCallContext *context);
  static void fadein(GfMenuCallContext *context);
};

} // namespace gf
