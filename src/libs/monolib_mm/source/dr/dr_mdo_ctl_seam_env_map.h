#pragma once

#include "dr/dr_man.h"
#include "dr/dr_mdo_ctl_seam.h"
#include "dr/dr_mdo_ctl_seam_mpf_map.h"
#include "dr/dr_res_mdo_seam_wrk_env.h"
#include "types.h"

namespace ml {

class DrMdoCtlSeamEnvMap : public DrMdoCtlSeamMpfMap {
public:
  DrMdoCtlSeamEnvMap(int viewNum);
  void releaseEnvMap();
  void releaseFreeSeamEnvMap(DrResMdoSeamWrkEnv *env);
  void initEnvMapParts(DrResMdoSeamWrkEnv *env);
  void changeMemEnvMapParts(DrResMdoSeamWrkEnv *env);
  DrResMdoSeamWrkEnv *createFreeSeamEnvMap();
  void updateEnvMap();
  void readEnvMapCheck();
  void updateEnvMapRenderList();
  void createEnvDisplayList(DrResMdoSeamWrkEnv *wrk);
  void callRenderSeamEnvMap();
  void callGBuffRenderSeamEnvMap();
  void callLightPrePassRenderSeamEnvMap();
  void callAlphaRenderSeamEnvMap();
  void callSpAlphaRenderSeamEnvMap();
  void callRefractionRenderSeamEnvMap();

  // Inferred role: renders the env maps that have the env flag set, with the render type and header mask; original name unknown.
  // Numbered 002 because unknown001 of DrMdoSetup is used through this class.
  void unknown002(u32 envFlag, int renderType, u32 flags) {
    if (!m_drMan->unknown1d6c) {
      for (DrResMdoSeamWrkEnv *env = unknown370.unknown10.unknown00; env != nullptr; env = env->unknown08) {
        unknown30 = env->unknown58;
        if (unknown30 != nullptr && (env->unknown68 & envFlag) != 0) {
          calcSeamMapRender(renderType, flags);
        }
      }
    }
  }
};

} // namespace ml
