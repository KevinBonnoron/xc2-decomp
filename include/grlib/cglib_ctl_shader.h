#pragma once
#include "types.h"

namespace grlib {
class CGLibDecShader;
class CGLibDecShdExtTbl;
class CGLibVtxFetch;

class CGLibCtlShader {
public:
  static void setShader(CGLibDecShader &shader, CGLibVtxFetch &fetch);
  static void setShader(CGLibDecShdExtTbl &shader, CGLibVtxFetch &fetch);
  static void setMemoryBarrierBit(u32 bits);
};

} // namespace grlib
