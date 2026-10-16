#pragma once
#include <stddef.h>

#include "dr/dr_mdl_obj.h"
#include "types.h"

namespace mm {
struct Col3;
} // namespace mm

namespace ml {
class DrResEtcPamObj;
class DrResMdoMeshObj;
class DrResMdoShdObj;
class DrResMdoVtxMeshObj;

class DrMdoCtlNom : public DrMdlObj {
public:
  void createAfterImage(f32 count, f32 span, f32 fade, const mm::Col3 &headColor, f32 headAlpha, f32 headEmissive, f32 headScale,
                        const mm::Col3 &tailColor, f32 tailAlpha, f32 tailEmissive, f32 tailScale);
  void releaseAfterImage();

  u8 _164[0x1d0 - 0x164];
  DrResMdoShdObj *m_shdObj;
  DrResMdoVtxMeshObj *m_vtxMeshObj;
  u8 _1e0[0x1e8 - 0x1e0];
  DrResMdoMeshObj *m_meshObj;
  u8 _1f0[0x200 - 0x1f0];
  DrResEtcPamObj *m_etcPamObj;
};

static_assert(offsetof(DrMdoCtlNom, m_shdObj) == 0x1d0, "");
static_assert(offsetof(DrMdoCtlNom, m_vtxMeshObj) == 0x1d8, "");
static_assert(offsetof(DrMdoCtlNom, m_meshObj) == 0x1e8, "");
static_assert(offsetof(DrMdoCtlNom, m_etcPamObj) == 0x200, "");

} // namespace ml
