#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrResEtcParams {
public:
  void setParams(f32 value);
  void setPreParams(f32 value);
  void setInitParams(f32 value);
  f32 getValParams() const;

  u8 _00[0x18 - 0x00];
};

static_assert(sizeof(DrResEtcParams) == 0x18, "");

struct DrResEtcPamName {
  u32 nameOffset;
  u8 _04[0x10 - 0x04];
};

static_assert(sizeof(DrResEtcPamName) == 0x10, "");

class DrResEtcPamObj {
public:
  const char *m_names;
  const DrResEtcPamName *m_nameTable;
  DrResEtcParams *m_params;
  u32 m_paramsMax;
  u32 m_flags;
};

static_assert(offsetof(DrResEtcPamObj, m_params) == 0x10, "");
static_assert(offsetof(DrResEtcPamObj, m_paramsMax) == 0x18, "");
static_assert(offsetof(DrResEtcPamObj, m_flags) == 0x1c, "");

} // namespace ml
