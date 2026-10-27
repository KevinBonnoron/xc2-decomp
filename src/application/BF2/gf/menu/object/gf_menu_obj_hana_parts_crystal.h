#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjHanaPartsCrystal : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;
  void update() override;
  static u32 getCrystalItemCount(u32 item);
};

} // namespace gf
