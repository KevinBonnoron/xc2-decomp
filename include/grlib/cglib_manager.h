#pragma once
#include <stddef.h>

#include "mm_mtl/singleton.h"
#include "nvn/nvn.h"
#include "types.h"

namespace grlib {

class CGLibManager : public mm::mtl::PtrSingleton<CGLibManager> {
public:
  CGLibManager();
  void deviceInit();
  void begin();
  void end();

  static int s_nDblNowIdx;
  static int s_nTriNowIdx;

  NVNdevice m_device;
  u8 _3008[0x5030 - 0x3008];
};

static_assert(offsetof(CGLibManager, m_device) == 0x8, "");

} // namespace grlib
