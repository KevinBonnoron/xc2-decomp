#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjOption : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;

  static int getVolumeValue(u8 level, u8 levelMax);
  static u32 getGammaValue(u8 level, u8 levelMax);
};

} // namespace gf
