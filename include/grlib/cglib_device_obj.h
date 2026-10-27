#pragma once
#include <stddef.h>

#include "grlib/cglib_device_vi.h"
#include "nvn/nvn.h"
#include "types.h"

namespace grlib {

class CGLibDeviceObj_plf {
public:
  CGLibDeviceObj_plf();

  NVNdevice unknown00; // Inferred role: device; original member name unknown.
  u8 _3000[0x5000 - 0x3000];
  CGLibDeviceVI unknown5000; // Inferred role: vi; original member name unknown.
};

static_assert(offsetof(CGLibDeviceObj_plf, unknown5000) == 0x5000, "");
static_assert(sizeof(CGLibDeviceObj_plf) == 0x5020, "");

class CGLibDeviceObj : public CGLibDeviceObj_plf {
public:
  CGLibDeviceObj();
  void release();
  void swapChain();
};

} // namespace grlib
