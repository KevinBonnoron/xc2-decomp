#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace grlib {

class CGLibManager : public mm::mtl::PtrSingleton<CGLibManager> {
public:
  CGLibManager();
  void deviceInit();
  void begin();
  void end();

  static int s_nDblNowIdx;

  u8 _0008[0x5030 - 0x0008];
};

} // namespace grlib
