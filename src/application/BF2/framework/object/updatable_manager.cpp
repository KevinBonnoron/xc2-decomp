#include "framework/object/updatable_manager.h"

#include "framework/object/updatable_group.h"

namespace fw {

HandlePtr<void> UpdatableObjectManager::Impl::registPointer(u32 group, const void *ptr) {
  HandlePtr<void> handle;
  handle.id = pointerMap.regist(ptr);
  handle.map = &pointerMap;
  return handle;
}

void UpdatableObjectManager::Impl::registGroup(u32 group, UpdatableGroup *updatableGroup) {
  removeGroup(group);
  groups[group] = updatableGroup;
}

void UpdatableObjectManager::Impl::removeGroup(u32 group) {
  if (groups[group] != nullptr) {
    delete groups[group];
    groups[group] = nullptr;
  }
}

void UpdatableObjectManager::Impl::destroy() {
  for (int i = GROUP_MAX - 1; i >= 0; i--) {
    if (groups[i] != nullptr) {
      groups[i]->destroyAllObject();
    }
  }

  for (int i = GROUP_MAX - 1; i >= 0; i--) {
    removeGroup(i);
  }
}

void UpdatableObjectManager::Impl::destroyObject(u32 groupMask) {
  for (int i = GROUP_MAX - 1; i >= 0; i--) {
    if (groups[i] != nullptr && (groupMask & (1 << i)) != 0) {
      groups[i]->destroyAllObject();
    }
  }
}

void UpdatableObjectManager::Impl::update(const UpdateInfo &info, u32 layerMask) {
  for (u32 i = 0; i < GROUP_MAX; i++) {
    if (groups[i] != nullptr) {
      groups[i]->update(info, layerMask);
    }
  }
}

void UpdatableObjectManager::Impl::tail(const UpdateInfo &info) {
  for (int i = GROUP_MAX - 1; i >= 0; i--) {
    if (groups[i] != nullptr) {
      groups[i]->tail(info);
    }
  }
}

void UpdatableObjectManager::Impl::execEvent(const ObjectEvent &event, u32 layerMask) {
  for (u32 i = 0; i < GROUP_MAX; i++) {
    if (groups[i] != nullptr) {
      groups[i]->execEvent(event, layerMask);
    }
  }
}

UpdatableGroup *UpdatableObjectManager::Impl::getGroup(u32 group) { return groups[group]; }

void UpdatableObjectManager::Impl::registObject(u32 group, UpdatableObject *object) { groups[group]->registObject(object); }

void UpdatableObjectManager::update(const UpdateInfo &info, u32 layerMask) {
  if (isFinalized()) {
    return;
  }

  impl->update(info, layerMask);
}

void UpdatableObjectManager::execEvent(const ObjectEvent &event, u32 layerMask) {
  if (isFinalized()) {
    return;
  }

  impl->execEvent(event, layerMask);
}

void UpdatableObjectManager::tail(const UpdateInfo &info) {
  if (isFinalized()) {
    return;
  }

  impl->tail(info);
}

HandlePtr<void> UpdatableObjectManager::registPointer(u32 group, const void *ptr) { return impl->registPointer(group, ptr); }

void UpdatableObjectManager::registObject(u32 group, UpdatableObject *object) { impl->registObject(group, object); }

const char *UpdatableObjectManager::getName() const { return "UpdatableObjectManager"; }

} // namespace fw
