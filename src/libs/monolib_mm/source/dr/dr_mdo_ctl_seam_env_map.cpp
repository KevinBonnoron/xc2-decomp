#include "dr/dr_mdo_ctl_seam_env_map.h"

#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_mdo_ctl_seam.h"
#include "dr/dr_res_mdo_seam_mem_man.h"
#include "dr/dr_res_mdo_seam_parm_read.h"
#include "dr/dr_res_mdo_seam_res.h"
#include "dr/dr_res_mdo_seam_wrk_env.h"

namespace ml {
struct MdoWrkMatRes;

DrMdoCtlSeamEnvMap::DrMdoCtlSeamEnvMap(int viewNum) : DrMdoCtlSeamMpfMap(viewNum) {}

void DrMdoCtlSeamEnvMap::releaseEnvMap() {
  DrResMdoSeamWrkEnv *env = unknown370.unknown10.unknown00;
  while (env != nullptr) {
    DrResMdoSeamWrkEnv *next = env->unknown08;
    releaseFreeSeamEnvMap(env);
    env = next;
  }
  unknownc50 = 0;
}

void DrMdoCtlSeamEnvMap::changeMemEnvMapParts(DrResMdoSeamWrkEnv *env) {
  MdoWrkMatRes *matRes = env->unknown58;
  const u8 *data = env->unknown60->m_buffer;
  const MdsSeamEnvMapHead *head = reinterpret_cast<const MdsSeamEnvMapHead *>(data);
  resetBaseMapMaterial(matRes, data + head->unknown04, data + head->unknown00, data + head->unknown0c, data + head->unknown18, data + head->unknown10, 0);
  if (head->unknown08 != 0) {
    changeMemFixAnim(matRes, data + head->unknown08);
  }
  env->changeMemCall(head);
}

DrResMdoSeamWrkEnv *DrMdoCtlSeamEnvMap::createFreeSeamEnvMap() { return unknown370.unknown001(); }

void DrMdoCtlSeamEnvMap::releaseFreeSeamEnvMap(DrResMdoSeamWrkEnv *env) {
  DrResMdoSeamMemObj *mem = env->unknown60;
  if (env->unknown58 != nullptr) {
    unknownba0[env->unknown50 >> 5] &= ~(1 << (env->unknown50 & 0x1f));
    unknownc50 += env->unknown70;
    releaseBaseMapSeamMat(env->unknown58);
    env->release();
    unknownc08--;
  }
  unknown370.unknown002(env);
  if (mem != nullptr) {
    env->unknown60 = nullptr;
    unknown6e0.releaseFreeObj(mem);
  }
}

void DrMdoCtlSeamEnvMap::readEnvMapCheck() {
  DrCalcViewWork *view = m_drMan->unknown580->unknown10;
  bool isOpen = ((unknownc7c >> 12) & 1) != 0 || unknowncc8;
  DrResMdoSeamWrkEnv *env = unknown370.unknown10.unknown00;
  while (env != nullptr) {
    if (env->update(view->unknown400, isOpen)) {
      DrResMdoSeamWrkEnv *next = env->unknown08;
      releaseFreeSeamEnvMap(env);
      env = next;
    } else {
      if (env->unknown6c & 0x10) {
        changeMemEnvMapParts(env);
      }
      env = env->unknown08;
    }
  }
  if ((unknownc7c & 0x81200) == 0 && unknownc08 < 1) {
    for (int i = 0; i < unknown1a8->unknown30; i++) {
      if ((unknown723(unknownba0, i) & (1 << (i & 0x1f))) == 0) {
        unknownd30.setStockEnvMdl(i + 1);
        return;
      }
    }
  }
}

void DrMdoCtlSeamEnvMap::createEnvDisplayList(DrResMdoSeamWrkEnv *wrk) { wrk->setDispState(); }

void DrMdoCtlSeamEnvMap::updateEnvMap() {
  readEnvMapCheck();
  if (((unknownc7c >> 12) & 1) == 0) {
    updateEnvMapRenderList();
  }
}

void DrMdoCtlSeamEnvMap::callRenderSeamEnvMap() { unknown002(1, 0, 1); }

void DrMdoCtlSeamEnvMap::callGBuffRenderSeamEnvMap() { unknown002(2, 1, 8); }

void DrMdoCtlSeamEnvMap::callLightPrePassRenderSeamEnvMap() { unknown002(8, 3, 0x20); }

void DrMdoCtlSeamEnvMap::callAlphaRenderSeamEnvMap() { unknown002(0x10, 4, 2); }

void DrMdoCtlSeamEnvMap::callSpAlphaRenderSeamEnvMap() { unknown002(0x20, 5, 0x40); }

void DrMdoCtlSeamEnvMap::callRefractionRenderSeamEnvMap() { unknown002(4, 2, 4); }

} // namespace ml
