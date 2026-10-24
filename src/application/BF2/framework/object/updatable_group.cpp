#include "framework/object/updatable_group.h"

#include "framework/object/updatable_object.h"
#include "framework/pointer_map.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {

UpdatableGroup::UpdatableGroup(mm::mtl::IAllocator *allocator, u32 group) : _48(), unknown50(allocator), unknown58(group) {
  unknown08.setAllocator(allocator);
  unknown08.reserve(0x1000);
}

UpdatableGroup::~UpdatableGroup() { unknown08.clear(); }

void UpdatableGroup::update(const UpdateInfo &info, u32 layerMask) {
  for (mm::mtl::List<UpdatableObject *>::iterator it = unknown08.begin(); it != unknown08.end();) {
    UpdatableObject *object = *it;
    ++it;
    if ((layerMask & (1 << object->unknown2c)) != 0 && !object->isTerminate()) {
      object->update(info);
    }
  }
}

void UpdatableGroup::tail(const UpdateInfo &info) {
  for (mm::mtl::List<UpdatableObject *>::iterator it = unknown08.begin(); it != unknown08.end();) {
    UpdatableObject *object = *it;
    if (!object->isTerminate()) {
      ++it;
    } else {
      it = unknown08.erase(it);
      destroyObject(object);
    }
  }
}

void UpdatableGroup::destroyObject(UpdatableObject *object) {
  u32 id = object->unknown18.id;
  PointerMap *map = object->unknown18.map;
  delete object;
  if (id != 0 && map != nullptr) {
    map->remove(id);
  }
}

void UpdatableGroup::execEvent(const ObjectEvent &event, u32 layerMask) {
  for (mm::mtl::List<UpdatableObject *>::iterator it = unknown08.begin(); it != unknown08.end();) {
    UpdatableObject *object = *it;
    ++it;
    if ((layerMask & (1 << object->unknown2c)) != 0 && !object->isTerminate()) {
      object->onEvent(event);
    }
  }
}

void UpdatableGroup::registObject(UpdatableObject *object) { unknown08.push_back(object); }

void UpdatableGroup::destroyAllObject() {
  for (mm::mtl::List<UpdatableObject *>::iterator it = unknown08.begin(); it != unknown08.end();) {
    UpdatableObject *object = *it;
    it = unknown08.erase(it);
    destroyObject(object);
  }
}

} // namespace fw
