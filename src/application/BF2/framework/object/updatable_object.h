#pragma once
#include <stddef.h>

#include "framework/object/component_object.h"
#include "framework/pointer_map.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/rtti.h"
#include "types.h"

namespace fw {

struct UpdateInfo;

enum OBJECT_EVENT {
  OBJECT_EVENT_UPDATE_END = 0,
};

struct ObjectEvent {
  u32 type;
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
    ComponentObject *component = unknown38[T::COMPONENT_INDEX];
    if (component == nullptr) {
      return nullptr;
    }

    return mm::mtl::dynamicCast<T>(component);
  }

  HandlePtr<UpdatableObject> unknown18; // Inferred role: self handle; original member name unknown.
  u32 unknown28;                        // Inferred role: type; original member name unknown.
  u32 unknown2c;                        // Inferred role: layer; original member name unknown.
  u16 unknown30;                        // Inferred role: flags; original member name unknown.
  u8 _32[0x38 - 0x32];
  ComponentObject *unknown38[COMPONENT_SLOT_MAX];    // Inferred role: components; original member name unknown.
  mm::mtl::IntrusiveList<UpdatableObject> unknownb8; // Inferred role: children; original member name unknown.
  HandlePtr<UpdatableObject> unknownd0;              // Inferred role: parent; original member name unknown.
};

static_assert(offsetof(UpdatableObject, unknown18) == 0x18, "");
static_assert(offsetof(UpdatableObject, unknown28) == 0x28, "");
static_assert(offsetof(UpdatableObject, unknown2c) == 0x2c, "");
static_assert(offsetof(UpdatableObject, unknown30) == 0x30, "");
static_assert(offsetof(UpdatableObject, unknown38) == 0x38, "");
static_assert(offsetof(UpdatableObject, unknownb8) == 0xb8, "");
static_assert(offsetof(UpdatableObject, unknownd0) == 0xd0, "");
static_assert(sizeof(UpdatableObject) == 0xe0, "");

} // namespace fw
