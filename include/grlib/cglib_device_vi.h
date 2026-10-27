#pragma once
#include "types.h"

namespace grlib {

class CGLibDeviceVI {
public:
  CGLibDeviceVI();
  ~CGLibDeviceVI();
  void update();

  u8 _00[0x20];
};

static_assert(sizeof(CGLibDeviceVI) == 0x20, "");

} // namespace grlib
