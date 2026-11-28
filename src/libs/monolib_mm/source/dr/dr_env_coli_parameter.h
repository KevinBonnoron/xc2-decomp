#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrEnvColiMan;
class DrEnvColiObj;
class DrMan;
struct DrEnvColiResult;
struct EnvColiPostData;

template <int Version> struct EnvColiPostParameterVer;

class DrEnvColiParameter {
public:
  DrEnvColiParameter(DrEnvColiObj *object, DrEnvColiResult *result, DrMan *man, DrEnvColiMan *coliMan);
  ~DrEnvColiParameter();
  static void updateBloomParams();
  void resetToneMapParams(const EnvColiPostParameterVer<10006> *from, const EnvColiPostParameterVer<10006> *to, f32 ratio);
  void calcPostEffectParams(bool isReset);
  void updateCloudParams(f32 ratio, bool, const EnvColiPostData *from, const EnvColiPostData *to);
  void calcParams(u32 index, s32 num, bool isReset);

  // Names from the game symbols ml::DrEnvColiParameter::ENVCOLI_TIMEVAL and ENVCOLI_TIMEVAL_DIV (0x7100f83bbc, 0x7100f83bc0; also in torna): the minutes of a day and its inverse.
  static constexpr f32 ENVCOLI_TIMEVAL = 1440.0f;
  static constexpr f32 ENVCOLI_TIMEVAL_DIV = 1.0f / 1440.0f;
  DrMan *m_drMan;                     // Inferred role: dr manager; original member name unknown.
  DrEnvColiMan *m_drEnvColiMan;       // Inferred role: env coli manager; original member name unknown.
  DrEnvColiResult *m_drEnvColiResult; // Inferred role: result; original member name unknown.
  DrEnvColiObj *m_drEnvColiObj;       // Inferred role: env coli object; original member name unknown.
  const u8 *unknown20;                // Inferred role: post parameters; original member name unknown.
  s32 unknown28;                      // Inferred role: post parameter version, compared with 10006 by calcParams (0x71007d2e44); original member name unknown.
};

static_assert(offsetof(DrEnvColiParameter, m_drMan) == 0x00, "");
static_assert(offsetof(DrEnvColiParameter, m_drEnvColiMan) == 0x08, "");
static_assert(offsetof(DrEnvColiParameter, m_drEnvColiResult) == 0x10, "");
static_assert(offsetof(DrEnvColiParameter, m_drEnvColiObj) == 0x18, "");
static_assert(offsetof(DrEnvColiParameter, unknown20) == 0x20, "");
static_assert(offsetof(DrEnvColiParameter, unknown28) == 0x28, "");

} // namespace ml
