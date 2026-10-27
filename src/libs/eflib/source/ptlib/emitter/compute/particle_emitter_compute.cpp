#include "ptlib/emitter/compute/particle_emitter_compute.h"

// The game compiles ComputeManager::get, getPtr, init and term in this translation unit, from the _impl header.
#include "particle_emitter_compute_impl.h" // IWYU pragma: keep

namespace ptlib {
namespace emitter {

ComputeManager::ComputeManager() {}

ComputeManager::~ComputeManager() {}

void ComputeManager::resetUpdate() { unknown20c = false; }

void ComputeManager::calculateLight(u32 viewIndex) {}

void ComputeManager::calculateClip(u32 viewIndex) {}

void ComputeManager::initSub() {
  unknown08.createUniform(0, 10000);
  unknown48.createUniform(1, 0x7d1);
  unknown88[0].createUniform(3, 1);
  unknown108[0].createUniform(2, 1);
  unknown188[0].createUniform(4, 1);
  unknown88[1].createUniform(3, 1);
  unknown108[1].createUniform(2, 1);
  unknown188[1].createUniform(4, 1);
  unknown20c = false;
}

void ComputeManager::termSub() {
  unknown08.releaseUniform();
  unknown48.releaseUniform();
  unknown88[0].releaseUniform();
  unknown108[0].releaseUniform();
  unknown188[0].releaseUniform();
  unknown88[1].releaseUniform();
  unknown108[1].releaseUniform();
  unknown188[1].releaseUniform();
}

void ComputeManager::update(u32 viewIndex) {
  unknown208 = viewIndex != 0;
  unknown88[viewIndex != 0].createParticlesUniform();
  unknown108[unknown208].createParticlesUniform();
  unknown188[unknown208].createParticlesUniform();
  if (!unknown20c) {
    unknown48.createParticlesUniform();
    unknown20c = true;
  }
  unknown08.createParticlesUniform();
  calculateParticle();
}

} // namespace emitter
} // namespace ptlib
