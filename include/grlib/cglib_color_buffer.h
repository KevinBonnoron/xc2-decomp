#pragma once
#include <stddef.h>

#include "nvn/nvn.h"
#include "types.h"

struct NVNtexture;

namespace grlib {

class CGLibColorBuffer {
public:
  u8 _00[0x10 - 0x00];
  NVNtextureView m_textureView;
  NVNtexture *m_nvnTexture;
};

static_assert(offsetof(CGLibColorBuffer, m_textureView) == 0x10, "");
static_assert(offsetof(CGLibColorBuffer, m_nvnTexture) == 0x38, "");

} // namespace grlib
