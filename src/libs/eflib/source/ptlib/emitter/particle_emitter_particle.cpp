#include <math.h>

#include "mm_math/mm_vec3.h"
#include "ptlib/emitter/particle_emitter.h"
#include "ptlib/emitter/particle_emitter_ext.h"
#include "ptlib/emitter/particle_emitter_particle.h"
#include "ptlib/particle_intrusive_list.h"
#include "ptlib/particle_system.h"
#include "types.h"

namespace ptlib {
namespace emitter {

f32 EmitterObj::getEmitterScale() {
  f32 scale = 1.0f;
  if (unknownc0 != nullptr) {
    scale = unknownc0->unknown88;
    if (unknownc0->unknown00 == nullptr) {
      scale = 1.0f;
    }
  }
  return scale * unknown14c;
}

ParticleObj::~ParticleObj() {}

void ParticleObj::free_plight() {}

void ParticleObj::freeUtilObj() {
  if (unknown130 != nullptr) {
    if (unknown13e != 0) {
      ParticleManager::get()->deleteMdl(unknown130->unknown110);
      unknown130->unknown110 = nullptr;
      unknown13e = 0;
    }
    if (unknown144 != 0) {
      ParticleManager::get()->deleteLgt(unknown130->unknown110_u8, unknown130->unknown108);
      unknown130->unknown110_u8 = 0;
      unknown130->unknown108 = nullptr;
      unknown144 = 0;
    }
  }
}

void ParticleObj::particle_clear_union() {
  if (unknown13e != 0) {
    if (unknown130->unknown110 != nullptr) {
      ParticleManager::deleteMdl(unknown130->unknown110);
      unknown130->unknown110 = nullptr;
    }
    unknown13e = 0;
  }
  if (unknown144 != 0) {
    void *light = unknown130->unknown108;
    if (light != nullptr) {
      ParticleManager::deleteLgt(unknown130->unknown110_u8, light);
      unknown130->unknown108 = nullptr;
    }
    unknown144 = 0;
  }
  unknown130->unknown08 = nullptr;
  unknown130->unknown108 = nullptr;
  unknown130->unknown110 = nullptr;
  unknown130->unknown118 = nullptr;
  unknown130->unknown120 = nullptr;
  freeUtilObj();
}

void ParticleObj::addCalcTbl(mm::Vec3 &vector, f32 scale) {
  unknown10.x += vector.x * scale;
  unknown10.y += vector.y * scale;
  unknown10.z += vector.z * scale;
}

void ParticleObj::calcGravity(EmitterObj *emitter, f32 speed, mm::Vec3 &result) {
  unknown004 *gravity = emitter->unknown1c8;
  if (gravity != nullptr) {
    if (move_common_check_begin_end(emitter, gravity->unknown00, gravity->unknown02, gravity->unknown04)) {
      ExtObj *ext = unknown130;
      f32 force = ext->unknown20 * speed * emitter->getEmitterScale();
      f32 x = ext->unknown10.x + force * gravity->unknown08;
      f32 y = ext->unknown10.y + force * gravity->unknown0c;
      f32 z = ext->unknown10.z + force * gravity->unknown10;
      ext->unknown10.x = x;
      ext->unknown10.y = y;
      ext->unknown10.z = z;
      result.x = x + result.x;
      result.y = y + result.y;
      result.z = z + result.z;
    }
  }
}

void ParticleObj::calc_fit(f32 &pitch, f32 &yaw, const mm::Vec3 *direction) {
  f32 y = direction->y;
  f32 length = sqrtf(direction->x * direction->x + direction->z * direction->z);
  pitch = -atan2f(y, length);
  yaw = atan2f(direction->x, direction->z);
}

bool ParticleObj::move_common_wait(int isMove, f32 speed) {
  if (isMove == 0) {
    return false;
  }
  if (unknownc3 != 0) {
    int step = 1;
    if (0 < static_cast<int>(speed)) {
      step = static_cast<int>(speed);
    }
    unknownc3 -= step;
    return true;
  }
  return false;
}

bool EmitterObj::localUpdateParticleObjLgt(ParticleObj *&particle, IntrusiveList<ParticleObj>::iterator &it, f32 speed, int isMove, int &count) {
  particle = it.get();
  if (particle->move_common_wait(isMove, speed)) {
    ++it;
    return true;
  }
  if (particle->move_common_life(isMove, speed)) {
    ++it;
    remove_particle_free_tbl(particle);
    return true;
  }
  count++;
  particle->unknownb8 += speed;
  return false;
}

bool EmitterObj::localUpdateParticleObjMdl(ParticleObj *&particle, IntrusiveList<ParticleObj>::iterator &it, f32 speed, int isMove, int &count) {
  particle = it.get();
  if (particle->move_common_wait(isMove, speed)) {
    ++it;
    return true;
  }
  if (particle->move_common_life(isMove, speed)) {
    ++it;
    remove_particle_free_tbl(particle);
    return true;
  }
  count++;
  particle->unknownb8 += speed;
  return false;
}

bool EmitterObj::localUpdateParticleObj(ParticleObj *&particle, IntrusiveList<ParticleObj>::iterator &it, f32 speed, int isMove, int &count) {
  particle = it.get();
  if (0.0001f < speed) {
    particle->unknown20 = particle->unknown10;
  }
  if (particle->move_common_wait(isMove, speed)) {
    ++it;
    return true;
  }
  if (particle->move_common_life(isMove, speed)) {
    ++it;
    remove_particle_free_tbl(particle);
    return true;
  }
  count++;
  particle->unknownb8 += speed;
  return false;
}

void ParticleObj::move_common_check_begin_end_sub(EmitterObj *emitter, int mode, u16 &begin, u16 &end) {
  if (static_cast<u32>(mode) < 2) {
    begin = static_cast<int>(emitter->unknown18c);
    end = emitter->unknown188;
    return;
  }
  begin = static_cast<int>(unknownb8 * unknownbc);
  end = static_cast<int>(static_cast<s16>(unknownc0) * unknownbc);
}

void ParticleObj::moveFlowMap(EmitterObj *emitter, int isMove) {
  if (isMove != 0) {
    f32 position = unknown130->unknown22c + unknown130->unknownfc;
    while (1.0f < position) {
      position -= 1.0f;
    }
    unknown130->unknown22c = position;
    if (1e-06f < unknown130->unknown22c) {
      unknown130->unknown230 = 1;
    }
  }
}

f32 ParticleObj::move_common_keyframe_life(EmitterObj *emitter) {
  f32 life = unknownb8;
  f32 frame = life * unknownbc;
  if (unknownc0 == 0x7fff) {
    if (emitter->unknown182 != 0 && emitter->unknown180 != 0) {
      frame = static_cast<int>((emitter->unknown182 | 0x10000) - emitter->unknown181);
    }
    if (32768.0f < life) {
      unknownb8 = life - 16384.0f;
    }
  }
  return frame;
}

} // namespace emitter
} // namespace ptlib
