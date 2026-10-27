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
  void clear();

  DrEnvColiObj *unknown00[2]; // Inferred role: object list (first and last); original member name unknown.
  DrEnvColiObj *unknown10[2]; // Inferred role: object list (first and last); original member name unknown.
  DrEnvColiObj *unknown20[2]; // Inferred role: object list (first and last); original member name unknown.
  u8 _30[0x48 - 0x30];
  DrEnvColiResult unknown48; // Inferred role: result; original member name unknown.
};

static_assert(offsetof(DrEnvColiMan, unknown10) == 0x10, "");
static_assert(offsetof(DrEnvColiMan, unknown20) == 0x20, "");
static_assert(offsetof(DrEnvColiMan, unknown48) == 0x48, "");

} // namespace ml
