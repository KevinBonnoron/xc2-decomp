#pragma once
#include <stddef.h>

#include "dr/dr_mdo_node.h"
#include "types.h"

namespace ml {
class DrResMdoMat;
struct MdsMatInfoHeader;

struct MdsMatVariableTbl {
  u8 _00[0x02 - 0x00];
  u16 valueIndex;
  u8 _04[0x06 - 0x04];
  u16 count;
};

static_assert(offsetof(MdsMatVariableTbl, valueIndex) == 0x02, "");
static_assert(offsetof(MdsMatVariableTbl, count) == 0x06, "");

class DrMdoSetup : public DrMdoNode {
public:
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
  void varStImg_BaseColor(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStImg_Etc(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStImg_Normal(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStImg_Velocity(const MdsMatInfoHeader *header, u32 location, u32 index);
  void varStImg_ZBuff(const MdsMatInfoHeader *header, u32 location, u32 index);
};

} // namespace ml
