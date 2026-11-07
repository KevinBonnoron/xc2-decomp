#include "gf/menu/object/gf_menu_obj_option.h"

namespace gf {
class GfMenuCallContext;

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x86;

void GfMenuObjOption::finalize() { GfMenuObject::finalize(); }

void GfMenuObjOption::update() {
  unknown128.unknown003();
  GfMenuObject::update();
}

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

u8 GfMenuObjOption::getVolumeLevel(u8 value, u8 levelMax) {
  u8 level = levelMax;
  if (value != 0xff) {
    f32 step = 255.0f / levelMax;
    f32 volume = value / step;
    level = static_cast<int>(volume + (volume > 0.0f ? 0.5f : -0.5f));
  }
  return level;
}

u8 GfMenuObjOption::getGammaLevel(u16 value, u8 levelMax) {
  u8 level = levelMax;
  if (value != 0xff) {
    f32 ratio = value / 255.0f;
    f32 gamma = levelMax * ratio;
    level = static_cast<int>(gamma + (gamma > 0.0f ? 0.5f : -0.5f));
  }
  return level;
}

bool GfMenuObjOption::attach(GfMenuCallContext *context) { return unknown151(context, unknown001); }

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjOption>(const mm::mtl::Delegate<bool()> *);
