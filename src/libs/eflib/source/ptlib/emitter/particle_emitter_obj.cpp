#include <string.h>

#include "mm_math/mm_vec3.h"
#include "ptlib/emitter/particle_emitter.h"
#include "ptlib/emitter/particle_emitter_ext.h"
#include "ptlib/emitter/particle_emitter_param.h"
#include "ptlib/emitter/particle_emitter_particle.h"
#include "ptlib/particle_intrusive_list.h"
#include "ptlib/particle_math.h"
#include "ptlib/particle_system.h"
#include "ptlib/renderer/particle_renderer_stream.h"
#include "types.h"

namespace ptlib {
namespace renderer {
class RenderSet;
} // namespace renderer

namespace emitter {

int EmitterObj::getParentParticleState() const {
  if (unknown80 == nullptr) {
    return 0;
  }
  if (unknown80->unknown130->unknown08 != nullptr) {
    if (unknown88 != unknown80->unknown138) {
      return 2;
    }
    return 1;
  }
  return 2;
}

EmitterObj *EmitterObj::emitter_free() {
  unknown26c_4 = 1;
  unknownc0->unknown00 = nullptr;
  return static_cast<EmitterObj *>(unknown00);
}

void EmitterObj::emitter_dead(u8 value) {
  unknown188 = value;
  for (IntrusiveList<ParticleObj>::iterator it = unknown40.begin(); it != unknown40.end(); ++it) {
    if (it->unknownc0 == 0x7fff) {
      it->unknownc0 = 0;
    }
  }
}

void EmitterObj::calc_scale(mm::Vec3 *result, math::Vec3r *range, f32 scale, u32 &seed) {
  f32 x = range->unknown0c * math::unknown001(seed);
  f32 y = range->unknown10 * math::unknown001(seed);
  f32 z = range->unknown14 * math::unknown001(seed);
  result->x = (range->unknown00 + x) * scale;
  result->y = (range->unknown04 + y) * scale;
  result->z = (range->unknown08 + z) * scale;
}

void EmitterObj::emitter_set_param_sub_pos_only(EmitterParam *param) {
  if (unknown80 == nullptr) {
    memcpy(&unknowne0, param, sizeof(unknown001));
  }
  ParticleManager::get()->update_model_spd(this, 1.0f);
}

void EmitterObj::emitter_alloc01_set_move(FxHeader *header, EmitterArg *arg) {
  unknownd0 = 0;
  unknownd4 = 1;
  switch (arg->unknown00) {
  case 1:
    unknownd0 = 2;
    break;
  case 4:
    unknownd0 = 4;
    break;
  case 5:
    unknownd0 = 5;
    break;
  case 9:
    unknownd0 = 3;
    break;
  case 0xc:
  case 0xd:
    unknownd0 = 6;
    break;
  default:
    unknownd0 = 1;
    break;
  }
}

f32 EmitterObj::calc_fade() {
  if (unknown182 != 0) {
    return static_cast<f32>(unknown181) / unknown182;
  }
  return 1.0f;
}

void *EmitterObj::lockStream(const DrDrawWorkInfoEF *info) { return unknown60->lockStream(info); }

void EmitterObj::unlockStream(const DrDrawWorkInfoEF *info, u32 count) { unknown60->unlockStream(info, count); }

void EmitterObj::renderStreamNum(renderer::RenderSet &renderSet, const DrDrawWorkInfoEF *info) {
  if (unknown60 != nullptr) {
    unknown60->renderStreamNum(renderSet, info);
  }
}

void EmitterObj::releaseStream() {
  if (unknown60 != nullptr) {
    unknown60->release();
  }
}

} // namespace emitter
} // namespace ptlib
