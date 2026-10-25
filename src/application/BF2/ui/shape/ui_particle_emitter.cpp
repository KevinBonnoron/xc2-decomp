#include "ui/shape/ui_particle_emitter.h"

namespace ui {

UIParticleEmitter::~UIParticleEmitter() {
  if (unknowne0.capacity() != 0) {
    unknowne0.destroy();
  }
}

} // namespace ui
