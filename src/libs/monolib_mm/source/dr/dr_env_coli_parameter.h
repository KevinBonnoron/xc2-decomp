#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrEnvColiMan;
class DrEnvColiObj;
class DrMan;
struct DrEnvColiResult;

template <int Version> struct EnvColiPostParameterVer;

class DrEnvColiParameter {
public:
  DrEnvColiParameter(DrEnvColiObj *object, DrEnvColiResult *result, DrMan *man, DrEnvColiMan *coliMan);
  ~DrEnvColiParameter();
  static void updateBloomParams();
  void resetToneMapParams(const EnvColiPostParameterVer<10006> *from, const EnvColiPostParameterVer<10006> *to, f32 ratio);
  void calcPostEffectParams(bool isReset);
  void calcParams(u32 index, s32 num, bool isReset);

  DrMan *unknown00;           // Inferred role: dr manager; original member name unknown.
  DrEnvColiMan *unknown08;    // Inferred role: env coli manager; original member name unknown.
  DrEnvColiResult *unknown10; // Inferred role: result; original member name unknown.
  DrEnvColiObj *unknown18;    // Inferred role: env coli object; original member name unknown.
  const u8 *unknown20;        // Inferred role: post parameters; original member name unknown.
  s32 unknown28;              // Inferred role: post parameter index; original member name unknown.
};

static_assert(offsetof(DrEnvColiParameter, unknown00) == 0x00, "");
static_assert(offsetof(DrEnvColiParameter, unknown08) == 0x08, "");
static_assert(offsetof(DrEnvColiParameter, unknown10) == 0x10, "");
static_assert(offsetof(DrEnvColiParameter, unknown18) == 0x18, "");
static_assert(offsetof(DrEnvColiParameter, unknown20) == 0x20, "");
static_assert(offsetof(DrEnvColiParameter, unknown28) == 0x28, "");

} // namespace ml
