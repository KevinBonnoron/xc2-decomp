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
  DrLightObjGlobalIBL *m_drLightObjGlobalIBL; // Inferred role: light; original member name unknown.
  u64 unknown20;                              // Inferred role: request id (light address); original member name unknown.
  u8 *unknown28;                              // Inferred role: request state; original member name unknown.
};

static_assert(offsetof(DrRequetIBL, m_drLightObjGlobalIBL) == 0x18, "");
static_assert(offsetof(DrRequetIBL, unknown20) == 0x20, "");
static_assert(offsetof(DrRequetIBL, unknown28) == 0x28, "");
static_assert(sizeof(DrRequetIBL) == 0x30, "");

} // namespace ml
