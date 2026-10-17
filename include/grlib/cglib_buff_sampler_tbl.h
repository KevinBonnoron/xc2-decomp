#pragma once
#include "types.h"

namespace grlib {

class CGLibBuffResSamObj;
struct CGLibWkrSamplerParams;

class CGLibBuffSamplerTbl {
public:
  CGLibBuffResSamObj *allocSampler(const CGLibWkrSamplerParams &params);
  void freeSampler(CGLibBuffResSamObj *&sampler);

  u8 _000[0x830 - 0x000];
};

static_assert(sizeof(CGLibBuffSamplerTbl) == 0x830, "");

} // namespace grlib
