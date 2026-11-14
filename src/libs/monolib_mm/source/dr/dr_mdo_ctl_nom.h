#pragma once
#include <stddef.h>

#include "dr/dr_mdl_obj.h"
#include "dr/dr_res_mdo_lod_obj.h"
#include "grlib/cglib_ctl_shader.h"
#include "types.h"

namespace mm {
struct Col3;
} // namespace mm

namespace cloud {
class CloudMdlDataObj;
} // namespace cloud

namespace ml {
class DrMan;
class DrMdoNomAfterImage;
class DrResEtcPamObj;
class DrResMdoLight;
class DrResMdoMeshObj;
class DrResMdoMorpObj;
class DrResMdoShdObj;
class DrResMdoSortNomCldBackApha;
class DrResMdoSortNomFastApha;
class DrResMdoSortNomLastApha;
class DrResMdoVtxMeshObj;
class DrResClip;
struct MdsMdlTopHeader;

// Inferred role: entry of a render list, the list continues at the entry after the index; original member names unknown.
class DrResChkList {
public:
  u16 unknown00; // Inferred role: mdl info index; original member name unknown.
  u16 unknown02; // Inferred role: index of the next entry plus one, 0 ends the list; original member name unknown.
};

static_assert(sizeof(DrResChkList) == 0x04, "");

// Inferred role: sort objects and per mdl render lists of the alpha passes; original type name unknown.
struct unknown099 {
  DrResMdoSortNomFastApha *unknown00;    // Inferred role: fast alpha sort object; original member name unknown.
  DrResMdoSortNomLastApha *unknown08;    // Inferred role: last alpha sort object; original member name unknown.
  DrResMdoSortNomCldBackApha *unknown10; // Inferred role: cld back alpha sort object; original member name unknown.
  DrResChkList **unknown18;              // Inferred role: fast alpha render list per mdl; original member name unknown.
  DrResChkList **unknown20;              // Inferred role: last alpha render list per mdl; original member name unknown.
  DrResChkList **unknown28;              // Inferred role: cld back alpha render list per mdl; original member name unknown.
};

static_assert(offsetof(unknown099, unknown18) == 0x18, "");
static_assert(offsetof(unknown099, unknown20) == 0x20, "");
static_assert(offsetof(unknown099, unknown28) == 0x28, "");

class DrMdoCtlNom : public DrMdlObj {
public:
  DrMdoCtlNom(const void *data, const char *path, DrMan *drMan, int viewNum);
  ~DrMdoCtlNom() override;
  void update() override;
  void dispOffUpdate() override;
  void resourceInit() override;
  void shadowRender() override;
  bool shadowCacheRender(DrPixlShadowCacheObj &cache) override;
  void shadowCacheOnlyRender() override;
  void callShadowCacheUpdate(u64 flags) override;
  void occRender() override;
  bool cloneMdlObj(DrMdlObj *source) override;
  void setDisp(bool isDisp) override;
  void setDeleteCall(int deleteCall) override;
  void releaseNom();
  bool stmResSetup();
  void updateVanishEffectParams();
  void updateRimBloomParams();
  void updateAfterImage();
  void calcMdlUniformBlock();
  void updateShdMdl();
  void updateMdlUniformBlock();
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
  void zPrePassRender();
  void nomRender(const MdsMdlTopHeader *top, DrResChkList *list);
  void shadowMapDirRender(int index);
  void shwRender(const MdsMdlTopHeader *top, DrResChkList *list);
  void thicknessRender(bool isFirst);

  // Inferred role: creates the weight vertices and sets the material state up for the alpha pass; original name unknown.
  // Numbered 002 because unknown001 of DrMdoSetup is used through this class.
  void unknown002() {
    if (m_nodeMax != 0) {
      grlib::CGLibCtlShader::setMemoryBarrierBit(1);
      createWeightVtx(1, unknown100, unknown1f0->unknown1c, false);
      grlib::CGLibCtlShader::setMemoryBarrierBit(0x21);
    }
    unknownf4 = 4;
    unknownf2 = 1;
    beginSetup();
  }

  u8 _1a8[0x1b8 - 0x1a8];
  unknown099 *unknown1b8; // Inferred role: alpha sort work; original member name unknown.
  u8 _1c0[0x1c8 - 0x1c0];
  DrResMdoMorpObj *unknown1c8;    // Inferred role: morph object; original member name unknown.
  DrResMdoShdObj *unknown1d0;     // Inferred role: shd object; original member name unknown.
  DrResMdoVtxMeshObj *unknown1d8; // Inferred role: vtx mesh object; original member name unknown.
  DrResMdoLight *unknown1e0;      // Inferred role: light; original member name unknown.
  DrResMdoMeshObj *unknown1e8;    // Inferred role: mesh object; original member name unknown.
  DrResMdoLodObj *unknown1f0;     // Inferred role: lod object; original member name unknown.
  DrResClip *unknown1f8;          // Inferred role: clip; original member name unknown.
  DrResEtcPamObj *unknown200;     // Inferred role: etc pam object; original member name unknown.
  u8 _208[0x210 - 0x208];
  cloud::CloudMdlDataObj *unknown210; // Inferred role: cloud model data; original member name unknown.
  DrMdoNomAfterImage *unknown218;     // Inferred role: current after image, updated each frame and deleted once its release call is due; original member name unknown.
  DrMdoNomAfterImage *unknown220[2];  // Inferred role: new after images waiting per double buffer index; original member name unknown.
  u64 unknown230;                     // Inferred role: shadow cache mask; original member name unknown.
  const char *unknown238;             // Inferred role: path given to the constructor; original member name unknown.
};

static_assert(offsetof(DrMdoCtlNom, unknown190) == 0x190, "");
static_assert(offsetof(DrMdoCtlNom, unknown198) == 0x198, "");
static_assert(offsetof(DrMdoCtlNom, unknown1b8) == 0x1b8, "");
static_assert(offsetof(DrMdoCtlNom, unknown1c8) == 0x1c8, "");
static_assert(offsetof(DrMdoCtlNom, unknown1d0) == 0x1d0, "");
static_assert(offsetof(DrMdoCtlNom, unknown1d8) == 0x1d8, "");
static_assert(offsetof(DrMdoCtlNom, unknown1e0) == 0x1e0, "");
static_assert(offsetof(DrMdoCtlNom, unknown1e8) == 0x1e8, "");
static_assert(offsetof(DrMdoCtlNom, unknown1f0) == 0x1f0, "");
static_assert(offsetof(DrMdoCtlNom, unknown1f8) == 0x1f8, "");
static_assert(offsetof(DrMdoCtlNom, unknown200) == 0x200, "");
static_assert(offsetof(DrMdoCtlNom, unknown210) == 0x210, "");
static_assert(offsetof(DrMdoCtlNom, unknown218) == 0x218, "");
static_assert(offsetof(DrMdoCtlNom, unknown220) == 0x220, "");
static_assert(offsetof(DrMdoCtlNom, unknown230) == 0x230, "");
static_assert(offsetof(DrMdoCtlNom, unknown238) == 0x238, "");

} // namespace ml
