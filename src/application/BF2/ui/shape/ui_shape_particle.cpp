#include "ui/shape/ui_shape_particle.h"

#include "ui/shape/ui_particle_manager.h"

namespace ui {

UIShapeParticle::~UIShapeParticle() {
  if (unknown40 != -1) {
    UIParticleManager::get()->remove(unknown40);
  }
}

void UIShapeParticle::activate(bool activate) { UIParticleManager::get()->setActivate(unknown40, activate); }

bool UIShapeParticle::isActive() const { return UIParticleManager::get()->isActive(unknown40); }

const mm::mtl::RTTI *UIShapeParticle::getRTTI() const { return &m_rtti; }

} // namespace ui
