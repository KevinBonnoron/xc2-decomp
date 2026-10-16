#pragma once
#include <stddef.h>

#include "framework/object/component_object.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/rtti.h"
#include "types.h"

namespace fw {

struct ObjectEvent;
struct UpdateInfo;

class PointerMap {
public:
  void *getPtr(u32 id) const;
};

template <typename T> struct HandlePtr {
  HandlePtr() : id(0), map(nullptr) {}
  HandlePtr(const HandlePtr &other) : id(other.id), map(other.map) {}

  HandlePtr &operator=(const HandlePtr &other) {
    id = other.id;
    map = other.map;
    return *this;
  }

  T *get() const { return id != 0 ? static_cast<T *>(map->getPtr(id)) : nullptr; }

  u32 id;
  PointerMap *map;
};

class UpdatableObject : public mm::mtl::IntrusiveListNode<UpdatableObject> {
public:
  static const u32 COMPONENT_MAX = 12;
  static const u32 COMPONENT_SLOT_MAX = 16;

  static mm::mtl::RTTI m_rtti;

  UpdatableObject(u32 type, const HandlePtr<UpdatableObject> &handle, u32 layer);
  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual ~UpdatableObject();
  virtual void initialize();
  virtual void update(const UpdateInfo &info) = 0;
  virtual void onEvent(const ObjectEvent &event);

  void removeChild(const HandlePtr<UpdatableObject> &child);
  void setTerminate();
  bool isTerminate() const;
  void addChild(UpdatableObject *child);
  void setParent(const HandlePtr<UpdatableObject> &parent);
  void addChild(const HandlePtr<UpdatableObject> &child);
  void removeChild(UpdatableObject *child);
  void registComponentLocal(u32 index, ComponentObject *component);
  void removeComponentLocal(u32 index);

  template <typename T> T *getComponent() const {
    ComponentObject *component = components[T::COMPONENT_INDEX];
    if (component == nullptr) {
      return nullptr;
    }

    return mm::mtl::dynamicCast<T>(component);
  }

  HandlePtr<UpdatableObject> selfHandle;
  u32 type;
  u32 layer;
  u16 flags;
  u8 _32[0x38 - 0x32];
  ComponentObject *components[COMPONENT_SLOT_MAX];
  mm::mtl::IntrusiveList<UpdatableObject> children;
  HandlePtr<UpdatableObject> parent;
};

static_assert(offsetof(UpdatableObject, selfHandle) == 0x18, "");
static_assert(offsetof(UpdatableObject, type) == 0x28, "");
static_assert(offsetof(UpdatableObject, layer) == 0x2c, "");
static_assert(offsetof(UpdatableObject, flags) == 0x30, "");
static_assert(offsetof(UpdatableObject, components) == 0x38, "");
static_assert(offsetof(UpdatableObject, children) == 0xb8, "");
static_assert(offsetof(UpdatableObject, parent) == 0xd0, "");
static_assert(sizeof(UpdatableObject) == 0xe0, "");

} // namespace fw
