#include "framework/effect/effect_caster.h"

#include "framework/effect/effect_manager.h"

namespace fw {

void EffectCasterBase::setScl(f32 scale) { EffectManager::get()->sendCaster(this, scale); }

void EffectCasterBase::setMotionFrame(f32 frame) { EffectManager::get()->sendCasterFrame(this, frame); }

void EffectCasterBase::setStateName(const char *name) { EffectManager::get()->sendCasterStateName(this, name); }

void EffectCasterBase::setEfpMat(mm::Mat44 &matrix, const char *name, int index) { EffectManager::get()->sendCaster(this, matrix, name, index); }

void EffectCasterBase::changeLayer(u32 layer, u32 newLayer) {
  if (this->unknown3c != newLayer && unknown10 != nullptr) {
    this->unknown3c = newLayer;
    EffectManager::get()->changeLayerCaster(this, layer, newLayer);
    unknown10->unknown0c = newLayer;
  }
}

} // namespace fw
