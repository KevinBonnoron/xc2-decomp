#pragma once
#include <stddef.h>

#include "framework/manager_object.h"
#include "framework/pointer_map.h"
#include "mm_mtl/singleton.h"
#include "mm_mtl/unique_ptr.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {

class UpdatableGroup;
class UpdatableObject;
struct ObjectEvent;
struct UpdateInfo;

class UpdatableObjectManager : public ManagerObject, public mm::mtl::PtrSingleton<UpdatableObjectManager> {
public:
  static const u32 GROUP_MAX = 32;
  static const u32 POINTER_ID_MAX = 0x7ffffff;

  class Impl {
  public:
    Impl(mm::mtl::IAllocator *allocator, size_t capacity) : allocator(allocator) {
      for (u32 i = 0; i < GROUP_MAX; i++) {
        groups[i] = nullptr;
      }
      pointerMap.reserve(allocator, capacity);
      pointerMap.setRange(1, POINTER_ID_MAX, POINTER_ID_MAX);
    }

    ~Impl() {
      destroy();
      pointerMap.destroy();
    }

    HandlePtr<void> registPointer(u32 group, const void *ptr);
    void registGroup(u32 group, UpdatableGroup *updatableGroup);
    void removeGroup(u32 group);
    void destroy();
    void destroyObject(u32 groupMask);
    void update(const UpdateInfo &info, u32 layerMask);
    void tail(const UpdateInfo &info);
    void execEvent(const ObjectEvent &event, u32 layerMask);
    UpdatableGroup *getGroup(u32 group);
    void registObject(u32 group, UpdatableObject *object);

    mm::mtl::IAllocator *allocator;
    UpdatableGroup *groups[GROUP_MAX];
    PointerMap pointerMap;
  };

  UpdatableObjectManager(mm::mtl::IAllocator *allocator, size_t capacity);
  ~UpdatableObjectManager();
  bool initialize() override;
  bool finalize() override;
  const char *getName() const override;
  virtual void update(const UpdateInfo &info, u32 layerMask);
  virtual void tail(const UpdateInfo &info);
  void execEvent(const ObjectEvent &event, u32 layerMask);
  HandlePtr<void> registPointer(u32 group, const void *ptr);
  void registObject(u32 group, UpdatableObject *object);

  mm::mtl::UniquePtr<Impl> impl;
};

static_assert(offsetof(UpdatableObjectManager::Impl, allocator) == 0x00, "");
static_assert(offsetof(UpdatableObjectManager::Impl, groups) == 0x08, "");
static_assert(offsetof(UpdatableObjectManager::Impl, pointerMap) == 0x108, "");
static_assert(offsetof(UpdatableObjectManager, impl) == 0x18, "");

} // namespace fw
