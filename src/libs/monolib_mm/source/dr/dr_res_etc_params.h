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
  void update();
  f32 getValParams() const;
  f32 getParams() const;

  u16 unknown00; // Inferred role: param flags; original member name unknown.
  u8 _02[0x04 - 0x02];
  f32 unknown04[2]; // Inferred role: params per buffer; original member name unknown.
  f32 unknown0c[2]; // Inferred role: pre params per buffer; original member name unknown.
  f32 unknown14;    // Inferred role: current param; original member name unknown.
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
  // Inferred role: model resource header; original type name unknown.
  struct unknown001 {
    u8 _00[0x84];
    u32 unknown84; // Inferred role: offset of the params table; original member name unknown.
  };

  // Inferred role: params table header; original type name unknown.
  struct unknown002 {
    u8 _00[0x04];
    s32 unknown04; // Inferred role: param count; original member name unknown.
  };

  ~DrResEtcPamObj();
  static void release(DrResEtcPamObj *&obj);
  static int calcWorkSize(const u8 *data);

  const char *unknown00;            // Inferred role: names; original member name unknown.
  const DrResEtcPamName *unknown08; // Inferred role: name table; original member name unknown.
  DrResEtcParams *unknown10;        // Inferred role: params; original member name unknown.
  u32 unknown18;                    // Inferred role: params max; original member name unknown.
  u32 unknown1c;                    // Inferred role: flags; original member name unknown.
};

static_assert(offsetof(DrResEtcPamObj::unknown001, unknown84) == 0x84, "");
static_assert(offsetof(DrResEtcPamObj::unknown002, unknown04) == 0x04, "");
static_assert(offsetof(DrResEtcPamObj, unknown10) == 0x10, "");
static_assert(offsetof(DrResEtcPamObj, unknown18) == 0x18, "");
static_assert(offsetof(DrResEtcPamObj, unknown1c) == 0x1c, "");

} // namespace ml
