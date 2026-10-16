#include "gf/object/gf_obj.h"

namespace gf {

GfObjLayerSpeed::Info GfObjLayerSpeed::s_info[fw::Framework::LAYER_MAX];

void GfObjLayerSpeed::initialize() {
  for (u32 layer = 0; layer < fw::Framework::LAYER_MAX; layer++) {
    s_info[layer] = Info();
  }
}

void GfObjLayerSpeed::finalize() {}

void GfObjLayerSpeed::reqApplyModelLayerSpeed(u32 layer, f32 speed) {
  s_info[layer].request = true;
  s_info[layer].speed = speed;
}

bool GfObjLayerSpeed::isRequest(u32 layer) { return s_info[layer].request; }

f32 GfObjLayerSpeed::getSpeed(u32 layer) { return s_info[layer].speed; }

void GfObjLayerSpeed::cleanup() {
  for (u32 layer = 0; layer < fw::Framework::LAYER_MAX; layer++) {
    s_info[layer] = Info();
  }
}

} // namespace gf
