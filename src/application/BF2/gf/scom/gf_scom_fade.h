#pragma once
#include "types.h"

namespace mm {
struct Col4;
} // namespace mm

namespace gf {

class SCOM_FADE {
public:
  static void create(u32 channel, u32 frame, const mm::Col4 &color);
};

} // namespace gf
