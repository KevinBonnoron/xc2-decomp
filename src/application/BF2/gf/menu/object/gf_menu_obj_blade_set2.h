#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjBladeSet2 : public GfMenuObject {
public:
  static void sendEvent(u32 handle, u32 type, u32 param, f32 delay);
  void initialize() override;
  void finalize() override;
};

} // namespace gf
