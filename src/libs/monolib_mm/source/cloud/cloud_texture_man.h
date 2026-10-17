#pragma once
#include "types.h"

namespace cloud {

class CloudTextureMan {
public:
  CloudTextureMan();
  ~CloudTextureMan();
  void createTexture();

  u8 _00[0x20 - 0x00];
};

} // namespace cloud
