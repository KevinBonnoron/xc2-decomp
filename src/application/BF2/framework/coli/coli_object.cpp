#include "framework/coli/coli_object.h"

#include "framework/coli/coli_manager.h"
#include "framework/object/updatable_object.h"
#include "idcoli/idcoli.h"
#include "ml/work_cpu.h"

namespace idcoli {
enum ColiAtrr : int;
enum ColiState : int;
} // namespace idcoli

namespace fw {

void ColiObject::setColiObject(idcoli::IDColiObj *object) { coliObject = object; }

void ColiObject::setHitMaterialFlag(u32 flag) {
  if (coliObject == nullptr) {
    return;
  }

  switch (coliObject->type) {
  case idcoli::OBJ_TYPE_CHARACTER: {
    idcoli::IDColiParmsCharacter params(coliObject);
    params.setOffMaterialBit(~flag);
    break;
  }
  case idcoli::OBJ_TYPE_PHANTOM: {
    idcoli::IDColiParmsPhantom params(coliObject);
    params.setOffMaterialBit(~flag);
    break;
  }
  default:
    break;
  }
}

void ColiObject::setColiType(ColiType type) {
  this->type = type;
  if (type == COLI_TYPE_STATIC) {
    flags |= FLAG_MATRIX_DIRTY;
  }
}

void ColiObject::setPriority(int priority) {
  if (coliObject != nullptr && coliObject->type == idcoli::OBJ_TYPE_CHARACTER) {
    idcoli::IDColiParmsCharacter params(coliObject);
    params.setPriority(priority);
  }
}

void ColiObject::setMaterialFlag(u32 flag) {
  if (coliObject == nullptr) {
    return;
  }

  switch (coliObject->type) {
  case idcoli::OBJ_TYPE_CHARACTER: {
    idcoli::IDColiParmsCharacter params(coliObject);
    params.setMaterialBit(flag);
    break;
  }
  case idcoli::OBJ_TYPE_PHANTOM: {
    idcoli::IDColiParmsPhantom params(coliObject);
    params.setMaterialBit(flag);
    break;
  }
  default:
    break;
  }
}

void ColiObject::setState(ColiState state) {
  if (coliObject != nullptr && coliObject->type == idcoli::OBJ_TYPE_CHARACTER) {
    idcoli::IDColiParmsCharacter params(coliObject);
    params.setState(static_cast<idcoli::ColiState>(state));
  }
}

void ColiObject::clearState(ColiState state) {
  if (coliObject != nullptr && coliObject->type == idcoli::OBJ_TYPE_CHARACTER) {
    idcoli::IDColiParmsCharacter params(coliObject);
    params.clearState(static_cast<idcoli::ColiState>(state));
  }
}

void ColiObject::bindReferenceFrame(const mm::mtl::IntrusivePtr<ReferenceFrame> &frame) { referenceFrame = frame; }

void ColiObject::resetSphere(f32 radius) {
  if (shape == nullptr || shape->type != ColiShape::TYPE_SPHERE) {
    return;
  }

  shape->radius = radius;
  if (coliObject == nullptr) {
    return;
  }

  switch (coliObject->type) {
  case idcoli::OBJ_TYPE_CHARACTER: {
    idcoli::IDColiParmsCharacter params(coliObject);
    params.createSphere(radius);
    break;
  }
  case idcoli::OBJ_TYPE_PHANTOM: {
    idcoli::IDColiParmsPhantom params(coliObject);
    params.createSphere(radius);
    break;
  }
  default:
    break;
  }
}

void ColiObject::resetCapsule(f32 radius, f32 height, bool flag) {
  ColiShape *coliShape = shape;
  if (coliShape == nullptr || coliShape->type != ColiShape::TYPE_CAPSULE) {
    return;
  }

  coliShape->radius = radius;
  coliShape->height = height;
  if (coliObject == nullptr) {
    return;
  }

  switch (coliObject->type) {
  case idcoli::OBJ_TYPE_CHARACTER: {
    idcoli::IDColiParmsCharacter params(coliObject);
    params.createCapsule(radius, height, flag);
    break;
  }
  case idcoli::OBJ_TYPE_PHANTOM: {
    idcoli::IDColiParmsPhantom params(coliObject);
    params.createCapsule(radius, height);
    break;
  }
  default:
    break;
  }
}

void ColiObject::resetBox(const mm::Vec3 &size, bool flag) {
  if (shape == nullptr || shape->type != ColiShape::TYPE_BOX) {
    return;
  }

  shape->size = size;
  if (coliObject == nullptr) {
    return;
  }

  switch (coliObject->type) {
  case idcoli::OBJ_TYPE_CHARACTER: {
    idcoli::IDColiParmsCharacter params(coliObject);
    params.createBox(size, flag);
    break;
  }
  case idcoli::OBJ_TYPE_PHANTOM: {
    idcoli::IDColiParmsPhantom params(coliObject);
    params.createBox(size);
    break;
  }
  default:
    break;
  }
}

void ColiObject::resetCharacter(f32 radius, f32 height) {
  ColiShape *coliShape = shape;
  if (coliShape == nullptr || coliShape->type != ColiShape::TYPE_CHARACTER) {
    return;
  }

  coliShape->radius = radius;
  coliShape->height = height;
  if (coliObject == nullptr) {
    return;
  }

  switch (coliObject->type) {
  case idcoli::OBJ_TYPE_CHARACTER: {
    idcoli::IDColiParmsCharacter params(coliObject);
    params.createCharacter(radius, height);
    break;
  }
  case idcoli::OBJ_TYPE_PHANTOM: {
    idcoli::IDColiParmsPhantom params(coliObject);
    params.createCharacter(radius, height);
    break;
  }
  default:
    break;
  }
}

ColiObject::ColiObject() : coliObject(nullptr), flags(0), listener(nullptr), _58(), scale(1.0f), shape(nullptr) {
  offsetMatrix = mm::Mat44::identity;
  matrix = mm::Mat44::identity;
}

ColiObject::~ColiObject() {
  if (coliObject != nullptr) {
    ColiManager::get()->getInterface();
    ml::WorkCpu::getFrameCount();
    coliObject->release();
    coliObject = nullptr;
  }

  ColiManager::get()->removeObject(this);
  if (shape != nullptr) {
    delete shape;
    shape = nullptr;
  }
}

void ColiObject::setOwner(UpdatableObject *owner) {
  if (owner != nullptr) {
    this->owner = owner->selfHandle;
  } else {
    this->owner = HandlePtr<UpdatableObject>();
  }
}

UpdatableObject *ColiObject::getOwner() const { return owner.get(); }

void ColiObject::setHandle(u32 handle) {
  userData.handle = handle;
  if (coliObject == nullptr) {
    return;
  }

  switch (coliObject->type) {
  case idcoli::OBJ_TYPE_CHARACTER: {
    idcoli::IDColiParmsCharacter params(coliObject);
    params.setUserData(&userData);
    break;
  }
  case idcoli::OBJ_TYPE_PHANTOM: {
    idcoli::IDColiParmsPhantom params(coliObject);
    params.setUserData(&userData);
    break;
  }
  default:
    break;
  }
}

bool ColiObject::isChar() const {
  if (coliObject == nullptr) {
    return false;
  }

  return coliObject->type == idcoli::OBJ_TYPE_CHARACTER;
}

bool ColiObject::isPhantom() const {
  if (coliObject == nullptr) {
    return false;
  }

  return coliObject->type == idcoli::OBJ_TYPE_PHANTOM;
}

const mm::Mat44 &ColiObject::getMatrix() const { return matrix; }

int ColiObject::getPriority() const {
  if (coliObject != nullptr && coliObject->type == idcoli::OBJ_TYPE_CHARACTER) {
    idcoli::IDColiParmsCharacter params(coliObject);
    return params.getPriority();
  }

  return 0;
}

bool ColiObject::isGrand() const {
  if (coliObject == nullptr) {
    return false;
  }

  return coliObject->type == idcoli::OBJ_TYPE_GRAND;
}

bool ColiObject::testAttribute(ColiAtrr attribute) const {
  if (coliObject != nullptr && coliObject->type == idcoli::OBJ_TYPE_CHARACTER) {
    idcoli::IDColiParmsCharacter params(coliObject);
    return params.isAttr(static_cast<idcoli::ColiAtrr>(attribute));
  }

  return false;
}

bool ColiObject::testState(ColiState state) const {
  if (coliObject != nullptr && coliObject->type == idcoli::OBJ_TYPE_CHARACTER) {
    idcoli::IDColiParmsCharacter params(coliObject);
    return params.isState(static_cast<idcoli::ColiState>(state));
  }

  return false;
}

void ColiObject::setActivate(bool isActivate) {
  if (isActivate) {
    clearState(COLI_STATE_INACTIVE);
  } else {
    setState(COLI_STATE_INACTIVE);
  }
}

bool ColiObject::isActivate() const { return !testState(COLI_STATE_INACTIVE); }

u32 ColiObject::getHitMaterialFlag() const {
  if (coliObject == nullptr) {
    return 0;
  }

  switch (coliObject->type) {
  case idcoli::OBJ_TYPE_CHARACTER: {
    idcoli::IDColiParmsCharacter params(coliObject);
    return ~params.getOffMaterialBit();
  }
  case idcoli::OBJ_TYPE_PHANTOM: {
    idcoli::IDColiParmsPhantom params(coliObject);
    return ~params.getOffMaterialBit();
  }
  default:
    return 0;
  }
}

bool ColiObject::testHitMaterialFlag(u32 flag) const { return (getHitMaterialFlag() & flag) != 0; }

u32 ColiObject::getMaterialFlag() const {
  if (coliObject == nullptr) {
    return 0;
  }

  switch (coliObject->type) {
  case idcoli::OBJ_TYPE_CHARACTER: {
    idcoli::IDColiParmsCharacter params(coliObject);
    return params.getMaterialBit();
  }
  case idcoli::OBJ_TYPE_PHANTOM: {
    idcoli::IDColiParmsPhantom params(coliObject);
    return params.getMaterialBit();
  }
  default:
    return 0;
  }
}

void ColiObject::setAdsorption(f32 adsorption) {
  if (coliObject != nullptr && coliObject->type == idcoli::OBJ_TYPE_CHARACTER) {
    idcoli::IDColiParmsCharacter params(coliObject);
    params.setAdsorption(adsorption);
  }
}

f32 ColiObject::getAdsorption() const {
  if (coliObject != nullptr && coliObject->type == idcoli::OBJ_TYPE_CHARACTER) {
    idcoli::IDColiParmsCharacter params(coliObject);
    return params.getAdsorption();
  }

  return 0.0f;
}

bool ColiObject::isLanding() const {
  if (coliObject != nullptr && coliObject->type == idcoli::OBJ_TYPE_CHARACTER) {
    return coliObject->flags & idcoli::IDColiObj::FLAG_LANDING;
  }

  return false;
}

bool ColiObject::isContactWall() const {
  if (coliObject != nullptr && coliObject->type == idcoli::OBJ_TYPE_CHARACTER) {
    return coliObject->flags & idcoli::IDColiObj::FLAG_CONTACT_WALL;
  }

  return false;
}

bool ColiObject::isOutRange() const {
  if (coliObject != nullptr && coliObject->type == idcoli::OBJ_TYPE_CHARACTER) {
    return coliObject->flags & idcoli::IDColiObj::FLAG_OUT_RANGE;
  }

  return false;
}

bool ColiObject::getAABB(mm::Vec3 &min, mm::Vec3 &max) const {
  if (coliObject == nullptr) {
    return false;
  }

  switch (coliObject->type) {
  case idcoli::OBJ_TYPE_CHARACTER: {
    idcoli::IDColiParmsCharacter params(coliObject);
    min = params.getMin();
    max = params.getMax();
    return true;
  }
  case idcoli::OBJ_TYPE_PHANTOM: {
    idcoli::IDColiParmsPhantom params(coliObject);
    min = params.getMin();
    max = params.getMax();
    return true;
  }
  default:
    return false;
  }
}

void ColiObject::enter(const IColiEventListener::EnterInfo &info) {
  bool isEnable = eventFlags.test(EVENT_ENTER);
  if (listener != nullptr && isEnable) {
    listener->enter(info);
  }
}

void ColiObject::leave(const IColiEventListener::LeaveInfo &info) {
  bool isEnable = eventFlags.test(EVENT_LEAVE);
  if (listener != nullptr && isEnable) {
    listener->leave(info);
  }
}

void ColiObject::contact(const IColiEventListener::EnterInfo &info) {
  if (listener != nullptr && eventFlags.test(EVENT_CONTACT)) {
    listener->contact(info);
  }
}

void ColiObject::update() {}

void ColiObject::postUpdate() {
  if (type == COLI_TYPE_STATIC && !(flags & FLAG_MATRIX_DIRTY)) {
    return;
  }

  if (referenceFrame.get() != nullptr && coliObject != nullptr) {
    flags &= ~FLAG_MATRIX_DIRTY;
    setMatrix(referenceFrame->getSyncedWorldMatrix());
  }
}

} // namespace fw
