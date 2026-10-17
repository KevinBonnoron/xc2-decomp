#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
class DrEnvColiMan;
class DrEnvironmentObj;

class DrEnvironmentMan {
public:
  DrEnvironmentObj *createObj(const void *data);

  u8 _00[0x18 - 0x00];
  DrEnvColiMan *m_envColiMan;
};

static_assert(offsetof(DrEnvironmentMan, m_envColiMan) == 0x18, "");

} // namespace ml
