#include "eflib/effect_system_manager.h"
#include "framework/effect/effect_caster.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace fw {

EffectCasterBase *EffectCasterSend::getCaster() { return caster; }

bool EffectCasterSend::checkCaster(EffectCasterBase *caster) { return this->caster == caster; }

void EffectCasterSend::sendData(f32 scale) {
  if (caster == nullptr || effect::SystemManager::getPtr() == nullptr) {
    return;
  }

  scales[effect::SystemManager::getPtr()->writeBuffer != 0] = scale;
}

void EffectCasterSend::sendDataFrame(f32 frame) {
  if (caster == nullptr || effect::SystemManager::getPtr() == nullptr) {
    return;
  }

  frames[effect::SystemManager::getPtr()->writeBuffer != 0] = frame;
}

void EffectCasterSend::sendDataStateName(const char *name) {
  if (caster == nullptr || effect::SystemManager::getPtr() == nullptr) {
    return;
  }

  stateNames[effect::SystemManager::getPtr()->writeBuffer != 0] = name;
}

const char *EffectCasterSend::getStateName() { return stateNames[effect::SystemManager::getPtr()->writeBuffer == 0].c_str(); }

EffectBindData *EffectCasterSend::getBindData(u32 &count) {
  if (caster == nullptr) {
    return nullptr;
  }

  EffectBindData *datas = caster->bindDatas;
  count = caster->bindDataCount;
  return datas;
}

f32 EffectCasterSend::getMdlFrame() { return frames[effect::SystemManager::getPtr()->writeBuffer == 0]; }

f32 EffectCasterSend::getMdlScl() { return scales[effect::SystemManager::getPtr()->writeBuffer == 0]; }

} // namespace fw
