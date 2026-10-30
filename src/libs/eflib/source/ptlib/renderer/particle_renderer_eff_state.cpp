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

void EffStateManager::init(StaticAllocObj *allocator) {
  initSampler();
  initVtxFetch();
  initVtxIndex();
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

void EffStateManager::initVtxFetch() {
  grlib::CGLibVtxAttr attributes[11];
  for (u32 i = 0; i < 4; i++) {
    attributes[i] = {unknown073_46, i, i * 0x10, 0};
  }
  for (u32 i = 4; i < 11; i++) {
    attributes[i] = {unknown073_46, i, i * 0x10, 0};
    unknown400[i - 4].createFetchObj(attributes, i + 1);
  }
  attributes[0] = {unknown073_13, 0, 0, 0};
  for (u32 i = 1; i < 5; i++) {
    attributes[i] = {unknown073_46, i, (i - 1) * 0x10, 1};
  }
  // The original writes a 12th attribute into the 11-entry array (original bug, reproduced).
  for (u32 i = 5; i < 12; i++) {
    attributes[i] = {unknown073_46, i, (i - 1) * 0x10, 1};
    unknown470[i - 5].createFetchObj(attributes, i + 1);
  }
  attributes[0] = {unknown073_46, 0, 0, 0};
  attributes[1] = {unknown073_22, 1, 0x10, 0};
  attributes[2] = {unknown073_37, 2, 0x18, 0};
  unknown4e0.createFetchObj(attributes, 3);
  attributes[0] = {unknown073_46, 0, 0, 0};
  attributes[1] = {unknown073_47, 1, 0x10, 0};
  unknown4f0.createFetchObj(attributes, 2);
}

} // namespace renderer
} // namespace ptlib
