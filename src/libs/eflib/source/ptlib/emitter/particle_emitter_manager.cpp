#include "ptlib/emitter/particle_emitter_manager.h"

#include <string.h>

#include "mm/mm_std_base.h"
#include "ptlib/emitter/particle_emitter.h"
#include "ptlib/emitter/particle_emitter_param.h"
#include "ptlib/emitter/particle_emitter_particle.h"
#include "ptlib/emitter/particle_emitter_set_node.h"
#include "ptlib/particle_system.h"
#include "ptlib/renderer/particle_renderer_stream.h"

namespace ptlib {

namespace emitter {

namespace {
EmitterManager *s_instance;
} // namespace

f32 EmitterObj::getCateSpd() {
  EmitterManager *manager = EmitterManager::getPtr();
  return manager->unknown1700[unknown170];
}

EmitterManager *EmitterManager::get() {
#line 21
  MM_ASSERT(getPtr());
  return getPtr();
}

EmitterManager *&EmitterManager::getPtr() { return s_instance; }

void EmitterManager::moveAfter() {}

IntrusiveList<EmitterObj> &EmitterManager::getEmitterActiveList() { return unknown17a8; }

IntrusiveList<EmitterObj>::iterator EmitterManager::getEmitterActiveIt(EmitterObj *emitter) { return unknown17a8.find(emitter); }

EmitterObj *EmitterManager::getEmitterFree() {
  if (unknown17c0.m_size == 0) {
    return nullptr;
  }
  IntrusiveList<EmitterObj>::iterator it = unknown17c0.begin();
  EmitterObj &emitter = *it;
  unknown17c0.erase(it);
  return &emitter;
}

void EmitterManager::addEmitterFree(EmitterObj *emitter) {
  if (emitter->unknown60 != nullptr) {
    emitter->unknown60->release();
  }
  emitter->releaseParticleAll();
  unknown17c0.push_back(emitter);
}

void EmitterManager::removeEmitterActive(EmitterObj *emitter) {
  if (emitter->unknown60 != nullptr) {
    emitter->unknown60->release();
  }
  emitter->releaseParticleAll();
  unknown17a8.erase(getEmitterActiveIt(emitter));
}

void EmitterManager::addEmitterActive(EmitterObj *emitter) { unknown17a8.push_back(emitter); }

void EmitterManager::addEmitterActiveAfterParent(EmitterObj *emitter, EmitterObj *parent) { unknown17a8.push_back(emitter); }

void EmitterManager::addFreeParticleFront(ParticleObj *particle) { unknown17d8.push_front(particle); }

void EmitterManager::addFreeParticleBack(ParticleObj *particle) { unknown17d8.push_back(particle); }

void EmitterManager::emitter_set_param_pos_only(u32 handle, EmitterParam *param) {
  for (IntrusiveList<EmitterObj>::iterator it = unknown17a8.begin(); it != unknown17a8.end(); ++it) {
    if (it->unknown264 == handle) {
      if (it->unknown80 == nullptr) {
        memcpy(&it->unknowne0, param, sizeof(unknown001));
      }
      ParticleManager::get()->update_model_spd(it.get(), 1.0f);
    }
  }
}

void EmitterManager::emitter_set_param(u32 handle, EmitterParam *param) {
  for (IntrusiveList<EmitterObj>::iterator it = unknown17a8.begin(); it != unknown17a8.end(); ++it) {
    if (it->unknown264 == handle) {
      it->emitter_set_param_sub(param);
    }
  }
  f32 skip = param->unknown7c;
  if (skip >= 1.0f) {
    int count = static_cast<int>(skip * 0.5f);
    if (count < 1) {
      count = 1;
    } else {
      skip = 2.0f;
    }
    for (int i = 0; i < count; i++) {
      emitter_update(handle, skip, false);
    }
  }
}

void EmitterManager::emitter_set_param(FxHeader *header, EmitterParam *param) {
  for (IntrusiveList<EmitterObj>::iterator it = unknown17a8.begin(); it != unknown17a8.end(); ++it) {
    if (it->unknown58 == header) {
      it->emitter_set_param_sub(param);
    }
  }
}

void EmitterManager::emitter_set_disp(u32 handle, int isDisp) {
  for (IntrusiveList<EmitterObj>::iterator it = unknown17a8.begin(); it != unknown17a8.end(); ++it) {
    if (it->unknown264 == handle) {
      it->unknown151 = isDisp;
    }
  }
}

void EmitterManager::emitter_set_alpha(u32 handle, f32 alpha) {
  for (IntrusiveList<EmitterObj>::iterator it = unknown17a8.begin(); it != unknown17a8.end(); ++it) {
    if (it->unknown264 == handle) {
      it->unknown12c = alpha;
    }
  }
}

void EmitterManager::emitter_set_category(u32 handle, u32 category) {
  for (IntrusiveList<EmitterObj>::iterator it = unknown17a8.begin(); it != unknown17a8.end(); ++it) {
    if (it->unknown264 == handle) {
      it->unknown170 = category;
    }
  }
}

void EmitterManager::emitter_set_nowait(u32 handle, int isNoWait) {
  for (IntrusiveList<EmitterObj>::iterator it = unknown17a8.begin(); it != unknown17a8.end(); ++it) {
    if (it->unknown264 == handle) {
      it->unknown152 = isNoWait;
    }
  }
}

void EmitterManager::emitter_set_viewnum(u32 handle, int viewnum) {
  for (IntrusiveList<EmitterObj>::iterator it = unknown17a8.begin(); it != unknown17a8.end(); ++it) {
    if (it->unknown264 == handle) {
      it->unknown274 = viewnum;
      it->unknown90 = ParticleManager::getGrp(viewnum & 0xff);
    }
  }
}

void EmitterManager::emitter_set_casparam(u32 handle, const void *model, EmitterParam *param) {
  for (IntrusiveList<EmitterObj>::iterator it = unknown17a8.begin(); it != unknown17a8.end(); ++it) {
    if (it->unknown264 == handle && it->unknown80 == nullptr) {
      it->unknownc0->unknown00 = model;
      it->unknownc0->unknown70[0] = 0;
      it->emitter_set_param_sub(param);
    }
  }
}

void *EmitterManager::createFunc(EmitterObj *emitter, ParticleObj *particle, f32 frame, int param) {
  if (particle->unknownd4 == 1) {
    return create_local01(emitter, particle, frame, param);
  }
  efAstMsg("0", "create func set error !!!");
  return nullptr;
}

void EmitterManager::emitter_set_casname(u32 handle, const void *model, const char *name, int index, f32 frame, int flags) {
  if (name != nullptr && strlen(name) >= 0x10) {
    efAstMsg("0", "emitter_set_casname:too long name[%s]", name);
  }
  for (IntrusiveList<EmitterObj>::iterator it = unknown17a8.begin(); it != unknown17a8.end(); ++it) {
    if (it->unknown264 == handle && it->unknown80 == nullptr) {
      if (model == nullptr) {
        it->unknownc0->unknown00 = nullptr;
        it->unknownc0->unknown70[0] = 0;
      } else {
        it->unknownc0->unknown00 = model;
        it->unknown14c = frame;
        it->unknown153 = flags;
        if (name != nullptr) {
          strcpy(it->unknownc0->unknown70, name);
        }
      }
    }
  }
}

bool EmitterManager::emitter_set_check(FxHeader *header) {
  for (IntrusiveList<EmitterSetNode>::iterator it = unknown17f0.begin(); it != unknown17f0.end(); ++it) {
    if (header != nullptr) {
      return true;
    }
  }
  return false;
}

void EmitterManager::emitter_pack_free(u64 pack) {
  int count = 0;
  for (IntrusiveList<EmitterSetNode>::iterator it = unknown17f0.begin(); it != unknown17f0.end(); ++it) {
    if (it->unknown18->unknown48 == pack) {
      count++;
    }
  }
  if (count > 0) {
    do {
      for (IntrusiveList<EmitterSetNode>::iterator it = unknown17f0.begin(); it != unknown17f0.end(); ++it) {
        if (it->unknown18->unknown48 == pack) {
          emitter_set_free(it->unknown18, 1);
          count--;
          break;
        }
      }
    } while (count > 0);
  }
}

void EmitterManager::emitter_set_speed(u32 handle, f32 speed) {
  for (IntrusiveList<EmitterObj>::iterator it = unknown17a8.begin(); it != unknown17a8.end(); ++it) {
    if (handle == 0 || it->unknown264 == handle) {
      it->unknown158 = speed;
    }
  }
}

} // namespace emitter
} // namespace ptlib
