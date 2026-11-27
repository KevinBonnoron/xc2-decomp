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
  static const u32 GROUP_UNKNOWN_32 = 32;                    // Inferred role: maximum number of groups; original name unknown.
  static const u32 POINTER_ID_UNKNOWN_134217727 = 0x7ffffff; // Inferred role: maximum pointer id; original name unknown.

  class Impl {
  public:
    Impl(mm::mtl::IAllocator *allocator, size_t capacity) : unknown00(allocator) {
      for (u32 i = 0; i < GROUP_UNKNOWN_32; i++) {
        m_group[i] = nullptr;
      }
      m_pointerMap.reserve(allocator, capacity);
      m_pointerMap.setRange(1, POINTER_ID_UNKNOWN_134217727, POINTER_ID_UNKNOWN_134217727);
    }

    ~Impl() {
      destroy();
      m_pointerMap.destroy();
    }

    HandlePtr<UpdatableObject> registPointer(u32 group, const void *ptr);
    void registGroup(u32 group, UpdatableGroup *updatableGroup);
    void removeGroup(u32 group);
    void destroy();
    void destroyObject(u32 groupMask);
    void update(const UpdateInfo &info, u32 layerMask);
    void tail(const UpdateInfo &info);
    void execEvent(const ObjectEvent &event, u32 layerMask);
    UpdatableGroup *getGroup(u32 group);
    void registObject(u32 group, UpdatableObject *object);

    mm::mtl::IAllocator *unknown00;            // Inferred role: allocator; original member name unknown.
    UpdatableGroup *m_group[GROUP_UNKNOWN_32]; // Inferred role: groups; named after the game accessor fw::UpdatableObjectManager::Impl::getGroup.
    PointerMap m_pointerMap;                   // Inferred role: pointer map; original member name unknown.
  };

  UpdatableObjectManager(mm::mtl::IAllocator *allocator, size_t capacity);
  ~UpdatableObjectManager();
  bool initialize() override;
  bool finalize() override;
  const char *getName() const override;
  virtual void update(const UpdateInfo &info, u32 layerMask);
  virtual void tail(const UpdateInfo &info);
  void execEvent(const ObjectEvent &event, u32 layerMask);
  HandlePtr<UpdatableObject> registPointer(u32 group, const void *ptr);
  void registObject(u32 group, UpdatableObject *object);

  mm::mtl::UniquePtr<Impl> unknown18; // Inferred role: impl; original member name unknown.
};

static_assert(offsetof(UpdatableObjectManager::Impl, unknown00) == 0x00, "");
static_assert(offsetof(UpdatableObjectManager::Impl, m_group) == 0x08, "");
static_assert(offsetof(UpdatableObjectManager::Impl, m_pointerMap) == 0x108, "");
static_assert(offsetof(UpdatableObjectManager, unknown18) == 0x18, "");

} // namespace fw
