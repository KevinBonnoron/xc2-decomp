#pragma once
#include "types.h"

namespace mm {
struct Vec3;
}

namespace gf {

class GfMapManager {
public:
  static void setEnvWeather(u32 weatherType);
  static void setGlobalIBLReferencePos(const mm::Vec3 &position);
};

} // namespace gf
