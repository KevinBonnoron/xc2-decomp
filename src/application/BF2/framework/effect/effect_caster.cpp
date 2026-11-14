#include "framework/effect/effect_caster.h"

#include "framework/effect/effect_manager.h"
#include "framework/effect/effect_point.h"
#include "framework/framework.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/reference_object.h"

namespace fw {

mm::mtl::FixedVector<EffectCasterBase *, 256> EffectCasterBase::s_casterList;

EffectCasterBase::EffectCasterBase(const EffectPoint *point, u32 layer) : unknown18(nullptr), unknown20(nullptr), unknown28(0), _40(false) {
  // `this != nullptr` is in the game's constructor (the `cbz x19` after the vtable store; Torna's C2 is code-identical;
  // clang 3.9 never synthesises it).
  if (this != nullptr && EffectManager::get() != nullptr) {
    unknown38 = 1;
    unknown10 = nullptr;
    if (point != nullptr) {
      // The member must be non-const (changeLayer writes through it) while the symbol takes `const EffectPoint *`; no code effect.
      unknown10 = const_cast<EffectPoint *>(point);
      unknown38 += unknown10->getPointCount();
      unknown10->unknown001();
    }
    unknown08 = nullptr;
    unknown3c = layer;
    unknown30 = Framework::getAllocator();
    EffectManager::get()->addCaster(this);
  }
  s_casterList.push_back(this);
}

EffectCasterBase::~EffectCasterBase() {
  if (unknown10 != nullptr) {
    unknown10->unknown002();
    unknown10 = nullptr;
  }
  EffectManager::get()->remove(this);
  EffectManager::get()->removeCaster(this);
  for (EffectCasterBase **it = s_casterList.begin(); it != s_casterList.end();) {
    if (*it == this) {
      it = s_casterList.erase(it);
    } else {
      it++;
    }
  }
}

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
