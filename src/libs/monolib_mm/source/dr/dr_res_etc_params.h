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
  u32 unknown00; // Inferred role: name offset; original member name unknown.
  u8 _04[0x10 - 0x04];
};

static_assert(sizeof(DrResEtcPamName) == 0x10, "");

class DrResEtcPamObj {
public:
  const char *unknown00;            // Inferred role: names; original member name unknown.
  const DrResEtcPamName *unknown08; // Inferred role: name table; original member name unknown.
  DrResEtcParams *unknown10;        // Inferred role: params; original member name unknown.
  u32 unknown18;                    // Inferred role: params max; original member name unknown.
  u32 unknown1c;                    // Inferred role: flags; original member name unknown.
};

static_assert(offsetof(DrResEtcPamObj, unknown10) == 0x10, "");
static_assert(offsetof(DrResEtcPamObj, unknown18) == 0x18, "");
static_assert(offsetof(DrResEtcPamObj, unknown1c) == 0x1c, "");

} // namespace ml
