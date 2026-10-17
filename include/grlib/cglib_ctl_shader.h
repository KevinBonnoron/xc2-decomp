#pragma once
#include "types.h"

namespace grlib {
class CGLibDecShader;
class CGLibDecShdExtTbl;
class CGLibVtxFetch;

enum GrlUtilVertFetch {};

class CGLibCtlShader {
public:
  static void setShader(CGLibDecShader &shader, CGLibVtxFetch &fetch);
  static void setShader(CGLibDecShdExtTbl &shader, CGLibVtxFetch &fetch);
  static void setComputeShader(CGLibDecShader &shader);
  static void setDispatchCompute(u32 groupsX, u32 groupsY, u32 groupsZ);
  static void setMemoryBarrier();
  static void setMemoryBarrierBit(u32 bits);
  static CGLibDecShader *getDecShader();
  static CGLibVtxFetch *getVtxFetch(GrlUtilVertFetch type);
};

} // namespace grlib
