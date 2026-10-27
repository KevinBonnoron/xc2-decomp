#include "dr/dr_env_coli_parameter.h"

#include "dr/dr_env_coli_obj.h"

namespace ml {

struct unknown001 {
  u8 _00[0x04];
  s32 unknown04; // Inferred role: post parameter index; original member name unknown.
  u8 _08[0x18 - 0x08];
  u32 unknown18; // Inferred role: post parameters offset; original member name unknown.
};

DrEnvColiParameter::DrEnvColiParameter(DrEnvColiObj *object, DrEnvColiResult *result, DrMan *man, DrEnvColiMan *coliMan) {
  unknown10 = result;
  unknown18 = object;
  unknown00 = man;
  unknown08 = coliMan;
  unknown20 = static_cast<const u8 *>(object->unknown10) + static_cast<const unknown001 *>(object->unknown10)->unknown18;
  unknown28 = static_cast<const unknown001 *>(object->unknown10)->unknown04;
}

DrEnvColiParameter::~DrEnvColiParameter() {}

} // namespace ml
