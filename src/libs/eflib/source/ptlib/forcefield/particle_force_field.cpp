#include "ptlib/forcefield/particle_force_field.h"

#include "mm/mm_std_base.h"
#include "ptlib/particle_system.h"

namespace ptlib {
namespace forcefield {

namespace {
FfManager *s_ffInstance;
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
