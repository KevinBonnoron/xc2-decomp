#include "framework/dynamics/dynamics_manager.h"

#include "anm/anm_job_queue.h"
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

DyanmicsManager::DyanmicsManager() {
  unknown618 = nullptr;
  mm::mtl::IAllocator *allocator = Allocator::getProcAllocator();
#line 30
  unknown618 = new (allocator, 16, __FILE__, __LINE__) anm::JobQueue(allocator);
  unknown618->registerJobExecuter(0, DynamicsColUpdateJob::exec);
  unknown618->registerJobExecuter(1, DynamicsUpdateJob::exec);
}

DyanmicsManager::~DyanmicsManager() {
  AnimationManager::get()->unknownf18->waitForCompletion();
  if (unknown618 != nullptr) {
    delete unknown618;
    unknown618 = nullptr;
  }
}

void DyanmicsManager::updateColObjects(u32 layers) {
  anm::ThreadPool *pool = AnimationManager::get()->unknownf18;
  for (u32 layer = 0; layer < LAYER_MAX; layer++) {
    if ((layers & 1 << layer) != 0) {
      mm::mtl::IntrusiveList<DynamicsColObjUpdaterInterface> &list = unknown18[layer].unknown18;
      mm::mtl::IntrusiveList<DynamicsColObjUpdaterInterface>::iterator it = list.begin();
      for (int count = list.size(); count != 0; count--) {
        DynamicsColUpdateJob job(1);
        job.unknown10[0] = &*it;
        ++it;
        unknown618->unknown001(job);
      }
    }
  }

  pool->processAllJob(*unknown618);
  pool->waitForCompletion();
}

void DyanmicsManager::updateDynamics(const UpdateInfo &info, u32 layers) {
  anm::ThreadPool *pool = AnimationManager::get()->unknownf18;
  for (u32 layer = 0; layer < LAYER_MAX; layer++) {
    if ((layers & 1 << layer) != 0) {
      mm::mtl::IntrusiveList<DynamicsUpdaterInterface> &list = unknown18[layer].unknown00;
      mm::mtl::IntrusiveList<DynamicsUpdaterInterface>::iterator it = list.begin();
      for (int count = unknown18[layer].unknown18.size(); count != 0; count--) {
        DynamicsUpdateJob job(1);
        job.unknown20 = &info;
        job.unknown10[0] = &*it;
        ++it;
        unknown618->unknown001(job);
      }
    }
  }

  pool->processAllJob(*unknown618);
  pool->waitForCompletion();
}

const char *DyanmicsManager::getName() const { return "DyanmicsManager"; }

void DyanmicsManager::update(const UpdateInfo &info) {}

void DyanmicsManager::addColUpdater(u32 layer, DynamicsColObjUpdaterInterface &updater) { unknown18[layer].unknown18.push_back(&updater); }

void DyanmicsManager::removeColUpdater(u32 layer, DynamicsColObjUpdaterInterface &updater) { unknown18[layer].unknown18.erase(&updater); }

void DyanmicsManager::addUpdater(u32 layer, DynamicsUpdaterInterface &updater) { unknown18[layer].unknown00.push_back(&updater); }

void DyanmicsManager::removeUpdater(u32 layer, DynamicsUpdaterInterface &updater) { unknown18[layer].unknown00.erase(&updater); }

} // namespace fw
