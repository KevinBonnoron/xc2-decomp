#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjItemList2 : public GfMenuObject {
public:
  static void sendEvent(u32 handle, u32 type, u32 param, u32 delay);
  void initialize() override;
  void finalize() override;
  void update() override;
  static void setFadeOutSub(u32 handle);
};

} // namespace gf
