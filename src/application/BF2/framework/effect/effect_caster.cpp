#include "framework/effect/effect_caster.h"

#include "framework/effect/effect_manager.h"
#include "mm_mtl/fixed_vector.h"

namespace fw {

mm::mtl::FixedVector<EffectCasterBase *, 256> EffectCasterBase::s_casterList;

void EffectCasterBase::tail() {
  mm::mtl::FixedVector<EffectCasterBase *, 256> casters;
  for (u32 i = 0; i < s_casterList.size(); i++) {
    if (s_casterList[i]->_40) {
      casters.push_back(s_casterList[i]);
    }
  }
  for (u32 i = 0; i < casters.size(); i++) {
    if (casters[i] != nullptr) {
      delete casters[i];
      casters[i] = nullptr;
    }
  }
}

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
