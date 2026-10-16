#pragma once
#include <stddef.h>

#include "mm_mtl/list.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {

class UpdatableObject;
struct ObjectEvent;
struct UpdateInfo;

class UpdatableGroup {
public:
  UpdatableGroup(mm::mtl::IAllocator *allocator, u32 group);
  virtual ~UpdatableGroup();
  virtual void update(const UpdateInfo &info, u32 layerMask);
  virtual void tail(const UpdateInfo &info);
  void destroyObject(UpdatableObject *object);
  void execEvent(const ObjectEvent &event, u32 layerMask);
  void registObject(UpdatableObject *object);
  void destroyAllObject();

  mm::mtl::List<UpdatableObject *> objects;
  u8 _48[0x4c - 0x48];
  mm::mtl::IAllocator *allocator;
  u32 group;
};

static_assert(offsetof(UpdatableGroup, objects) == 0x08, "");
static_assert(offsetof(UpdatableGroup, allocator) == 0x50, "");
static_assert(offsetof(UpdatableGroup, group) == 0x58, "");
static_assert(sizeof(UpdatableGroup) == 0x60, "");

} // namespace fw
