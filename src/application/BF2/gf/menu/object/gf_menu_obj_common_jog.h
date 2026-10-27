#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjCommonJog : public GfMenuObject {
public:
  void initialize() override;
  void update() override;
  static void pop(GfMenuCallContext *context);
  static void enable(GfMenuCallContext *context);
  static void disable(GfMenuCallContext *context);
  static void close(GfMenuCallContext *context);
};

} // namespace gf
