#include <math.h>
#include <string.h>

#include "mm_math/mm_col4.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mm_math/mm_vec3_na.h"
#include "ptlib/emitter/particle_emitter.h"
#include "ptlib/emitter/particle_emitter_ext.h"
#include "ptlib/emitter/particle_emitter_manager.h"
#include "ptlib/emitter/particle_emitter_param.h"
#include "ptlib/emitter/particle_emitter_particle.h"
#include "ptlib/math/particle_keyframe_ip.h"
#include "ptlib/particle_intrusive_list.h"
#include "ptlib/particle_math.h"
#include "ptlib/particle_noise.h"
#include "ptlib/particle_system.h"
#include "types.h"

namespace ptlib {

namespace emitter {

namespace {

// Inferred role: wraps an angle back into [-pi, pi] after one step; original name unknown.
inline f32 unknown007(f32 angle) {
  if (angle > 3.1415927f) {
    angle -= 6.2831855f;
  } else if (angle < -3.1415927f) {
    angle += 6.2831855f;
  }
  return angle;
}

// Inferred role: wind direction modes that keep the direction as is; original name unknown.
constexpr u32 MASK_UNKNOWN_3329 = 0xd01;

} // namespace

f32 EmitterObj::getEmitterScale() {
  f32 scale = 1.0f;
  if (unknownc0 != nullptr) {
    scale = unknownc0->unknown88;
    if (unknownc0->unknown00 == nullptr) {
      scale = 1.0f;
    }
  }
  return scale * m_param.unknown6c;
}

ParticleObj::ParticleObj() {
  unknown00 = this;
  unknown08 = this;
  unknown001();
}

ParticleObj::~ParticleObj() {}

void ParticleObj::free_plight() {}

void ParticleObj::freeUtilObj() {
  if (m_extParam != nullptr) {
    if (unknown13e != 0) {
      ParticleManager::get()->deleteMdl(m_extParam->unknown110);
      m_extParam->unknown110 = nullptr;
      unknown13e = 0;
    }
    if (unknown144 != 0) {
      ParticleManager::get()->deleteLgt(m_extParam->unknown110_u8, m_extParam->unknown108);
      m_extParam->unknown110_u8 = 0;
      m_extParam->unknown108 = nullptr;
      unknown144 = 0;
    }
  }
}

void ParticleObj::particle_clear_union() {
  if (unknown13e != 0) {
    if (m_extParam->unknown110 != nullptr) {
      ParticleManager::deleteMdl(m_extParam->unknown110);
      m_extParam->unknown110 = nullptr;
    }
    unknown13e = 0;
  }
  if (unknown144 != 0) {
    void *light = m_extParam->unknown108;
    if (light != nullptr) {
      ParticleManager::deleteLgt(m_extParam->unknown110_u8, light);
      m_extParam->unknown108 = nullptr;
    }
    unknown144 = 0;
  }
  m_extParam->m_emParent = nullptr;
  m_extParam->unknown108 = nullptr;
  m_extParam->unknown110 = nullptr;
  m_extParam->unknown118 = nullptr;
  m_extParam->unknown120 = nullptr;
  freeUtilObj();
}

void ParticleObj::addCalcTbl(mm::Vec3 &vector, f32 scale) {
  unknown10.x += vector.x * scale;
  unknown10.y += vector.y * scale;
  unknown10.z += vector.z * scale;
}

void ParticleObj::move_common_keyframe_uv23(vec2f *uv0, vec2f *uv1, f32 *rotation, EmitterObj *emitter, int index, f32 frame) {
  math::KeyFrameIP keyFrame;
  // The second and third uv layers use the keyframe channels from 5 on.
  emitter->unknown98->get_kf(&keyFrame,
                             emitter->unknown98->unknown18c[index].unknown04,
                             10,
                             frame,
                             m_extParam->unknown214[6 + index],
                             &m_extParam->unknown190[5] + index,
                             &unknownd8[5] + index,
                             (&emitter->unknown2b8[5])[index]);
  keyFrame.setup_keyrand(&m_extParam->unknown190[5] + index, 5, emitter->unknown268);
  keyFrame.get_ip2(uv0, 0);
  keyFrame.get_ip2(uv1, 4);
  *rotation = keyFrame.get_ip1(8);
}

void ParticleObj::move01_common_posVec(EmitterObj *emitter, int isFit) {
  EmitterManager *manager = EmitterManager::getPtr();
  f32 speed = emitter->m_param.speed * manager->unknown1700[emitter->m_param.unknown90];
  mm::Vec3 offset;
  offset.x = unknownac.x * unknown30.x;
  offset.y = unknownac.x * unknown30.y;
  offset.z = unknownac.x * unknown30.z;
  calcGravity(emitter, speed, offset);
  calcWind(emitter, offset);
  calcNoise(emitter, offset);
  calcVortex2(emitter, offset);
  calcNewton(emitter, offset);
  unknown10.x += speed * offset.x;
  unknown10.y += speed * offset.y;
  unknown10.z += speed * offset.z;
  calcIsFit(isFit, emitter, offset);
}

void ParticleObj::emitter_create_local_common_grav_wind(EmitterObj *emitter) {
  unknown004 *gravity = emitter->unknown1c8;
  if (gravity != nullptr) {
    m_extParam->unknown20 = gravity->unknown14 + gravity->unknown18 * math::unknown001(emitter->unknown268);
    m_extParam->unknown10 = mm::Vec3::zero;
  }
  unknown012 *wind = emitter->unknown1f0;
  if (wind != nullptr) {
    mm::Vec3 direction(wind->unknown0c.x, wind->unknown0c.y, wind->unknown0c.z);
    f32 strength = wind->unknown18;
    u16 mode = wind->unknown06;
    if (mode > 11 || (MASK_UNKNOWN_3329 & (1 << mode)) == 0) {
      const mm::Mat44 &matrix = emitter->unknownc0->unknown10;
      direction = mm::Vec3(direction.x * matrix.rows[0][0] + direction.y * matrix.rows[1][0] + direction.z * matrix.rows[2][0],
                           direction.x * matrix.rows[0][1] + direction.y * matrix.rows[1][1] + direction.z * matrix.rows[2][1],
                           direction.x * matrix.rows[0][2] + direction.y * matrix.rows[1][2] + direction.z * matrix.rows[2][2]);
    }
    m_extParam->unknown30 = mm::Vec3(strength * direction.x, strength * direction.y, strength * direction.z);
  }
  if (emitter->unknown1f8 != nullptr) {
    m_extParam->unknown40 = mm::Vec3::zero;
  }
}

void ParticleObj::calcGravity(EmitterObj *emitter, f32 speed, mm::Vec3 &result) {
  unknown004 *gravity = emitter->unknown1c8;
  if (gravity != nullptr) {
    if (move_common_check_begin_end(emitter, gravity->unknown00, gravity->unknown02, gravity->unknown04)) {
      ExtObj *ext = m_extParam;
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

void ParticleObj::calcWind(EmitterObj *emitter, mm::Vec3 &result) {
  unknown012 *wind = emitter->unknown1f0;
  if (wind != nullptr) {
    f32 rate = move_common_check_begin_end_fin_fout(emitter, wind->unknown00, wind->unknown02, wind->unknown08, wind->unknown0a, wind->unknown04);
    f32 force = rate * emitter->getEmitterScale();
    if (force > 0.0f) {
      result.x += force * m_extParam->unknown30.x;
      result.y += force * m_extParam->unknown30.y;
      result.z += force * m_extParam->unknown30.z;
    }
  }
}

void ParticleObj::calcNoise(EmitterObj *emitter, mm::Vec3 &result) {
  unknown013 *noise = emitter->unknown1f8;
  if (noise != nullptr) {
    f32 rate = move_common_check_begin_end_fin_fout(emitter, noise->unknown00, noise->unknown02, noise->unknown08, noise->unknown0a, noise->unknown04);
    f32 force = rate * emitter->getEmitterScale();
    if (force > 0.0f) {
      mm::Vec3 turbulence;
      TurbulenceN::turb3d(turbulence, unknown10, noise->unknown0c, noise->unknown10, noise->unknown06);
      m_extParam->unknown40 += turbulence;
      result.x += force * m_extParam->unknown40.x;
      result.y += force * m_extParam->unknown40.y;
      result.z += force * m_extParam->unknown40.z;
    }
  }
}

void ParticleObj::calcParRot(math::KeyFrameIP &keyFrame, f32 frame, EmitterObj *emitter, bool isCreate, f32 speed) {
  EmitterArg *arg = emitter->unknown98;
  if (arg->unknownc6 == 0) {
    return;
  }
  arg->get_kf(&keyFrame, arg->unknownc6, 6, frame, m_extParam->unknown214[2], &m_extParam->unknown190[2], &unknownd8[2], emitter->unknown2b8[2]);
  if (arg->unknownc5 == 0 && isCreate) {
    keyFrame.keyrand_get_ip3(&unknown94, &m_extParam->unknown190[2], emitter->unknown268);
    return;
  }
  mm::Vec3 rotation;
  keyFrame.keyrand_get_ip3(&rotation, &m_extParam->unknown190[2], emitter->unknown268);
  rotation.x *= speed;
  rotation.y *= speed;
  rotation.z *= speed;
  if (arg->unknownc5 != 1) {
    if (arg->unknownc5 != 2) {
      return;
    }
    u8 flip = unknownc2;
    if (flip & 1) {
      rotation.x = -rotation.x;
    }
    if (flip & 2) {
      rotation.y = -rotation.y;
    }
    if (flip & 4) {
      rotation.z = -rotation.z;
    }
  }
  unknown94.x = unknown007(rotation.x + unknown94.x);
  unknown94.y = unknown007(rotation.y + unknown94.y);
  unknown94.z = unknown007(rotation.z + unknown94.z);
}

void ParticleObj::calcParPivot(math::KeyFrameIP &keyFrame, f32 frame, EmitterObj *emitter) {
  u16 offset = emitter->unknown98->unknowne2;
  if (offset != 0) {
    emitter->unknown98->get_kf(&keyFrame, offset, 6, frame, m_extParam->unknown214[3], &m_extParam->unknown190[3], &unknownd8[3], emitter->unknown2b8[3]);
    keyFrame.keyrand_get_ip3(&unknowna0, &m_extParam->unknown190[3], emitter->unknown268);
  }
}

void ParticleObj::calcNewton(EmitterObj *emitter, mm::Vec3 &result) {
  unknown005 *newton = emitter->unknown1d0;
  if (newton != nullptr) {
    if (move_common_check_begin_end(emitter, newton->unknown00, newton->unknown02, newton->unknown04)) {
      mm::Vec3 direction;
      direction.x = unknown10.x - emitter->unknown1e0.x;
      direction.y = unknown10.y - emitter->unknown1e0.y;
      direction.z = unknown10.z - emitter->unknown1e0.z;
      f32 distanceSquared = direction.x * direction.x + direction.y * direction.y + direction.z * direction.z;
      f32 distance = sqrtf(distanceSquared);
      if (distance > newton->unknown14) {
        f32 strength = newton->unknown18;
        f32 power = powf(distance, newton->unknown1c);
        f32 length = sqrtf(distanceSquared);
        strength = strength * power;
        if (length <= 1e-06f) {
          direction = mm::Vec3::zero;
        } else {
          f32 inverse = 1.0f / length;
          direction.x = direction.x * inverse;
          direction.y = direction.y * inverse;
          direction.z = direction.z * inverse;
        }
        mm::Vec3 force = direction * strength;
        ExtObj *ext = m_extParam;
        ext->unknown90 -= force;
      }
      result.x = m_extParam->unknown90.x + result.x;
      result.y = m_extParam->unknown90.y + result.y;
      result.z = m_extParam->unknown90.z + result.z;
    }
  }
}

void ParticleObj::calcIsFit(int isFit, EmitterObj *emitter, mm::Vec3 &direction) {
  // The original reads the fit mode of the emitter argument even when the argument is null (original bug, reproduced).
  if (isFit != 0 && (emitter->unknown98 == nullptr || emitter->unknown98->unknown00 != 4) && (emitter->unknown98->unknownc4 == 8 || emitter->unknown98->unknownc4 == 9)) {
    if (emitter->unknown98->unknown09 != 0 && emitter->unknown80 != nullptr && emitter->unknown80->getExtParam().getEmParent() != nullptr && emitter->unknown88 == emitter->unknown80->unknown138 &&
        emitter->unknown80->getExtParam().getEmParent()->unknown98 != nullptr && (emitter->unknown80->getExtParam().getEmParent()->unknown98->unknownc4 & 8) != 0) {
      unknown94.x = emitter->unknown80->unknown94.x;
      unknown94.y = emitter->unknown80->unknown94.y;
    } else {
      calc_fit(unknown94.x, unknown94.y, &direction);
    }
  }
}

void ParticleObj::calcSpeedKeyframe(EmitterObj *emitter, math::KeyFrameIP &keyFrame, f32 frame, f32 emitterFrame) {
  unknown006 *speed = emitter->unknown1c0;
  if (speed == nullptr) {
    return;
  }
  EmitterArg *arg = emitter->unknown98;
  if (emitter->unknown280 > 1.0f) {
    f32 start = frame - emitter->unknown280 * unknownbc;
    if (start <= 0.0f) {
      start = 1.0f;
    }
    if (speed->unknown0c != 0) {
      unknownd8[0] = &arg->unknown24c[speed->unknown0c];
    } else if (speed->unknown08 != 0) {
      unknownd8[0] = &arg->unknown24c[speed->unknown08];
    } else if (speed->unknown0a != 0) {
      unknownd8[0] = &arg->unknown24c[speed->unknown0a];
    }
    unknownac.x = 0.0f;
    while (start <= frame) {
      f32 value = 1.0f;
      int hasKey = 0;
      if (speed->unknown0c != 0) {
        arg->get_kf(&keyFrame, speed->unknown0c, 2, frame, m_extParam->unknown214[0], &m_extParam->unknown190[0], &unknownd8[0], emitter->unknown2b8[0]);
        value = keyFrame.keyrand_get_ip1(&m_extParam->unknown190[0], emitter->unknown268);
        hasKey = 1;
      }
      if (speed->unknown08 != 0) {
        value *= unknownac.z;
      } else if (speed->unknown0a != 0) {
        arg->get_kf(&keyFrame, speed->unknown0a, 2, emitterFrame, emitter->unknown250[3], &emitter->unknown220[0], &unknownd8[0], emitter->unknown2b8[0]);
        value *= keyFrame.keyrand_get_ip1(&emitter->unknown220[0], emitter->unknown268);
      } else if (!hasKey) {
        value = unknownac.y;
      }
      unknownac.x += value * emitter->getEmitterScale();
      start += 1.0f;
    }
  } else {
    f32 value = 1.0f;
    int hasKey = 0;
    if (speed->unknown0c != 0) {
      arg->get_kf(&keyFrame, speed->unknown0c, 2, frame, m_extParam->unknown214[0], &m_extParam->unknown190[0], &unknownd8[0], emitter->unknown2b8[0]);
      value = keyFrame.keyrand_get_ip1(&m_extParam->unknown190[0], emitter->unknown268);
      hasKey = true;
    }
    if (speed->unknown08 != 0) {
      value *= unknownac.z;
    } else if (speed->unknown0a != 0) {
      arg->get_kf(&keyFrame, speed->unknown0a, 2, emitterFrame, emitter->unknown250[3], &emitter->unknown220[0], &unknownd8[0], emitter->unknown2b8[0]);
      value *= keyFrame.keyrand_get_ip1(&emitter->unknown220[0], emitter->unknown268);
    } else if (!hasKey) {
      value = unknownac.y;
    }
    unknownac.x = value * emitter->getEmitterScale();
  }
}

void ParticleObj::calcSpeed(EmitterObj *emitter, math::KeyFrameIP &keyFrame, f32 frame) {
  unknown006 *speed = emitter->unknown1c0;
  if (speed == nullptr) {
    return;
  }
  if (speed->unknown0c != 0) {
    emitter->unknown98->get_kf(&keyFrame, speed->unknown0c, 2, frame, m_extParam->unknown214[0], &m_extParam->unknown190[0], &unknownd8[0], emitter->unknown2b8[0]);
    unknownac.x = keyFrame.keyrand_get_ip1(&m_extParam->unknown190[0], emitter->unknown268) * emitter->getEmitterScale();
  } else {
    unknownac.x = unknownac.y * emitter->getEmitterScale();
  }
}

void ParticleObj::calcTurb(mm::Vec3 &result, f32 frequency, f32 amplitude, int octaves) { TurbulenceN::turb3d(result, unknown10, frequency, amplitude, octaves); }

void ParticleObj::calcExternalColor(mm::Vec3 &color, EmitterObj *emitter, f32 &alpha, int isFirst, int isSecond) {
  if (emitter->unknown98->unknown109 != 0) {
    color.x = m_extParam->unknown130.x * emitter->m_param.unknown40.r;
    color.y = m_extParam->unknown130.y * emitter->m_param.unknown40.g;
    color.z = m_extParam->unknown130.z * emitter->m_param.unknown40.b;
    alpha = m_extParam->unknown174 * emitter->m_param.unknown40.a;
    m_extParam->unknown17c_u32 = Utility::conv_rgba(&color, alpha);
  } else if (isFirst != 0) {
    m_extParam->unknown17c_u32 = Utility::conv_rgba(&m_extParam->unknown130, m_extParam->unknown174);
  }
  if (isSecond != 0) {
    mm::Vec3 second;
    second.x = m_extParam->unknown140.x * emitter->m_param.unknown40.r;
    second.y = m_extParam->unknown140.y * emitter->m_param.unknown40.g;
    second.z = m_extParam->unknown140.z * emitter->m_param.unknown40.b;
    m_extParam->unknown180_u32 = Utility::conv_rgba(&second, m_extParam->unknown174 * emitter->m_param.unknown40.a);
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

bool ParticleObj::move_common_life(int isMove, f32 speed) {
  if (isMove == 0) {
    return false;
  }
  if (unknownc0 == 0x7fff) {
    return false;
  }
  int step = static_cast<int>(speed);
  if (step < 1) {
    step = 1;
  }
  unknownc0 -= step;
  if (static_cast<s16>(unknownc0) < 1) {
    unknownc0 = 0;
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

ParticleObj *EmitterObj::move_type1_sort(ParticleObj **table, EmitterObj *emitter) {
  if (table != nullptr) {
    memset(table, 0, sizeof(ParticleObj *) * 100);
  }
  ParticleObj *top = nullptr;
  for (IntrusiveList<ParticleObj>::iterator it = emitter->unknown40.begin(); it != emitter->unknown40.end(); ++it) {
    ParticleObj &particle = *it;
    if (table != nullptr) {
      if (particle.unknownc0 > 100) {
        top = &particle;
      } else {
        table[static_cast<s16>(particle.unknownc0) - 1] = &particle;
      }
    } else if (particle.unknownc0 > 100) {
      return &particle;
    }
  }
  return top;
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
    f32 position = m_extParam->unknown22c + m_extParam->unknownfc;
    while (1.0f < position) {
      position -= 1.0f;
    }
    m_extParam->unknown22c = position;
    if (1e-06f < m_extParam->unknown22c) {
      m_extParam->unknown230 = 1;
    }
  }
}

void ParticleObj::move01_common_keyframe(EmitterObj *emitter, f32 speed, int isMove) {
  f32 frame = move_common_keyframe_life(emitter);
  f32 emitterFrame = emitter->unknown18c;
  math::KeyFrameIP keyFrame;
  calcSpeedKeyframe(emitter, keyFrame, frame, emitterFrame);
  calcParSize(isMove, emitter, keyFrame, frame, emitterFrame, true);
  calcParRot(keyFrame, frame, emitter, true, speed);
  EmitterArg *arg = emitter->unknown98;
  if (arg->unknowne2 != 0) {
    arg->get_kf(&keyFrame, arg->unknowne2, 6, frame, m_extParam->unknown214[3], &m_extParam->unknown190[3], &unknownd8[3], emitter->unknown2b8[3]);
    keyFrame.keyrand_get_ip3(&unknowna0, &m_extParam->unknown190[3], emitter->unknown268);
  }
  move_common_keyframe_uv1_full(emitter, frame, speed);
  calcMatColor(frame, keyFrame, emitter, emitterFrame, true);
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
