#include "ptlib/renderer/particle_renderer_stream_kizuna.h"

#include "grlib/cglib_sampler.h"
#include "ptlib/renderer/particle_renderer_eff_state.h"

namespace ptlib {
namespace renderer {

StreamObjKizuna::~StreamObjKizuna() { unknown00.delayRelease(); }

void StreamObjKizuna::release() { unknown00.delayRelease(); }

void StreamObjKizuna::releaseSub() { unknown00.delayRelease(); }

void *StreamObjKizuna::lockStream(const DrDrawWorkInfoEF *info) {
  u32 size;
  unknown00.lock(&unknown38, &size);
  return unknown38;
}

void StreamObjKizuna::unlockStream(const DrDrawWorkInfoEF *info) { unknown00.unlock(); }

grlib::CGLibSampler *StreamObjKizuna::getSampler(u32 clamp) {
  switch (clamp) {
  case 0:
  case 1:
    return EffStateManager::get()->unknown00;
  case 4:
  case 5:
    return &EffStateManager::get()->unknown00[26];
  default:
    return &EffStateManager::get()->unknown00[13];
  }
}

grlib::CGLibSampler *StreamObjKizuna::getSampler(u32 clampS, u32 clampT) {
  int s = clampS;
  if (s > 2) {
    s = 0;
  }
  EffStateManager *manager = EffStateManager::get();
  int t = clampT * 3;
  if (static_cast<int>(clampT) > 2) {
    t = 0;
  }
  return &manager->unknown00[t + s];
}

} // namespace renderer
} // namespace ptlib
