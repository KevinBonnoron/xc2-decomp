#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace mm {
struct Col3;
struct Mat44;
} // namespace mm

namespace ml {
class DrLightObjGlobalIBL;

class DrRequetIBL {
public:
  DrRequetIBL(DrLightObjGlobalIBL *light);
  int getTextureNum() const;
  const grlib::CGLibTextureBuffer *getTexture(u32 index) const;
  const mm::Mat44 *getSHMatrix(u32 index, u32 term) const;
  const f32 *getSHTerm(u32 index, u32 term) const;
  f32 getSkyIntensity() const;
  f32 getDirLightIntensity() const;
  const mm::Col3 *getAdditionalAmbient() const;
  int getVersion() const;

  u8 _00[0x18 - 0x00];
  DrLightObjGlobalIBL *unknown18; // Inferred role: light; original member name unknown.
  DrLightObjGlobalIBL *_20;
};

static_assert(offsetof(DrRequetIBL, unknown18) == 0x18, "");

} // namespace ml
