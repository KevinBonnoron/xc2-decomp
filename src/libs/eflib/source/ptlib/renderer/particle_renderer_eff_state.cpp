#include "ptlib/renderer/particle_renderer_eff_state.h"

namespace ptlib {
namespace renderer {

namespace {
EffStateManager *unknown001;
const GrlTexClamp unknown002[3] = {GRL_TEX_CLAMP_REPEAT, GRL_TEX_CLAMP_CLAMP, GRL_TEX_CLAMP_MIRRORED_REPEAT};
} // namespace

EffStateManager *EffStateManager::get() { return unknown001; }

EffStateManager::EffStateManager() { unknown001 = this; }

EffStateManager::~EffStateManager() {
  for (int i = 0; i < 7; i++) {
    unknown400[i].release();
    unknown470[i].release();
  }
  unknown4e0.release();
  unknown4f0.release();
  unknown500.release();
  unknown528.release();
  for (int i = 0; i < 4; i++) {
    unknown578[i].release();
  }
  unknown001 = nullptr;
}

void EffStateManager::begin() { unknown618.beginInstansBuff(); }

void EffStateManager::initSampler() {
  for (int r = 0; r < 3; r++) {
    for (int t = 0; t < 3; t++) {
      for (int s = 0; s < 3; s++) {
        grlib::CGLibSampler &sampler = unknown00[s + t * 3 + r * 9];
        sampler.initSampler(GRL_TEX_CLAMP_REPEAT, GRL_TEX_MAG_FILTER_LINEAR);
        sampler.setClamp(unknown002[s], unknown002[t], unknown002[r]);
        sampler.updateData();
      }
    }
  }
  unknown360.initSampler(GRL_TEX_CLAMP_CLAMP_TO_BORDER, GRL_TEX_MAG_FILTER_LINEAR);
  unknown360.setDepthCompare(static_cast<GrlTexCompare>(3));
  unknown360.setBorderType(GRL_TEX_BORDER_OPAQUE_WHITE);
  unknown360.updateData();
  unknown380.initSampler(GRL_TEX_CLAMP_CLAMP_TO_BORDER, GRL_TEX_MAG_FILTER_LINEAR);
  unknown380.setBorderType(GRL_TEX_BORDER_OPAQUE_WHITE);
  unknown380.updateData();
  unknown3e0.initSampler(GRL_TEX_CLAMP_CLAMP, GRL_TEX_MAG_FILTER_NEAREST);
  unknown3e0.updateData();
  unknown3a0.initSampler(GRL_TEX_CLAMP_REPEAT, GRL_TEX_MAG_FILTER_NEAREST);
  unknown3a0.setClamp(GRL_TEX_CLAMP_CLAMP, GRL_TEX_CLAMP_CLAMP, GRL_TEX_CLAMP_CLAMP);
  unknown3a0.updateData();
  unknown3c0.initSampler(GRL_TEX_CLAMP_CLAMP, GRL_TEX_MAG_FILTER_NEAREST);
  unknown3c0.setClamp(GRL_TEX_CLAMP_CLAMP, GRL_TEX_CLAMP_CLAMP, GRL_TEX_CLAMP_CLAMP);
  unknown3c0.updateData();
}

} // namespace renderer
} // namespace ptlib
