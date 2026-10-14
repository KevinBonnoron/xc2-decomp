#pragma once
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GfSetupParam;

class GfGameSpeed {
public:
  static void build(const GfSetupParam &param);
  static void setGlobalSpeed(f32 speed);
  static void destroy();
  static void update(const fw::UpdateInfo &info);
  static void clear();
  static f32 getLayerSpeed(u32 layer);
};

} // namespace gf
