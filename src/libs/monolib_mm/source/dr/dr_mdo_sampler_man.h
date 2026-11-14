#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrMan;
class DrResMdoSampler;

class DrMdoSamplerMan {
public:
  DrMdoSamplerMan(DrMan *drMan);
  ~DrMdoSamplerMan();
  void begin();
  DrResMdoSampler *createSamplerObj(const u8 *data);
  DrResMdoSampler *createSamplerSeamObj(const u8 *data);
  void releaseSamplerObj(DrResMdoSampler *sampler);
  void releaseSamplerSeamObj(DrResMdoSampler *sampler);

  DrResMdoSampler *unknown00; // Inferred role: first sampler; original member name unknown.
  DrResMdoSampler *unknown08; // Inferred role: last sampler; original member name unknown.
  DrMan *unknown10;           // Inferred role: dr man; original member name unknown.
};

static_assert(offsetof(DrMdoSamplerMan, unknown08) == 0x08, "");
static_assert(offsetof(DrMdoSamplerMan, unknown10) == 0x10, "");

} // namespace ml
