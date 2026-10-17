#pragma once
#include <stddef.h>

#include "grlib/cglib_buff_fix_alloc.h"
#include "types.h"

namespace grlib {

class CGLibBuffTexture : public CGLibBuffFixAlloc {
public:
  CGLibBuffTexture();
  ~CGLibBuffTexture();
  void release();
  void createTexture(u32 num);

  void *m_textures;
};

static_assert(offsetof(CGLibBuffTexture, m_textures) == 0x28, "");

} // namespace grlib
