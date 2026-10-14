#pragma once
#include "mm_mtl/rtti.h"
#include "types.h"
#include <stddef.h>

namespace fw {

class UpdatableObject;

class PointerMap {
public:
  void *getPtr(u32 id) const;
};

template <typename T> struct HandlePtr {
  T *get() const { return id != 0 ? static_cast<T *>(map->getPtr(id)) : nullptr; }

  u32 id;
  PointerMap *map;
};

class ComponentObject {
public:
  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual ~ComponentObject();

  UpdatableObject *owner;
};

static_assert(offsetof(ComponentObject, owner) == 0x08, "");

class UpdatableObject {
public:
  static const u32 COMPONENT_MAX = 12;

  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual ~UpdatableObject();

  template <typename T> T *getComponent() const {
    ComponentObject *component = components[T::COMPONENT_INDEX];
    if (component == nullptr) {
      return nullptr;
    }

    return mm::mtl::dynamicCast<T>(component);
  }

  u8 _08[0x28 - 0x08];
  u32 type;
  u32 layer;
  u8 _30[0x38 - 0x30];
  ComponentObject *components[COMPONENT_MAX];
  u8 _98[0xd0 - 0x98];
  HandlePtr<UpdatableObject> parent;
};

static_assert(offsetof(UpdatableObject, type) == 0x28, "");
static_assert(offsetof(UpdatableObject, layer) == 0x2c, "");
static_assert(offsetof(UpdatableObject, components) == 0x38, "");
static_assert(offsetof(UpdatableObject, parent) == 0xd0, "");
static_assert(sizeof(UpdatableObject) == 0xe0, "");

} // namespace fw
