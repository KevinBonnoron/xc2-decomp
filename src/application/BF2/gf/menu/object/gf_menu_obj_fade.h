#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace mm {
struct Col4;
} // namespace mm

namespace gf {

class GfMenuObjFade : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;
  void update() override;
  static void dispLoading(bool disp, u16 type);
  static void getFadeColor(u8 type, mm::Col4 &color);
};

} // namespace gf
