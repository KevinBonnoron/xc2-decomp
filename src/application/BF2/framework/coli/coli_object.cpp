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

void ColiObject::setColiObject(idcoli::IDColiObj *object) { m_coliObject = object; }

void ColiObject::setHitMaterialFlag(u32 flag) {
  if (m_coliObject == nullptr) {
    return;
  }

  switch (m_coliObject->unknown24) {
  case idcoli::OBJ_TYPE_CHARACTER: {
    idcoli::IDColiParmsCharacter params(m_coliObject);
    params.setOffMaterialBit(~flag);
    break;
  }
  case idcoli::OBJ_TYPE_PHANTOM: {
    idcoli::IDColiParmsPhantom params(m_coliObject);
    params.setOffMaterialBit(~flag);
    break;
  }
  default:
    break;
  }
}

void ColiObject::setColiType(ColiType type) {
  this->unknown30 = type;
  if (type == COLI_TYPE_STATIC) {
    unknown34 |= FLAG_MATRIX_DIRTY;
  }
}

void ColiObject::setPriority(int priority) {
  if (m_coliObject != nullptr && m_coliObject->unknown24 == idcoli::OBJ_TYPE_CHARACTER) {
    idcoli::IDColiParmsCharacter params(m_coliObject);
    params.setPriority(priority);
  }
}

void ColiObject::setMaterialFlag(u32 flag) {
  if (m_coliObject == nullptr) {
    return;
  }

  switch (m_coliObject->unknown24) {
  case idcoli::OBJ_TYPE_CHARACTER: {
    idcoli::IDColiParmsCharacter params(m_coliObject);
    params.setMaterialBit(flag);
    break;
  }
  case idcoli::OBJ_TYPE_PHANTOM: {
    idcoli::IDColiParmsPhantom params(m_coliObject);
    params.setMaterialBit(flag);
    break;
  }
  default:
    break;
  }
}

void ColiObject::setState(ColiState state) {
  if (m_coliObject != nullptr && m_coliObject->unknown24 == idcoli::OBJ_TYPE_CHARACTER) {
    idcoli::IDColiParmsCharacter params(m_coliObject);
    params.setState(static_cast<idcoli::ColiState>(state));
  }
}

void ColiObject::clearState(ColiState state) {
  if (m_coliObject != nullptr && m_coliObject->unknown24 == idcoli::OBJ_TYPE_CHARACTER) {
    idcoli::IDColiParmsCharacter params(m_coliObject);
    params.clearState(static_cast<idcoli::ColiState>(state));
  }
}

void ColiObject::bindReferenceFrame(const mm::mtl::IntrusivePtr<ReferenceFrame> &frame) { unknown28 = frame; }

void ColiObject::resetSphere(f32 radius) {
  if (unknowne8 == nullptr || unknowne8->unknown00 != ColiShape::TYPE_SPHERE) {
    return;
  }

  unknowne8->unknown04 = radius;
  if (m_coliObject == nullptr) {
    return;
  }

  switch (m_coliObject->unknown24) {
  case idcoli::OBJ_TYPE_CHARACTER: {
    idcoli::IDColiParmsCharacter params(m_coliObject);
    params.createSphere(radius);
    break;
  }
  case idcoli::OBJ_TYPE_PHANTOM: {
    idcoli::IDColiParmsPhantom params(m_coliObject);
    params.createSphere(radius);
    break;
  }
  default:
    break;
  }
}

void ColiObject::resetCapsule(f32 radius, f32 height, bool flag) {
  ColiShape *coliShape = unknowne8;
  if (coliShape == nullptr || coliShape->unknown00 != ColiShape::TYPE_CAPSULE) {
    return;
  }

  coliShape->unknown04 = radius;
  coliShape->unknown08 = height;
  if (m_coliObject == nullptr) {
    return;
  }

  switch (m_coliObject->unknown24) {
  case idcoli::OBJ_TYPE_CHARACTER: {
    idcoli::IDColiParmsCharacter params(m_coliObject);
    params.createCapsule(radius, height, flag);
    break;
  }
  case idcoli::OBJ_TYPE_PHANTOM: {
    idcoli::IDColiParmsPhantom params(m_coliObject);
    params.createCapsule(radius, height);
    break;
  }
  default:
    break;
  }
}

void ColiObject::resetBox(const mm::Vec3 &size, bool flag) {
  if (unknowne8 == nullptr || unknowne8->unknown00 != ColiShape::TYPE_BOX) {
    return;
  }

  unknowne8->unknown10 = size;
  if (m_coliObject == nullptr) {
    return;
  }

  switch (m_coliObject->unknown24) {
  case idcoli::OBJ_TYPE_CHARACTER: {
    idcoli::IDColiParmsCharacter params(m_coliObject);
    params.createBox(size, flag);
    break;
  }
  case idcoli::OBJ_TYPE_PHANTOM: {
    idcoli::IDColiParmsPhantom params(m_coliObject);
    params.createBox(size);
    break;
  }
  default:
    break;
  }
}

void ColiObject::resetCharacter(f32 radius, f32 height) {
  ColiShape *coliShape = unknowne8;
  if (coliShape == nullptr || coliShape->unknown00 != ColiShape::TYPE_CHARACTER) {
    return;
  }

  coliShape->unknown04 = radius;
  coliShape->unknown08 = height;
  if (m_coliObject == nullptr) {
    return;
  }

  switch (m_coliObject->unknown24) {
  case idcoli::OBJ_TYPE_CHARACTER: {
    idcoli::IDColiParmsCharacter params(m_coliObject);
    params.createCharacter(radius, height);
    break;
  }
  case idcoli::OBJ_TYPE_PHANTOM: {
    idcoli::IDColiParmsPhantom params(m_coliObject);
    params.createCharacter(radius, height);
    break;
  }
  default:
    break;
  }
}

ColiObject::ColiObject() : m_coliObject(nullptr), unknown34(0), unknown50(nullptr), unknown58(nullptr), unknowne0(1.0f), unknowne8(nullptr) {
  unknown60 = mm::Mat44::identity;
  m_matrix = mm::Mat44::identity;
}

ColiObject::~ColiObject() {
  if (m_coliObject != nullptr) {
    ColiManager::get()->getInterface();
    ml::WorkCpu::getFrameCount();
    m_coliObject->release();
    m_coliObject = nullptr;
  }

  ColiManager::get()->removeObject(this);
  if (unknowne8 != nullptr) {
    delete unknowne8;
    unknowne8 = nullptr;
  }
}

void ColiObject::setOwner(UpdatableObject *owner) {
  if (owner != nullptr) {
    this->unknown38 = owner->unknown18;
  } else {
    this->unknown38 = HandlePtr<UpdatableObject>();
  }
}

UpdatableObject *ColiObject::getOwner() const { return unknown38.get(); }

void ColiObject::setHandle(u32 handle) {
  unknownf0.unknown08 = handle;
  if (m_coliObject == nullptr) {
    return;
  }

  switch (m_coliObject->unknown24) {
  case idcoli::OBJ_TYPE_CHARACTER: {
    idcoli::IDColiParmsCharacter params(m_coliObject);
    params.setUserData(&unknownf0);
    break;
  }
  case idcoli::OBJ_TYPE_PHANTOM: {
    idcoli::IDColiParmsPhantom params(m_coliObject);
    params.setUserData(&unknownf0);
    break;
  }
  default:
    break;
  }
}

bool ColiObject::isChar() const {
  if (m_coliObject == nullptr) {
    return false;
  }

  return m_coliObject->unknown24 == idcoli::OBJ_TYPE_CHARACTER;
}

bool ColiObject::isPhantom() const {
  if (m_coliObject == nullptr) {
    return false;
  }

  return m_coliObject->unknown24 == idcoli::OBJ_TYPE_PHANTOM;
}

const mm::Mat44 &ColiObject::getMatrix() const { return m_matrix; }

int ColiObject::getPriority() const {
  if (m_coliObject != nullptr && m_coliObject->unknown24 == idcoli::OBJ_TYPE_CHARACTER) {
    idcoli::IDColiParmsCharacter params(m_coliObject);
    return params.getPriority();
  }

  return 0;
}

bool ColiObject::isGrand() const {
  if (m_coliObject == nullptr) {
    return false;
  }

  return m_coliObject->unknown24 == idcoli::OBJ_TYPE_GRAND;
}

bool ColiObject::testAttribute(ColiAtrr attribute) const {
  if (m_coliObject != nullptr && m_coliObject->unknown24 == idcoli::OBJ_TYPE_CHARACTER) {
    idcoli::IDColiParmsCharacter params(m_coliObject);
    return params.isAttr(static_cast<idcoli::ColiAtrr>(attribute));
  }

  return false;
}

bool ColiObject::testState(ColiState state) const {
  if (m_coliObject != nullptr && m_coliObject->unknown24 == idcoli::OBJ_TYPE_CHARACTER) {
    idcoli::IDColiParmsCharacter params(m_coliObject);
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
  if (m_coliObject == nullptr) {
    return 0;
  }

  switch (m_coliObject->unknown24) {
  case idcoli::OBJ_TYPE_CHARACTER: {
    idcoli::IDColiParmsCharacter params(m_coliObject);
    return ~params.getOffMaterialBit();
  }
  case idcoli::OBJ_TYPE_PHANTOM: {
    idcoli::IDColiParmsPhantom params(m_coliObject);
    return ~params.getOffMaterialBit();
  }
  default:
    return 0;
  }
}

bool ColiObject::testHitMaterialFlag(u32 flag) const { return (getHitMaterialFlag() & flag) != 0; }

u32 ColiObject::getMaterialFlag() const {
  if (m_coliObject == nullptr) {
    return 0;
  }

  switch (m_coliObject->unknown24) {
  case idcoli::OBJ_TYPE_CHARACTER: {
    idcoli::IDColiParmsCharacter params(m_coliObject);
    return params.getMaterialBit();
  }
  case idcoli::OBJ_TYPE_PHANTOM: {
    idcoli::IDColiParmsPhantom params(m_coliObject);
    return params.getMaterialBit();
  }
  default:
    return 0;
  }
}

void ColiObject::setAdsorption(f32 adsorption) {
  if (m_coliObject != nullptr && m_coliObject->unknown24 == idcoli::OBJ_TYPE_CHARACTER) {
    idcoli::IDColiParmsCharacter params(m_coliObject);
    params.setAdsorption(adsorption);
  }
}

f32 ColiObject::getAdsorption() const {
  if (m_coliObject != nullptr && m_coliObject->unknown24 == idcoli::OBJ_TYPE_CHARACTER) {
    idcoli::IDColiParmsCharacter params(m_coliObject);
    return params.getAdsorption();
  }

  return 0.0f;
}

bool ColiObject::isLanding() const {
  if (m_coliObject != nullptr && m_coliObject->unknown24 == idcoli::OBJ_TYPE_CHARACTER) {
    return m_coliObject->unknown20 & idcoli::IDColiObj::FLAG_LANDING;
  }

  return false;
}

bool ColiObject::isContactWall() const {
  if (m_coliObject != nullptr && m_coliObject->unknown24 == idcoli::OBJ_TYPE_CHARACTER) {
    return m_coliObject->unknown20 & idcoli::IDColiObj::FLAG_CONTACT_WALL;
  }

  return false;
}

bool ColiObject::isOutRange() const {
  if (m_coliObject != nullptr && m_coliObject->unknown24 == idcoli::OBJ_TYPE_CHARACTER) {
    return m_coliObject->unknown20 & idcoli::IDColiObj::FLAG_OUT_RANGE;
  }

  return false;
}

bool ColiObject::getAABB(mm::Vec3 &min, mm::Vec3 &max) const {
  if (m_coliObject == nullptr) {
    return false;
  }

  switch (m_coliObject->unknown24) {
  case idcoli::OBJ_TYPE_CHARACTER: {
    idcoli::IDColiParmsCharacter params(m_coliObject);
    min = params.getMin();
    max = params.getMax();
    return true;
  }
  case idcoli::OBJ_TYPE_PHANTOM: {
    idcoli::IDColiParmsPhantom params(m_coliObject);
    min = params.getMin();
    max = params.getMax();
    return true;
  }
  default:
    return false;
  }
}

void ColiObject::enter(const IColiEventListener::EnterInfo &info) {
  bool isEnable = unknown48.test(EVENT_ENTER);
  if (unknown50 != nullptr && isEnable) {
    unknown50->enter(info);
  }
}

void ColiObject::leave(const IColiEventListener::LeaveInfo &info) {
  bool isEnable = unknown48.test(EVENT_LEAVE);
  if (unknown50 != nullptr && isEnable) {
    unknown50->leave(info);
  }
}

void ColiObject::contact(const IColiEventListener::EnterInfo &info) {
  if (unknown50 != nullptr && unknown48.test(EVENT_CONTACT)) {
    unknown50->contact(info);
  }
}

void ColiObject::update() {}

void ColiObject::postUpdate() {
  if (unknown30 == COLI_TYPE_STATIC && !(unknown34 & FLAG_MATRIX_DIRTY)) {
    return;
  }

  if (unknown28.get() != nullptr && m_coliObject != nullptr) {
    unknown34 &= ~FLAG_MATRIX_DIRTY;
    setMatrix(unknown28->getSyncedWorldMatrix());
  }
}

} // namespace fw
