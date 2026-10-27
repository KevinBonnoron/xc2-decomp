#pragma once
#include "grlib/cglib_buff_fix_alloc.h"
#include "types.h"

namespace grlib {

class CGLibBuffTexture_plf {
public:
  void createPlf(u32 num, u8 *buffer);
  void releasePlf();

  void *unknown00; // Inferred role: textures; original member name unknown.
};

class CGLibBuffTexture : public CGLibBuffFixAlloc, public CGLibBuffTexture_plf {
public:
  CGLibBuffTexture();
  ~CGLibBuffTexture();
  void release();
  void createTexture(u32 num);
};

static_assert(sizeof(CGLibBuffTexture) == 0x30, "");

} // namespace grlib
