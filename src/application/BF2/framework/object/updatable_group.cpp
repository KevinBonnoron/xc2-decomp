#include "framework/object/updatable_group.h"

#include "framework/object/updatable_object.h"
#include "framework/pointer_map.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {

UpdatableGroup::UpdatableGroup(mm::mtl::IAllocator *allocator, u32 group) : _48(), allocator(allocator), group(group) {
  objects.setAllocator(allocator);
  objects.reserve(0x1000);
}

UpdatableGroup::~UpdatableGroup() { objects.clear(); }

void UpdatableGroup::update(const UpdateInfo &info, u32 layerMask) {
  for (mm::mtl::List<UpdatableObject *>::iterator it = objects.begin(); it != objects.end();) {
    UpdatableObject *object = *it;
    ++it;
    if ((layerMask & (1 << object->layer)) != 0 && !object->isTerminate()) {
      object->update(info);
    }
  }
}

void UpdatableGroup::tail(const UpdateInfo &info) {
  for (mm::mtl::List<UpdatableObject *>::iterator it = objects.begin(); it != objects.end();) {
    UpdatableObject *object = *it;
    if (!object->isTerminate()) {
      ++it;
    } else {
      it = objects.erase(it);
      destroyObject(object);
    }
  }
}

void UpdatableGroup::destroyObject(UpdatableObject *object) {
  u32 id = object->selfHandle.id;
  PointerMap *map = object->selfHandle.map;
  delete object;
  if (id != 0 && map != nullptr) {
    map->remove(id);
  }
}

void UpdatableGroup::execEvent(const ObjectEvent &event, u32 layerMask) {
  for (mm::mtl::List<UpdatableObject *>::iterator it = objects.begin(); it != objects.end();) {
    UpdatableObject *object = *it;
    ++it;
    if ((layerMask & (1 << object->layer)) != 0 && !object->isTerminate()) {
      object->onEvent(event);
    }
  }
}

void UpdatableGroup::registObject(UpdatableObject *object) { objects.push_back(object); }

void UpdatableGroup::destroyAllObject() {
  for (mm::mtl::List<UpdatableObject *>::iterator it = objects.begin(); it != objects.end();) {
    UpdatableObject *object = *it;
    it = objects.erase(it);
    destroyObject(object);
  }
}

} // namespace fw
