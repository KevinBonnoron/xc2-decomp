#pragma once
#include <stddef.h>

#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {
class DrEnvColiObj;

struct DrEnvColiResult {
  s32 unknown00; // Inferred role: bgm id; original member name unknown.
  s32 unknown04; // Inferred role: layer id; original member name unknown.
  s32 unknown08; // Inferred role: reverb id; original member name unknown.
  s32 unknown0c; // Inferred role: cave id; original member name unknown.
  s32 unknown10; // Inferred role: area id; original member name unknown.
  u8 _14[0x18 - 0x14];
  s32 unknown18; // Inferred role: wind id; original member name unknown.
  u8 : 2;
  u8 unknown1c_2 : 1; // Inferred role: room; original member name unknown.
};

static_assert(offsetof(DrEnvColiResult, unknown18) == 0x18, "");

class DrEnvColiMan {
public:
  DrEnvColiObj *createObj(const void *data);
  bool testEnvColi(DrEnvColiResult *result, const mm::Vec3 &position, f32 radius);

  u8 _00[0x48 - 0x00];
  DrEnvColiResult unknown48; // Inferred role: result; original member name unknown.
};

static_assert(offsetof(DrEnvColiMan, unknown48) == 0x48, "");

} // namespace ml
