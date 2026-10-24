#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
class DrPixlMan;

class DrPixlShadowCacheMan {
public:
  bool isShadowMap() const;
  void callShadowCacheUpdate(bool isAll);
  void callShadowCacheVariance();
  void callFgShadowCacheUpdate();
  void shadowCacheRender();
  void fastRender();
  void endMode();

  u32 unknown00;        // Inferred role: flags; original member name unknown.
  DrPixlMan *unknown08; // Inferred role: pixl man; original member name unknown.
};

static_assert(offsetof(DrPixlShadowCacheMan, unknown08) == 0x8, "");

} // namespace ml
