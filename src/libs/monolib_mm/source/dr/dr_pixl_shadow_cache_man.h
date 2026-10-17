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

  u32 m_flags;
  DrPixlMan *m_pixlMan;
};

static_assert(offsetof(DrPixlShadowCacheMan, m_pixlMan) == 0x8, "");

} // namespace ml
