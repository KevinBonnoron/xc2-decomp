#include "gf/menu/object/gf_menu_obj_option.h"

namespace gf {

void GfMenuObjOption::finalize() { GfMenuObject::finalize(); }

int GfMenuObjOption::getVolumeValue(u8 level, u8 levelMax) {
  f32 volume = (1.0f / levelMax) * level;
  if (volume > 1.0f) {
    volume = 1.0f;
  }
  return static_cast<int>(volume * 255.0f);
}

u32 GfMenuObjOption::getGammaValue(u8 level, u8 levelMax) {
  u32 value = 0xff;
  if (level != levelMax) {
    u32 scaled = static_cast<int>((static_cast<f32>(level) / levelMax) * 256.0f);
    if (scaled < 0x100) {
      value = scaled;
    }
  }
  return value;
}

} // namespace gf
