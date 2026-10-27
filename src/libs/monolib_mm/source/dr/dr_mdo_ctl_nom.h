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
  void updateShdMdl();
  void callNomSetupRender();
  void callZSortNomZpreePassRender();
  void callZSortThicknessRenderFirst();
  void callZSortThicknessRenderSecond();
  void callZSortNomRender();
  void callZSortLightPrePassRender();
  void callZSortNomAlphaRender();
  void callZSortNomSpAlphaRender();
  void callZSortGBuffRender();
  void callZSortNomRefractionRender();
  void callLastAlphaNomRender();
  void callFastAlphaNomRender();
  void callCldBackAlphaNomRender();
  void createAfterImage(f32 count, f32 span, f32 fade, const mm::Col3 &headColor, f32 headAlpha, f32 headEmissive, f32 headScale, const mm::Col3 &tailColor, f32 tailAlpha, f32 tailEmissive,
                        f32 tailScale);
  void releaseAfterImage();
  void nomCallRender(int pass);
  void lastAlphaCallRender();
  void fastAlphaCallRender();
  void cldBackAlphaCallRender();

  u8 _190[0x1d0 - 0x190];
  DrResMdoShdObj *unknown1d0;     // Inferred role: shd object; original member name unknown.
  DrResMdoVtxMeshObj *unknown1d8; // Inferred role: vtx mesh object; original member name unknown.
  u8 _1e0[0x1e8 - 0x1e0];
  DrResMdoMeshObj *unknown1e8; // Inferred role: mesh object; original member name unknown.
  u8 _1f0[0x200 - 0x1f0];
  DrResEtcPamObj *unknown200; // Inferred role: etc pam object; original member name unknown.
};

static_assert(offsetof(DrMdoCtlNom, unknown1d0) == 0x1d0, "");
static_assert(offsetof(DrMdoCtlNom, unknown1d8) == 0x1d8, "");
static_assert(offsetof(DrMdoCtlNom, unknown1e8) == 0x1e8, "");
static_assert(offsetof(DrMdoCtlNom, unknown200) == 0x200, "");

} // namespace ml
