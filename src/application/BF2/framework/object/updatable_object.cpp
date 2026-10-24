#include "framework/object/updatable_object.h"

namespace fw {

UpdatableObject::UpdatableObject(u32 type, const HandlePtr<UpdatableObject> &handle, u32 layer) : unknown18(handle), unknown28(type), unknown2c(layer), unknown30(0), unknownd0() {
  for (u32 i = 0; i < COMPONENT_SLOT_MAX; i++) {
    unknown38[i] = nullptr;
  }
}

UpdatableObject::~UpdatableObject() {
  UpdatableObject *parentObject = unknownd0.get();
  if (parentObject != nullptr) {
    parentObject->removeChild(unknown18);
  }
}

void UpdatableObject::removeChild(const HandlePtr<UpdatableObject> &child) {
  UpdatableObject *childObject = child.get();
  unknownb8.erase(childObject);
  childObject->unknownd0 = HandlePtr<UpdatableObject>();
}

void UpdatableObject::setTerminate() { unknown30 |= 1; }

bool UpdatableObject::isTerminate() const { return unknown30 & 1; }

void UpdatableObject::addChild(UpdatableObject *child) {
  unknownb8.push_back(child);
  child->unknownd0 = unknown18;
}

void UpdatableObject::setParent(const HandlePtr<UpdatableObject> &parent) { this->unknownd0 = parent; }

void UpdatableObject::addChild(const HandlePtr<UpdatableObject> &child) { addChild(child.get()); }

void UpdatableObject::removeChild(UpdatableObject *child) {
  unknownb8.erase(child);
  child->unknownd0 = HandlePtr<UpdatableObject>();
}

void UpdatableObject::registComponentLocal(u32 index, ComponentObject *component) {
  unknown38[index] = component;
  component->unknown08 = this;
}

void UpdatableObject::removeComponentLocal(u32 index) {
  if (unknown38[index] != nullptr) {
    delete unknown38[index];
    unknown38[index] = nullptr;
  }
}

const mm::mtl::RTTI *UpdatableObject::getRTTI() const { return &m_rtti; }

void UpdatableObject::initialize() {}

void UpdatableObject::onEvent(const ObjectEvent &event) {}

} // namespace fw
