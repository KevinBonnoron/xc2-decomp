#include "framework/object/updatable_object.h"

namespace fw {

UpdatableObject::UpdatableObject(u32 type, const HandlePtr<UpdatableObject> &handle, u32 layer)
    : selfHandle(handle), type(type), layer(layer), flags(0), parent() {
  for (u32 i = 0; i < COMPONENT_SLOT_MAX; i++) {
    components[i] = nullptr;
  }
}

UpdatableObject::~UpdatableObject() {
  UpdatableObject *parentObject = parent.get();
  if (parentObject != nullptr) {
    parentObject->removeChild(selfHandle);
  }
}

void UpdatableObject::removeChild(const HandlePtr<UpdatableObject> &child) {
  UpdatableObject *childObject = child.get();
  children.erase(childObject);
  childObject->parent = HandlePtr<UpdatableObject>();
}

void UpdatableObject::setTerminate() { flags |= 1; }

bool UpdatableObject::isTerminate() const { return flags & 1; }

void UpdatableObject::addChild(UpdatableObject *child) {
  children.push_back(child);
  child->parent = selfHandle;
}

void UpdatableObject::setParent(const HandlePtr<UpdatableObject> &parent) { this->parent = parent; }

void UpdatableObject::addChild(const HandlePtr<UpdatableObject> &child) { addChild(child.get()); }

void UpdatableObject::removeChild(UpdatableObject *child) {
  children.erase(child);
  child->parent = HandlePtr<UpdatableObject>();
}

void UpdatableObject::registComponentLocal(u32 index, ComponentObject *component) {
  components[index] = component;
  component->owner = this;
}

void UpdatableObject::removeComponentLocal(u32 index) {
  if (components[index] != nullptr) {
    delete components[index];
    components[index] = nullptr;
  }
}

const mm::mtl::RTTI *UpdatableObject::getRTTI() const { return &m_rtti; }

void UpdatableObject::initialize() {}

void UpdatableObject::onEvent(const ObjectEvent &event) {}

} // namespace fw
