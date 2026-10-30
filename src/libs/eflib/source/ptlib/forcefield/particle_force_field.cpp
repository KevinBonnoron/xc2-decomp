#include "ptlib/forcefield/particle_force_field.h"

#include <math.h>

#include "mm/mm_std_base.h"
#include "mm_math/mm_vec3.h"
#include "ptlib/emitter/particle_emitter.h"
#include "ptlib/emitter/particle_emitter_ext.h"
#include "ptlib/emitter/particle_emitter_particle.h"
#include "ptlib/particle_system.h"

namespace ptlib {
namespace forcefield {

namespace {
FfManager *s_ffInstance;

// Inferred role: normalizes a vector, zero when it is too short; original name unknown.
inline void unknown001(mm::Vec3 &vector) {
  f32 length = sqrtf(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
  if (length <= 1e-06f) {
    vector = mm::Vec3::zero;
  } else {
    f32 inverse = 1.0f / length;
    vector.x = vector.x * inverse;
    vector.y = vector.y * inverse;
    vector.z = vector.z * inverse;
  }
}

// Inferred role: tells whether every component of a vector is nearly zero; original name unknown.
inline bool unknown004(const mm::Vec3 &vector) { return fabsf(vector.x) <= 1e-06f && fabsf(vector.y) <= 1e-06f && fabsf(vector.z) <= 1e-06f; }

// Inferred role: tells whether two vectors are nearly equal; original name unknown.
inline bool unknown005(const mm::Vec3 &a, const mm::Vec3 &b) { return fabsf(a.x - b.x) <= 1e-06f && fabsf(a.y - b.y) <= 1e-06f && fabsf(a.z - b.z) <= 1e-06f; }

// Inferred role: clears the vectors of a particle hit by a force field; original name unknown.
inline void unknown006(emitter::ParticleObj *particle) {
  particle->getExtParam().unknown50 = mm::Vec3::zero;
  particle->getExtParam().unknown70 = mm::Vec3::zero;
  particle->getExtParam().unknown30 = mm::Vec3::zero;
}
} // namespace

FfManager *FfManager::get() {
#line 52
  MM_ASSERT(getPtr());
  return getPtr();
}

FfManager *&FfManager::getPtr() { return s_ffInstance; }

void FfManager::initSub() { unknown00.clear(); }

void FfManager::termSub() {
  for (unknown002 **it = unknown00.begin(); it != unknown00.end(); ++it) {
    if (*it != nullptr) {
      ParticleManager::sysFree(*it);
    }
  }
  unknown00.clear();
}

void FfManager::update(f32 speed) {
  for (unknown002 **it = unknown00.begin(); it != unknown00.end();) {
    unknown002 *force = *it;
    force->unknown00 += static_cast<int>(speed);
    if (force->unknown10.unknown06 != -1 && force->unknown10.unknown06 <= force->unknown00) {
      it = unknown00.erase(it);
      if (force != nullptr) {
        ParticleManager::sysFree(force);
      }
    } else {
      ++it;
    }
  }
}

void FfManager::moveForce(emitter::ParticleObj *particle) {
  if (particle->getExtParam().getEmParent() == nullptr) {
    return;
  }
  particle->unknown40 *= 0.95f;
  particle->unknown50 *= 0.95f;
  if (particle->getExtParam().unknownb2 != 0) {
    particle->getExtParam().unknownb2--;
  }
  for (unknown002 **it = unknown00.begin(); it != unknown00.end(); ++it) {
    unknown002 *force = *it;
    if (force->unknown10.unknown04 > force->unknown00) {
      continue;
    }
    emitter::EmitterObj *emitter = particle->getExtParam().getEmParent();
    if (emitter != nullptr && emitter->unknown98 != nullptr && emitter->unknown98->unknown08) {
      continue;
    }
    switch (force->unknown10.unknown00) {
    case 1:
      particle->unknown40 += mm::Vec3(force->unknown30.x, force->unknown30.y, force->unknown30.z);
      break;
    case 2:
      particle->unknown40 += mm::Vec3(force->unknown30.x, force->unknown30.y, force->unknown30.z);
      break;
    case 3: {
      mm::Vec3 center(force->unknown20.x, force->unknown20.y, force->unknown20.z);
      mm::Vec3 direction = particle->unknown10 - center;
      if (direction.x * direction.x + direction.y * direction.y + direction.z * direction.z < force->unknown40 * force->unknown40) {
        unknown006(particle);
        unknown001(direction);
        mm::Vec3 power(force->unknown30.x, force->unknown30.y, force->unknown30.z);
        particle->unknown40 += mm::Vec3(power.x * direction.x, power.y * direction.y, power.z * direction.z);
      }
      break;
    }
    }
  }
  for (unknown002 **it = unknown00.begin(); it != unknown00.end(); ++it) {
    unknown002 *force = *it;
    if (force->unknown10.unknown04 > force->unknown00) {
      continue;
    }
    emitter::EmitterObj *emitter = particle->getExtParam().getEmParent();
    if (emitter != nullptr && emitter->unknown98 != nullptr && emitter->unknown98->unknown08) {
      continue;
    }
    switch (force->unknown10.unknown00) {
    case 4: {
      mm::Vec3 center(force->unknown20.x, force->unknown20.y, force->unknown20.z);
      mm::Vec3 direction = particle->unknown10 - center;
      if (direction.x * direction.x + direction.y * direction.y + direction.z * direction.z < force->unknown40 * force->unknown40) {
        if (!unknown004(direction)) {
          unknown001(direction);
          center += direction * force->unknown40;
        }
        particle->unknown40 = (particle->unknown10 - center) * -1.0f;
        particle->unknown50 = mm::Vec3::zero;
      }
      break;
    }
    case 5: {
      mm::Vec3 center(force->unknown20.x, force->unknown20.y, force->unknown20.z);
      mm::Vec3 direction(particle->unknown10.x - center.x, 0.0f, particle->unknown10.z - center.z);
      if (direction.x * direction.x + direction.z * direction.z < force->unknown40 * force->unknown40) {
        if (!unknown004(direction)) {
          unknown001(direction);
          center += direction * force->unknown40;
        }
        mm::Vec3 velocity(particle->unknown10.x - center.x, 0.0f, particle->unknown10.z - center.z);
        particle->unknown50 = mm::Vec3::zero;
        particle->unknown40 = velocity * -0.5f;
        particle->getExtParam().unknownb2 = 120;
        particle->getExtParam().unknownb3 = 120;
      }
      break;
    }
    case 7: {
      mm::Vec3 normal;
      mm::Vec3 pos;
      mm::Vec3 direction = mm::Vec3::zero;
      if (!unknown005(particle->unknown20, particle->unknown10)) {
        direction.x = particle->unknown10.x - particle->unknown20.x;
        direction.y = particle->unknown10.y - particle->unknown20.y;
        direction.z = particle->unknown10.z - particle->unknown20.z;
        unknown001(direction);
      }
      if (ParticleManager::getPtr()->testRayGround(normal, pos, particle->unknown10, direction, 0.2f, 0.0f)) {
        unknown006(particle);
        particle->unknown10 = pos;
        mm::Vec3 power(force->unknown30.x, force->unknown30.y, force->unknown30.z);
        particle->unknown40 += mm::Vec3(power.x * normal.x, power.y * normal.y, power.z * normal.z);
      }
      break;
    }
    case 8: {
      mm::Vec3 normal;
      mm::Vec3 pos;
      mm::Vec3 direction = mm::Vec3::zero;
      if (!unknown005(particle->unknown20, particle->unknown10)) {
        direction.x = particle->unknown10.x - particle->unknown20.x;
        direction.y = particle->unknown10.y - particle->unknown20.y;
        direction.z = particle->unknown10.z - particle->unknown20.z;
        unknown001(direction);
      }
      if (ParticleManager::getPtr()->testRayChara(normal, pos, particle->unknown10, direction, 0.2f, 0.0f)) {
        unknown006(particle);
        particle->unknown10 = pos;
        mm::Vec3 power(force->unknown30.x, force->unknown30.y, force->unknown30.z);
        particle->unknown40 += mm::Vec3(power.x * normal.x, power.y * normal.y, power.z * normal.z);
      }
      break;
    }
    }
  }
  if (particle->getExtParam().getEmParent() != nullptr) {
    f32 scale = particle->getExtParam().getEmParent()->getEmitterScale();
    particle->unknown10 += particle->unknown40 * scale;
  }
}

void FfManager::addForce(const AddForceParam &param) {
#line 306
  unknown002 *force = static_cast<unknown002 *>(ParticleManager::sysAlloc(sizeof(unknown002), 0x10, __FILE__, __LINE__));
  if (force == nullptr) {
    efMsg("memory empty");
    return;
  }
  force->unknown10 = param.unknown00;
  force->unknown20.x = param.unknown10.x;
  force->unknown20.y = param.unknown10.y;
  force->unknown20.z = param.unknown10.z;
  force->unknown30.x = param.unknown20.x;
  force->unknown30.y = param.unknown20.y;
  force->unknown30.z = param.unknown20.z;
  force->unknown40 = param.unknown30;
  if (force->unknown10.unknown06 != -1) {
    force->unknown10.unknown06++;
  }
  force->unknown00 = 0;
  unknown00.push_back(force);
}

void FfManager::term() {
  if (getPtr() != nullptr) {
    getPtr()->termSub();
    getPtr()->unknown00.~FixedVector();
    if (getPtr() != nullptr) {
      ParticleManager::sysFree(getPtr());
      getPtr() = nullptr;
    }
  }
}

} // namespace forcefield
} // namespace ptlib
