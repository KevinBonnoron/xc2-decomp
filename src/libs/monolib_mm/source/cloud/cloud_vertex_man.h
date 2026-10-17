#pragma once
#include "types.h"

namespace cloud {

class CloudVertexMan {
public:
  CloudVertexMan();
  ~CloudVertexMan();

  u8 _00[0x90 - 0x00];
};

} // namespace cloud
