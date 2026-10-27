#pragma once
#include "grlib/cglib_buff_fix_alloc.h"
#include "types.h"

namespace grlib {

class CGLibBuffOcclusion_plf {
public:
  static u32 createPlf(u32 num, u8 *buffer);
  static int getBufferSize();
  static void releasePlf();
};

class CGLibBuffOcclusion : public CGLibBuffFixAlloc, public CGLibBuffOcclusion_plf {
public:
  CGLibBuffOcclusion();
  ~CGLibBuffOcclusion();
  void release();
  void createOcclusion(u32 num);
};

static_assert(sizeof(CGLibBuffOcclusion) == 0x28, "");

} // namespace grlib
