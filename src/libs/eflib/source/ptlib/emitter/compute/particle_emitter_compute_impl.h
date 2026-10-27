#pragma once
#include <new>

#include "mm/mm_std_base.h"
#include "ptlib/emitter/compute/particle_emitter_compute.h"
#include "ptlib/particle_system.h"

namespace ptlib {
namespace emitter {

namespace {
ComputeManager *s_instance;
} // namespace

ComputeManager *&ComputeManager::getPtr() { return s_instance; }

ComputeManager *ComputeManager::get() {
#line 26
  MM_ASSERT(getPtr());
  return getPtr();
}

void ComputeManager::init() {
#line 40
  MM_ASSERT(!getPtr());
  s_instance = static_cast<ComputeManager *>(ParticleManager::sysAlloc(sizeof(ComputeManager), 0x20, __FILE__, __LINE__));
  if (s_instance != nullptr) {
    new (s_instance) ComputeManager;
    s_instance->initSub();
  }
}

void ComputeManager::term() {
#line 51
  MM_ASSERT(getPtr());
  if (getPtr() != nullptr) {
    getPtr()->termSub();
    getPtr()->~ComputeManager();
    if (getPtr() != nullptr) {
      ParticleManager::sysFree(getPtr());
      getPtr() = nullptr;
    }
  }
  getPtr() = nullptr;
}

} // namespace emitter
} // namespace ptlib
