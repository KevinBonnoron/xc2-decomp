#include "ui/shape/ui_particle_manager.h"

#include "mm_math/mm_pnt.h"
#include "mm_mtl/vector.h"
#include "ui/shape/ui_particle_emitter.h"

namespace ui {

UIParticleManager::UIParticleManager() : unknown20(1), m_loadReduction(0.0f) {}

UIParticleManager::~UIParticleManager() {
  if (unknown08.size() != 0) {
    for (mm::mtl::IntrusiveList<EmitterInfo>::iterator it = unknown08.begin(); it != unknown08.end();) {
      EmitterInfo *info = it.get();
      it = unknown08.erase(it);
      if (info->unknown18 != nullptr) {
        delete info->unknown18;
        info->unknown18 = nullptr;
      }
      delete info;
    }
  }
}

void UIParticleManager::remove(int emitter) {
  for (mm::mtl::IntrusiveList<EmitterInfo>::iterator it = unknown08.begin(); it != unknown08.end(); ++it) {
    EmitterInfo &info = *it;
    if (info.unknown10 == emitter) {
      unknown08.erase(it);
      if (info.unknown18 != nullptr) {
        delete info.unknown18;
        info.unknown18 = nullptr;
      }
      delete &info;
      return;
    }
  }
}

UIParticleEmitter *UIParticleManager::getEmitter(int emitter) {
  for (mm::mtl::IntrusiveList<EmitterInfo>::iterator it = unknown08.begin(); it != unknown08.end(); ++it) {
    EmitterInfo &info = *it;
    if (info.unknown10 == emitter) {
      return info.unknown18;
    }
  }
  return nullptr;
}

void UIParticleManager::setEmitterPos(int emitter, const mm::Pnt<s16> &pos) {
  for (mm::mtl::IntrusiveList<EmitterInfo>::iterator it = unknown08.begin(); it != unknown08.end(); ++it) {
    EmitterInfo &info = *it;
    if (info.unknown10 == emitter) {
      UIParticleEmitter *emitter = info.unknown18;
      emitter->unknown10 = static_cast<f32>(pos.x);
      emitter->unknown14 = static_cast<f32>(pos.y);
    }
  }
}

void UIParticleManager::setEmitterRot(int emitter, f32 rot) {
  for (mm::mtl::IntrusiveList<EmitterInfo>::iterator it = unknown08.begin(); it != unknown08.end(); ++it) {
    EmitterInfo &info = *it;
    if (info.unknown10 == emitter) {
      info.unknown18->unknown20 = rot;
    }
  }
}

void UIParticleManager::setActivate(int emitter, bool activate) {
  for (mm::mtl::IntrusiveList<EmitterInfo>::iterator it = unknown08.begin(); it != unknown08.end(); ++it) {
    EmitterInfo &info = *it;
    if (info.unknown10 == emitter) {
      info.unknown18->unknown108 = activate;
    }
  }
}

bool UIParticleManager::isActive(int emitter) const {
  bool active = false;
  for (mm::mtl::IntrusiveList<EmitterInfo>::iterator it = unknown08.begin(); it != unknown08.end(); ++it) {
    EmitterInfo &info = *it;
    if (info.unknown10 == emitter) {
      active = info.unknown18->unknown108;
      break;
    }
  }
  return active;
}

void UIParticleManager::setLoadReduction(f32 reduction) {
  for (mm::mtl::IntrusiveList<EmitterInfo>::iterator it = unknown08.begin(); it != unknown08.end(); ++it) {
    f32 scale = (1.0f - reduction) + (1.0f - (1.0f - reduction)) * it->unknown14;
    if (scale <= 0.3f) {
      scale = 0.3f;
    }
    it->unknown18->unknown08 = scale;
  }
  m_loadReduction = reduction;
}

void UIParticleManager::update(const fw::UpdateInfo &info) {
  for (mm::mtl::IntrusiveList<EmitterInfo>::iterator it = unknown08.begin(); it != unknown08.end(); ++it) {
    EmitterInfo &emitter = *it;
    emitter.unknown18->update(info);
  }
}

int UIParticleManager::getAllEmissionCount() {
  int count = 0;
  for (mm::mtl::IntrusiveList<EmitterInfo>::iterator it = unknown08.begin(); it != unknown08.end(); ++it) {
    EmitterInfo &info = *it;
    count += static_cast<int>(info.unknown18->unknowne0.size());
  }
  return count;
}

} // namespace ui
