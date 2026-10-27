#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjHanaPartsCrystal : public GfMenuObject {
public:
  static void sendEvent(u32 handle, u32 type, u32 param);
  void initialize() override;
  void finalize() override;
  void update() override;
  static u32 getCrystalItemCount(u32 item);
};

} // namespace gf
