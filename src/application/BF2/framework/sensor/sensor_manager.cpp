#include "framework/sensor/sensor_manager.h"

#include "anm/anm_thread_pool.h"
#include "framework/anim/anim_manager.h"
#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {

SensorManager::SensorManager() {
  unknown618 = nullptr;
  mm::mtl::IAllocator *allocator = Allocator::getProcAllocator();
#line 31
  unknown618 = new (allocator, 16, __FILE__, __LINE__) anm::JobQueue(allocator);
  unknown618->registerJobExecuter(0, SensorUpdateJob::exec);
}

SensorManager::~SensorManager() {
  AnimationManager::get()->unknownf18->waitForCompletion();
  if (unknown618 != nullptr) {
    delete unknown618;
    unknown618 = nullptr;
  }
}

void SensorManager::flushBeforeGame(const UpdateInfo &info, u32 layers) {
  anm::ThreadPool *pool = AnimationManager::get()->unknownf18;
  for (u32 layer = 0; layer < LAYER_MAX; layer++) {
    if ((layers & 1 << layer) != 0) {
      mm::mtl::IntrusiveList<SensorUpdater> &list = unknown18[layer].unknown00;
      u32 count = list.size();
      u32 remaining = count & 1;
      u32 batches = count >> 1;
      mm::mtl::IntrusiveList<SensorUpdater>::iterator it = list.begin();
      for (u32 batch = 0; batch < batches; batch++) {
        unknown001(it, 2);
      }

      if (remaining != 0) {
        unknown001(it, remaining);
      }
    }
  }

  pool->processAllJob(*unknown618);
  pool->waitForCompletion();
}

void SensorManager::flushAfterAnimation(const UpdateInfo &info, u32 layers) {
  anm::ThreadPool *pool = AnimationManager::get()->unknownf18;
  for (u32 layer = 0; layer < LAYER_MAX; layer++) {
    if ((layers & 1 << layer) != 0) {
      mm::mtl::IntrusiveList<SensorUpdater> &list = unknown18[layer].unknown18;
      u32 count = list.size();
      u32 remaining = count & 1;
      u32 batches = count >> 1;
      mm::mtl::IntrusiveList<SensorUpdater>::iterator it = list.begin();
      for (u32 batch = 0; batch < batches; batch++) {
        unknown001(it, 2);
      }

      if (remaining != 0) {
        unknown001(it, remaining);
      }
    }
  }

  pool->processAllJob(*unknown618);
  pool->waitForCompletion();
}

const char *SensorManager::getName() const { return "SensorManager"; }

void SensorManager::update(const UpdateInfo &info) {}

void SensorManager::addUpdaterBeforeGame(u32 layer, SensorUpdater &updater) {
  unknown18[layer].unknown00.push_back(&updater);
  updater.unknown30 = true;
}

void SensorManager::removeUpdaterBeforeGame(u32 layer, SensorUpdater &updater) {
  unknown18[layer].unknown00.erase(&updater);
  updater.unknown30 = false;
}

void SensorManager::addUpdaterAfterAnimation(u32 layer, SensorUpdater &updater) {
  unknown18[layer].unknown18.push_back(&updater);
  updater.unknown30 = true;
}

void SensorManager::removeUpdaterAfterAnimation(u32 layer, SensorUpdater &updater) {
  unknown18[layer].unknown18.erase(&updater);
  updater.unknown30 = false;
}

} // namespace fw
