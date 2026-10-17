#pragma once
#include "dr/dr_mdo_node.h"
#include "types.h"

namespace ml {
struct MdsMatInfoHeader;

class DrMdoSetup : public DrMdoNode {
public:
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
