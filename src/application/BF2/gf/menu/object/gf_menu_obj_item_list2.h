#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjItemList2 : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;
  void update() override;
  static void setFadeOutSub(u32 handle);
};

} // namespace gf
