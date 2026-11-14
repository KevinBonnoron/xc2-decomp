#pragma once
#include <stddef.h>

#include "types.h"

namespace mm {
struct Mat44;
} // namespace mm

namespace ml {

class DrLightObj;
class DrResEtcParams;
class DrResEtcPamObj;

class DrResMdoLight {
public:
  // Inferred role: resource header holding the offset of the light table; original type name unknown.
  struct unknown001 {
    u8 _00[0x2c];
    u32 unknown2c; // Inferred role: offset of the light table; original member name unknown.
  };

  // Inferred role: light table; original type name unknown.
  struct unknown002 {
    s32 unknown00; // Inferred role: light count; original member name unknown.
  };

  // Inferred role: resource header holding the offset of the light data; original type name unknown.
  struct unknown003 {
    u8 _00[0x30];
    u32 unknown30; // Inferred role: offset of the light data; original member name unknown.
  };

  DrResMdoLight();
  ~DrResMdoLight();
  static void release(DrResMdoLight *&light);
  void release();
  void lgtCreate();
  int setup(u8 *work, const u8 *resource, const u8 *lightResource);
  static int create(u8 *work, const u8 *resource, const u8 *lightResource);
  void update(const mm::Mat44 *prevMatrix, const mm::Mat44 &matrix, DrResEtcPamObj *pamObj, f32 ratio);
  static int calcWorkSize(const u8 *resource);
  void setDisp(bool isDisp);
  static void lgtCall_col_r(f32 *color, DrResEtcParams *params);
  static void lgtCall_col_g(f32 *color, DrResEtcParams *params);
  static void lgtCall_col_b(f32 *color, DrResEtcParams *params);
  static void lgtCall_col_inv(f32 *color, DrResEtcParams *params);

  DrLightObj **unknown00;      // Inferred role: lights; original member name unknown.
  const unknown002 *unknown08; // Inferred role: light table; original member name unknown.
  const u8 *unknown10;         // Inferred role: light data; original member name unknown.
  s16 unknown18;               // Inferred role: light count; original member name unknown.
  u16 unknown1a;               // Inferred role: flags, bit 1 is display; original member name unknown.
  u8 _1c[0x20 - 0x1c];
};

static_assert(offsetof(DrResMdoLight, unknown08) == 0x08, "");
static_assert(offsetof(DrResMdoLight, unknown10) == 0x10, "");
static_assert(offsetof(DrResMdoLight, unknown18) == 0x18, "");
static_assert(offsetof(DrResMdoLight, unknown1a) == 0x1a, "");
static_assert(sizeof(DrResMdoLight) == 0x20, "");

} // namespace ml
