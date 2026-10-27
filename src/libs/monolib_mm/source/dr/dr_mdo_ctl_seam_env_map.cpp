#include "dr/dr_mdo_ctl_seam_env_map.h"

#include "dr/dr_res_mdo_seam_wrk_env.h"

namespace ml {

void DrMdoCtlSeamEnvMap::releaseEnvMap() {
  DrResMdoSeamWrkEnv *env = unknown380;
  while (env != nullptr) {
    DrResMdoSeamWrkEnv *next = env->unknown08;
    releaseFreeSeamEnvMap(env);
    env = next;
  }
  unknownc50 = 0;
}

void DrMdoCtlSeamEnvMap::createEnvDisplayList(DrResMdoSeamWrkEnv *wrk) { wrk->setDispState(); }

void DrMdoCtlSeamEnvMap::updateEnvMap() {
  readEnvMapCheck();
  if (((unknownc7c >> 12) & 1) == 0) {
    updateEnvMapRenderList();
  }
}

} // namespace ml
