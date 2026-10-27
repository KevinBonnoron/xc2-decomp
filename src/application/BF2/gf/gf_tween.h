#pragma once
#include <stddef.h>

#include "types.h"

namespace gf {

template <typename T> class TGfTween {
public:
  virtual ~TGfTween() {}

  T unknown08; // Role and original member name unknown.
  T unknown0c; // Role and original member name unknown.
};

class GfSpeedTween : public TGfTween<f32> {
public:
  ~GfSpeedTween() override {}

  f32 unknown10; // Role and original member name unknown.
  f32 unknown14; // Role and original member name unknown.
};

static_assert(offsetof(GfSpeedTween, unknown08) == 0x08, "");
static_assert(offsetof(GfSpeedTween, unknown14) == 0x14, "");
static_assert(sizeof(GfSpeedTween) == 0x18, "");

} // namespace gf
