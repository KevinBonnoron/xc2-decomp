#pragma once
#include <stddef.h>

#include "framework/manager_object.h"
#include "framework/pointer_map.h"
#include "mm_mtl/singleton.h"
#include "mm_mtl/unique_ptr.h"
#include "types.h"

namespace fw {

class UpdatableObject;
struct ObjectEvent;
struct UpdateInfo;

class UpdatableGroup {
public:
  virtual ~UpdatableGroup();
  virtual void update(const UpdateInfo &info, u32 layerMask);
  virtual void tail(const UpdateInfo &info);
  void execEvent(const ObjectEvent &event, u32 layerMask);
  void registObject(UpdatableObject *object);
  void destroyAllObject();
};

class UpdatableObjectManager : public ManagerObject, public mm::mtl::PtrSingleton<UpdatableObjectManager> {
public:
  static const u32 GROUP_MAX = 32;

  class Impl {
  public:
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

    u8 _00[0x08 - 0x00];
    UpdatableGroup *groups[GROUP_MAX];
    PointerMap pointerMap;
  };

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

static_assert(offsetof(UpdatableObjectManager::Impl, groups) == 0x08, "");
static_assert(offsetof(UpdatableObjectManager::Impl, pointerMap) == 0x108, "");
static_assert(offsetof(UpdatableObjectManager, impl) == 0x18, "");

} // namespace fw
