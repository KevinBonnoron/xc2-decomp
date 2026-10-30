#pragma once
#include <stddef.h>

#include "dr/dr_mdo_node.h"
#include "types.h"

namespace grlib {
class CGLibEtcUniformBlock;
} // namespace grlib

namespace ml {
class DrResMdoMat;
struct MdsMatInfoHeader;

struct MdsMatVariableTbl {
  u8 _00[0x02 - 0x00];
  u16 unknown02; // Inferred role: value index; original member name unknown.
  u8 _04[0x06 - 0x04];
  u16 unknown06; // Inferred role: count; original member name unknown.
};

static_assert(offsetof(MdsMatVariableTbl, unknown02) == 0x02, "");
static_assert(offsetof(MdsMatVariableTbl, unknown06) == 0x06, "");

struct MdsMatValShaderCate {
  enum Flag {
    FLAG_STORAGE_BUFFER = 1 << 0,
  };

  u8 _00[0x03 - 0x00];
  u8 unknown03; // Inferred role: flags; original member name unknown.
};

static_assert(offsetof(MdsMatValShaderCate, unknown03) == 0x03, "");

class DrMdoSetup : public DrMdoNode {
public:
  void changeShader(bool isChange);
  void beginMatInfo();
  // Inferred role: resets the material info state, the body of beginMatInfo inlined by callers; original name unknown.
  void unknown001() {
    unknown17c = 0xffff;
    unknown17e = 0xffff;
    unknown178 = 0x10;
    unknown179 = 0;
  }
  void changeSeamMatInfo();
  void changeShaderMat(bool isChange);
  void changeShaderPos();
  void setupCharAvatarUniform();
  void setupDollAvatarUniform();
  void uniformBlock_Static(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex);
  void uniformBlock_Material(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex);
  void uniformBlock_Light(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex);
  void uniformBlock_Mdl(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex);
  void uniformBlock_Bone(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex);
  void uniformBlock_no(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex);
  void uniformBlock_AvatarChar(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex);
  void uniformBlock_AvatarDoll(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex);
  void uniformBlock_Fog(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex);
  void uniformBlock_Toon(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex);
  void uniformBlock_VolTexCalc(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex);
  void uniformBlock_GlobalIBL(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex);
  void uniformBlock_ClusterParam(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex);
  void uniformBlock_ClusterPntList(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex);
  void uniformBlock_ClusterSptList(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex);
  void uniformBlock_ClusterIdxList(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex);
  void uniformBlock_ClusterAddressList(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex);
  void uniformBlock_RimBloomCalc(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex);
  void uniformBlock_Toon2(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex);
  int unimate_alphaInfo(f32 *work, DrResMdoMat *mat, const MdsMatInfoHeader *header, const MdsMatVariableTbl *variable);
  int unimate_texMatrix(f32 *work, DrResMdoMat *mat, const MdsMatInfoHeader *header, const MdsMatVariableTbl *variable);
  int unimate_workFloat4(f32 *work, DrResMdoMat *mat, const MdsMatInfoHeader *header, const MdsMatVariableTbl *variable);
  int unimate_workColor(f32 *work, DrResMdoMat *mat, const MdsMatInfoHeader *header, const MdsMatVariableTbl *variable);
  int unimate_ProjectionMat(f32 *work, DrResMdoMat *mat, const MdsMatInfoHeader *header, const MdsMatVariableTbl *variable);
  int unimate_NomProjectionMat(f32 *work, DrResMdoMat *mat, const MdsMatInfoHeader *header, const MdsMatVariableTbl *variable);
  void varStTex_ColorTex(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStTex_NormalTex(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStTex_LightTex(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStTex_DepthTex(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStTex_RefTex(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStTex_ShadowMap(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStTex_AvatarFaceMap1(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStTex_Capture1(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStTex_Capture2(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStTex_Capture3(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStTex_RefractionMap(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStTex_ColorDepTex(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStTex_AvatarFaceMap2(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStTex_AvatarEyeTex(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStTex_CaptureMain(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStTex_BaseColorTex(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStTex_ScreenCapTex(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStTex_ToonGradTex(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStTex_RefLightTex(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStTex_GlobalIBLIndexTex(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStTex_BackFaceDepthTex(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStTex_DownDepthTex(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStTex_ClusterIdxListTex(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStTex_VelocityTex(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStTex_RefractionAfterTex(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStTex_DiffuseIBL(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStTex_AOTex(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStTex_EtcTex(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStTex_ToonDarkGradTex(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStTex_AmbBRDFTex(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStTex_ToonRimTex(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStTex_VolumeTex01(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStTex_OrientationTex(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStTex_FlagWaveTex0(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStTex_FlagWaveTex1(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStTex_DitherTex(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStTex_Capture4(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStTex_Movie0(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStImg_BaseColor(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStImg_Etc(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStImg_Normal(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStImg_Velocity(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStImg_ZBuff(const MdsMatInfoHeader *header, u32 location, u32 index);

  u8 _16c[0x170 - 0x16c];
  grlib::CGLibEtcUniformBlock *unknown170; // Inferred role: etc uniform; original member name unknown.
  u8 unknown178;                           // Inferred role: setup flags; original member name unknown.
  u8 unknown179;                           // Inferred role: seam flag; original member name unknown.
  s16 unknown17a;                          // Inferred role: uniform index; original member name unknown.
  s16 unknown17c;                          // Inferred role: material index; original member name unknown.
  u16 unknown17e;                          // Inferred role: previous material index; original member name unknown.
};

static_assert(offsetof(DrMdoSetup, unknown170) == 0x170, "");
static_assert(offsetof(DrMdoSetup, unknown178) == 0x178, "");
static_assert(offsetof(DrMdoSetup, unknown17a) == 0x17a, "");
static_assert(offsetof(DrMdoSetup, unknown17c) == 0x17c, "");
static_assert(sizeof(DrMdoSetup) == 0x180, "");

} // namespace ml
