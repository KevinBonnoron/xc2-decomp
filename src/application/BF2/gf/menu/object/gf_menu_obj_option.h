#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

struct SDataOption;

class GfMenuObjOption : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;

  static void initOptionData(SDataOption &option);
  static int getVolumeValue(u8 level, u8 levelMax);
  static u32 getGammaValue(u8 level, u8 levelMax);
};

} // namespace gf
