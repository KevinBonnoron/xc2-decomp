#pragma once
#include "types.h"

namespace grlib {

class CGLibShader {
public:
  CGLibShader();
  int getTextureLocation(const char *name) const;
  int getUniformBlockOfs(const char *name) const;

  u8 _00[0xd8 - 0x00];
};

static_assert(sizeof(CGLibShader) == 0xd8, "");

} // namespace grlib
