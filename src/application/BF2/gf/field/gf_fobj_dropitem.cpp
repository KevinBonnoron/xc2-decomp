#include "gf/field/gf_fobj_dropitem.h"

#include "framework/effect/effect_manager.h"

namespace gf {

bool GfFobjDropitem::isEnableGet() const { return unknown30 > 1; }

void GfFobjDropitem::disposeEffect() {
  if (unknown54 != 0) {
    fw::EffectManager::get()->dead(unknown54);
    unknown54 = 0;
  }
}

} // namespace gf
