#include "eflib/effect_system_manager.h"
#include "framework/effect/effect_caster.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace fw {

EffectCasterBase *EffectCasterSend::getCaster() { return m_caster; }

bool EffectCasterSend::checkCaster(EffectCasterBase *caster) { return this->m_caster == caster; }

void EffectCasterSend::sendData(f32 scale) {
  if (m_caster == nullptr || effect::SystemManager::getPtr() == nullptr) {
    return;
  }

  unknown88[effect::SystemManager::getPtr()->unknown7824d != 0] = scale;
}

void EffectCasterSend::sendDataFrame(f32 frame) {
  if (m_caster == nullptr || effect::SystemManager::getPtr() == nullptr) {
    return;
  }

  unknown90[effect::SystemManager::getPtr()->unknown7824d != 0] = frame;
}

void EffectCasterSend::sendDataStateName(const char *name) {
  if (m_caster == nullptr || effect::SystemManager::getPtr() == nullptr) {
    return;
  }

  unknown98[effect::SystemManager::getPtr()->unknown7824d != 0] = name;
}

const char *EffectCasterSend::getStateName() { return unknown98[effect::SystemManager::getPtr()->unknown7824d == 0].c_str(); }

EffectBindData *EffectCasterSend::getBindData(u32 &count) {
  if (m_caster == nullptr) {
    return nullptr;
  }

  EffectBindData *datas = m_caster->unknown20;
  count = m_caster->unknown28;
  return datas;
}

f32 EffectCasterSend::getMdlFrame() { return unknown90[effect::SystemManager::getPtr()->unknown7824d == 0]; }

f32 EffectCasterSend::getMdlScl() { return unknown88[effect::SystemManager::getPtr()->unknown7824d == 0]; }

} // namespace fw
