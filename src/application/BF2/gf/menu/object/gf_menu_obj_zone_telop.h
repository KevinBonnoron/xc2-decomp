#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjZoneTelop : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;
  static void open(GfMenuCallContext *context, u16 zone);
  static void close(f32 wait);
};

} // namespace gf
