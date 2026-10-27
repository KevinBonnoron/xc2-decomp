#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
class DrEnvColiMan;
class DrEnvironmentObj;

class DrEnvironmentMan {
public:
  DrEnvironmentObj *createObj(const void *data);
  void releaseObj(DrEnvironmentObj *obj);

  u8 _00[0x18 - 0x00];
  DrEnvColiMan *unknown18; // Inferred role: env coli man; original member name unknown.
};

static_assert(offsetof(DrEnvironmentMan, unknown18) == 0x18, "");

} // namespace ml
