#pragma once
#include <stddef.h>

#include "dr/dr_mdo_node.h"
#include "types.h"

namespace ml {
class DrResMdoMat;
struct DrResMpfSampler;
class DrShdDataList;
struct MdoWrkMatSetupArg;
struct MdsMatInfoHeader;
struct MdsMpfMatInfoHeader;
struct MdsMatTechnique;

struct MdsMatVariableTbl {
  u16 unknown00; // Inferred role: variable type; original member name unknown.
  u16 unknown02; // Inferred role: value index; original member name unknown.
  u8 _04[0x06 - 0x04];
  u16 unknown06; // Inferred role: count; original member name unknown.
};

static_assert(offsetof(MdsMatVariableTbl, unknown02) == 0x02, "");
static_assert(offsetof(MdsMatVariableTbl, unknown06) == 0x06, "");
static_assert(sizeof(MdsMatVariableTbl) == 0x08, "");

struct MdsMatValShaderCate {
  enum Flag {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: storage buffer; original name unknown.
  };

  u8 _00[0x03 - 0x00];
  u8 unknown03; // Inferred role: flags; original member name unknown.
};

static_assert(offsetof(MdsMatValShaderCate, unknown03) == 0x03, "");

struct MdsMpfMatExtData {
  f32 unknown00[3]; // Inferred role: color; original member name unknown.
  u32 unknown0c;    // Inferred role: flags; original member name unknown.
  f32 unknown10;    // Inferred role: unknown value copied to the uniform; original member name unknown.
  f32 unknown14;    // Inferred role: unknown value copied to the uniform; original member name unknown.
  f32 unknown18;    // Inferred role: fade start distance; original member name unknown.
  f32 unknown1c;    // Inferred role: fade end distance; original member name unknown.
  f32 unknown20;    // Inferred role: fade ratio; original member name unknown.
  u16 unknown24;    // Inferred role: flags shifted by 4 into the uniform flags; original member name unknown.
  u8 _26[0x34 - 0x26];
};

static_assert(offsetof(MdsMpfMatExtData, unknown0c) == 0x0c, "");
static_assert(offsetof(MdsMpfMatExtData, unknown10) == 0x10, "");
static_assert(offsetof(MdsMpfMatExtData, unknown18) == 0x18, "");
static_assert(offsetof(MdsMpfMatExtData, unknown20) == 0x20, "");
static_assert(offsetof(MdsMpfMatExtData, unknown24) == 0x24, "");
static_assert(sizeof(MdsMpfMatExtData) == 0x34, "");

class DrMdoSetup : public DrMdoNode {
public:
  // Inferred role: mpf material uniform values; original type name unknown.
  struct unknown002 {
    f32 unknown00[3]; // Inferred role: color; original member name unknown.
    u32 unknown0c;    // Inferred role: flags; original member name unknown.
    f32 unknown10;    // Inferred role: unknown value; original member name unknown.
    f32 unknown14;    // Inferred role: unknown value; original member name unknown.
    f32 unknown18;    // Inferred role: unused; original member name unknown.
    f32 unknown1c;    // Inferred role: unused; original member name unknown.
    f32 unknown20;    // Inferred role: fade start distance; original member name unknown.
    f32 unknown24;    // Inferred role: inverse fade range; original member name unknown.
    f32 unknown28;    // Inferred role: fade ratio; original member name unknown.
    f32 unknown2c;    // Inferred role: unused; original member name unknown.
  };

  // Inferred role: mpf model resource header; original type name unknown.
  struct unknown003 {
    u8 _00[0x10 - 0x00];
    u32 unknown10; // Inferred role: material extension data offset; original member name unknown.
    s32 unknown14; // Inferred role: material extension data count; original member name unknown.
  };

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
  void getSetupMaterial(MdoWrkMatSetupArg &arg, const MdsMatInfoHeader *header, int mode);
  void createUniformBlock(const MdsMatInfoHeader *header, DrResMdoMat *mat);
  void setShader(DrResMdoMat *mat, const MdsMatInfoHeader *header, const MdsMatTechnique *technique, u32 matIndex, int mdlIndex, u32 bufferIndex);
  void updateUniformBlock(const u32 *flags);
  void createMpfMatUniformBlock(const MdsMpfMatExtData *data, int index);
  void updateMpfMatUniformBlock();
  void setupPrePassShader(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused);
  void setupThicknessShader(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, bool isFirst);
  void setupShadowShader(DrShdDataList *list, int index, const MdsMatInfoHeader *header, int uniformIndex, int unused);
  void setupMpfShader(DrShdDataList *list, int index, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre);
  void setupCharAvatarUniform();
  void setupDollAvatarUniform();
  void uniformBlock_Static(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex);
  void uniformBlock_Material(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex);
  void uniformBlock_Light(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex);
  void uniformBlock_Mdl(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex);
  void uniformBlock_Bone(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex);
  void uniformBlock_OldMdl(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex);
  void uniformBlock_OldBone(const MdsMatValShaderCate *cate, int paramIndex, int mdlIndex, int matIndex, bool isJitter, u32 bufferIndex);
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
  int unimate_matColor(f32 *work, DrResMdoMat *mat, const MdsMatInfoHeader *header, const MdsMatVariableTbl *variable);
  int unimate_alphaInfo(f32 *work, DrResMdoMat *mat, const MdsMatInfoHeader *header, const MdsMatVariableTbl *variable);
  int unimate_AvatarMapWrk(f32 *work, DrResMdoMat *mat, const MdsMatInfoHeader *header, const MdsMatVariableTbl *variable);
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
  void varStTex_DownBaseColorTex(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStTex_SpecularIBLTex(const MdsMatInfoHeader *header, u32 location, u32 index);
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
  void varStTex_Movie2(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStTex_Movie3(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStImg_BaseColor(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStImg_Etc(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStImg_Normal(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStImg_Velocity(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStImg_ZBuff(const MdsMatInfoHeader *header, u32 location, u32 index);

  static int (DrMdoSetup::*s_pStockMaterial[])(f32 *work, DrResMdoMat *mat, const MdsMatInfoHeader *header, const MdsMatVariableTbl *variable);
};

static_assert(sizeof(DrMdoSetup) == 0x190, "");

} // namespace ml
