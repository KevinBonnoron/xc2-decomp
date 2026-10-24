#include "framework/object/updatable_manager.h"

#include "framework/memory/framework_memory.h"
#include "framework/object/updatable_group.h"
#include "framework/object/updatable_object_factory.h"

namespace fw {

HandlePtr<void> UpdatableObjectManager::Impl::registPointer(u32 group, const void *ptr) {
  HandlePtr<void> handle;
  handle.id = unknown108.regist(ptr);
  handle.map = &unknown108;
  return handle;
}

void UpdatableObjectManager::Impl::registGroup(u32 group, UpdatableGroup *updatableGroup) {
  removeGroup(group);
  unknown08[group] = updatableGroup;
}

void UpdatableObjectManager::Impl::removeGroup(u32 group) {
  if (unknown08[group] != nullptr) {
    delete unknown08[group];
    unknown08[group] = nullptr;
  }
}

void UpdatableObjectManager::Impl::destroy() {
  for (int i = GROUP_MAX - 1; i >= 0; i--) {
    if (unknown08[i] != nullptr) {
      unknown08[i]->destroyAllObject();
    }
  }

  for (int i = GROUP_MAX - 1; i >= 0; i--) {
    removeGroup(i);
  }
}

void UpdatableObjectManager::Impl::destroyObject(u32 groupMask) {
  for (int i = GROUP_MAX - 1; i >= 0; i--) {
    if (unknown08[i] != nullptr && (groupMask & (1 << i)) != 0) {
      unknown08[i]->destroyAllObject();
    }
  }
}

void UpdatableObjectManager::Impl::update(const UpdateInfo &info, u32 layerMask) {
  for (u32 i = 0; i < GROUP_MAX; i++) {
    if (unknown08[i] != nullptr) {
      unknown08[i]->update(info, layerMask);
    }
  }
}

void UpdatableObjectManager::Impl::tail(const UpdateInfo &info) {
  for (int i = GROUP_MAX - 1; i >= 0; i--) {
    if (unknown08[i] != nullptr) {
      unknown08[i]->tail(info);
    }
  }
}

void UpdatableObjectManager::Impl::execEvent(const ObjectEvent &event, u32 layerMask) {
  for (u32 i = 0; i < GROUP_MAX; i++) {
    if (unknown08[i] != nullptr) {
      unknown08[i]->execEvent(event, layerMask);
    }
  }
}

UpdatableGroup *UpdatableObjectManager::Impl::getGroup(u32 group) { return unknown08[group]; }

void UpdatableObjectManager::Impl::registObject(u32 group, UpdatableObject *object) { unknown08[group]->registObject(object); }

UpdatableObjectManager::UpdatableObjectManager(mm::mtl::IAllocator *allocator, size_t capacity)
// __LINE__ of the game: it is the line argument of the operator new.
#line 234
    : unknown18(new (allocator, 8, __FILE__, __LINE__) Impl(allocator, capacity)) {
}

UpdatableObjectManager::~UpdatableObjectManager() {}

bool UpdatableObjectManager::initialize() {
  mm::mtl::IAllocator *allocator = unknown18->unknown00;
  for (u32 i = 0; i < GROUP_MAX; i++) {
    // __LINE__ of the game: it is the line argument of the operator new.
#line 256
    UpdatableGroup *group = new (allocator, 8, __FILE__, __LINE__) UpdatableGroup(allocator, i);
    unknown18->registGroup(i, group);
  }

  // __LINE__ of the game: it is the line argument of the operator new.
#line 262
  new (allocator, 8, __FILE__, __LINE__) UpdatableObjectFactory(allocator, this);
  return true;
}

bool UpdatableObjectManager::finalize() {
  delete UpdatableObjectFactory::get();
  unknown18.reset();
  return true;
}

void UpdatableObjectManager::update(const UpdateInfo &info, u32 layerMask) {
  if (isFinalized()) {
    return;
  }

  unknown18->update(info, layerMask);
}

void UpdatableObjectManager::execEvent(const ObjectEvent &event, u32 layerMask) {
  if (isFinalized()) {
    return;
  }

  unknown18->execEvent(event, layerMask);
}

void UpdatableObjectManager::tail(const UpdateInfo &info) {
  if (isFinalized()) {
    return;
  }

  unknown18->tail(info);
}

HandlePtr<void> UpdatableObjectManager::registPointer(u32 group, const void *ptr) { return unknown18->registPointer(group, ptr); }

void UpdatableObjectManager::registObject(u32 group, UpdatableObject *object) { unknown18->registObject(group, object); }

const char *UpdatableObjectManager::getName() const { return "UpdatableObjectManager"; }

} // namespace fw
