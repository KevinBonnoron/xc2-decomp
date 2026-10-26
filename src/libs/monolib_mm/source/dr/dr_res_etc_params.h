#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrResEtcParams {
public:
  DrResEtcParams();
  void setParams(f32 value);
  void setPreParams(f32 value);
  void setInitParams(f32 value);
  f32 getValParams() const;
  f32 getParams() const;

  u16 unknown00; // Inferred role: param flags; original member name unknown.
  u8 _02[0x04 - 0x02];
  f32 unknown04; // Inferred role: params; original member name unknown.
  f32 unknown08; // Inferred role: params; original member name unknown.
  f32 unknown0c; // Inferred role: params; original member name unknown.
  f32 unknown10; // Inferred role: params; original member name unknown.
  f32 unknown14; // Inferred role: params; original member name unknown.
};

static_assert(offsetof(DrResEtcParams, unknown00) == 0x00, "");
static_assert(offsetof(DrResEtcParams, unknown04) == 0x04, "");
static_assert(offsetof(DrResEtcParams, unknown14) == 0x14, "");
static_assert(sizeof(DrResEtcParams) == 0x18, "");

struct DrResEtcPamName {
  u32 unknown00; // Inferred role: name offset; original member name unknown.
  u8 _04[0x10 - 0x04];
};

static_assert(sizeof(DrResEtcPamName) == 0x10, "");

class DrResEtcPamObj {
public:
  ~DrResEtcPamObj();
  static void release(DrResEtcPamObj *&obj);

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
