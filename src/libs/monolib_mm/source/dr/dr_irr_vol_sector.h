#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
namespace irrvol {

struct SLightProbe {
  u8 _00[0x50];
};

static_assert(sizeof(SLightProbe) == 0x50, "");

struct SSectorInfo {
  u8 _00[0x40];
  const SLightProbe *unknown40; // Inferred role: probes; original member name unknown.
};

static_assert(offsetof(SSectorInfo, unknown40) == 0x40, "");

struct SCascadeInfo {
  u8 _00[0x20];
  u32 unknown20; // Inferred role: sector parameter; original member name unknown.
};

static_assert(offsetof(SCascadeInfo, unknown20) == 0x20, "");

class DrIrrVolSector {
public:
  DrIrrVolSector(const SSectorInfo *sectorInfo, const SCascadeInfo *cascadeInfo);
  ~DrIrrVolSector();
  const SLightProbe *getProbe(int index) const;

  const SSectorInfo *unknown00; // Inferred role: sector info; original member name unknown.
  u32 unknown08;                // Inferred role: sector parameter; original member name unknown.
};

static_assert(offsetof(DrIrrVolSector, unknown08) == 0x08, "");

} // namespace irrvol
} // namespace ml
