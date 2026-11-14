#include "framework/coli/coli_object.h"

#include "framework/coli/coli_manager.h"
#include "framework/memory/framework_memory.h"
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
  case idcoli::unknown098_1: {
    idcoli::IDColiParmsCharacter params(m_coliObject);
    params.setOffMaterialBit(~flag);
    break;
  }
  case idcoli::unknown098_2: {
    idcoli::IDColiParmsPhantom params(m_coliObject);
    params.setOffMaterialBit(~flag);
    break;
  }
  default:
    break;
  }
}

ColiObject *ColiObject::createColiGrand(const void *binary) {
  idcoli::IDColiAccMan accMan;
  idcoli::IDColiObj *coliObject = accMan.createColiGrand(binary);
#line 44
  ColiObject *object = new (FrameworkMemory::getAllocator(5), 16, __FILE__, __LINE__) ColiObject();
  object->addRef();
  object->setColiObject(coliObject);
#line 54
  object->unknowne8.reset(new (FrameworkMemory::getAllocator(5), 16, __FILE__, __LINE__) unknown135(unknown031::TYPE_UNKNOWN_4, binary));
  ColiManager::get()->registObject(object);
  return object;
}

ColiObject *ColiObject::createColiCharacter(const ColiCharacterInfo &info, const mm::mtl::IntrusivePtr<ReferenceFrame> &frame) {
  idcoli::IDColiAccMan accMan;
  idcoli::IDColiObj *coliObject = accMan.createColiCharacter();
#line 71
  ColiObject *object = new (FrameworkMemory::getAllocator(5), 16, __FILE__, __LINE__) ColiObject();
  object->addRef();
  object->setColiObject(coliObject);
  object->setHitMaterialFlag(0xfffffffa);
  ColiManager::get()->registObject(object);
  if (object != nullptr) {
    setupColiCharacter(object, info, frame);
  }

  return object;
}

void ColiObject::setupColiCharacter(ColiObject *object, const ColiCharacterInfo &info, const mm::mtl::IntrusivePtr<ReferenceFrame> &frame) {
  if (object == nullptr) {
    return;
  }

  object->setColiType(info.unknown04);
  object->setPriority(info.unknown08);
  object->setHitMaterialFlag(info.unknown10);
  object->setMaterialFlag(info.unknown14);
  object->unknown58 = info.unknown20;
  object->unknown48 = info.unknown28;
  const mm::Mat44 &offset = info.unknown40;
  object->unknown60 = offset;
  object->unknowne0 = info.unknown18;
  for (int state = COLI_STATE_UNKNOWN_0; state <= COLI_STATE_UNKNOWN_1; state++) {
    if ((info.unknown0c & (1 << state)) != 0) {
      object->setState(static_cast<ColiState>(state));
    } else {
      object->clearState(static_cast<ColiState>(state));
    }
  }

  const unknown031 *shape = info.unknown80;
  switch (shape->unknown00) {
  case unknown031::TYPE_UNKNOWN_0:
    // __LINE__ of the game: it is the line argument of the operator new.
#line 156
    object->unknowne8.reset(new (FrameworkMemory::getAllocator(5), 16, __FILE__, __LINE__) unknown131(*static_cast<const unknown131 *>(shape)));
    object->bindReferenceFrame(frame);
    object->resetSphere(static_cast<const unknown131 *>(shape)->unknown04);
    break;
  case unknown031::TYPE_UNKNOWN_1:
#line 165
    object->unknowne8.reset(new (FrameworkMemory::getAllocator(5), 16, __FILE__, __LINE__) unknown132(*static_cast<const unknown132 *>(shape)));
    object->bindReferenceFrame(frame);
    object->resetCapsule(static_cast<const unknown132 *>(shape)->unknown04, static_cast<const unknown132 *>(shape)->unknown08, static_cast<const unknown132 *>(shape)->unknown0c);
    break;
  case unknown031::TYPE_UNKNOWN_2: {
    const unknown137 &box = static_cast<const unknown133 *>(shape)->unknown10;
#line 174
    object->unknowne8.reset(new (FrameworkMemory::getAllocator(5), 16, __FILE__, __LINE__) unknown133(*static_cast<const unknown133 *>(shape)));
    object->bindReferenceFrame(frame);
    object->resetBox(box.unknown00, box.unknown10);
    break;
  }
  case unknown031::TYPE_UNKNOWN_3:
#line 183
    object->unknowne8.reset(new (FrameworkMemory::getAllocator(5), 16, __FILE__, __LINE__) unknown134(*static_cast<const unknown134 *>(shape)));
    object->bindReferenceFrame(frame);
    object->resetCharacter(static_cast<const unknown134 *>(shape)->unknown04, static_cast<const unknown134 *>(shape)->unknown08);
    break;
  case unknown031::TYPE_UNKNOWN_5: {
#line 192
    object->unknowne8.reset(new (FrameworkMemory::getAllocator(5), 16, __FILE__, __LINE__) unknown135(*static_cast<const unknown135 *>(shape)));
    object->bindReferenceFrame(frame);
    idcoli::IDColiParmsCharacter params(object->m_coliObject);
    params.createData(static_cast<const unknown135 *>(shape)->unknown08);
    break;
  }
  default:
    break;
  }

  if (frame.get() != nullptr) {
    object->setInstantlyMatrix(frame->getSyncedWorldMatrix());
  }
}

ColiObject *ColiObject::createColiPhantom(const ColiPhantomInfo &info, const mm::mtl::IntrusivePtr<ReferenceFrame> &frame) {
  idcoli::IDColiAccMan accMan;
  idcoli::IDColiObj *coliObject = accMan.createColiPhantom();
#line 100
  ColiObject *object = new (FrameworkMemory::getAllocator(5), 16, __FILE__, __LINE__) ColiObject();
  object->addRef();
  object->setColiObject(coliObject);
  ColiManager::get()->registObject(object);
  if (object != nullptr) {
    setupColiPhantom(object, info, frame);
  }

  return object;
}

void ColiObject::setupColiPhantom(ColiObject *object, const ColiPhantomInfo &info, const mm::mtl::IntrusivePtr<ReferenceFrame> &frame) {
  if (object == nullptr) {
    return;
  }

  object->setColiType(info.unknown04);
  object->setPriority(info.unknown08);
  object->setHitMaterialFlag(info.unknown10);
  object->unknown58 = info.unknown20;
  object->unknown48 = info.unknown28;
  const mm::Mat44 &offset = info.unknown40;
  object->unknown60 = offset;
  object->unknowne0 = info.unknown18;
  for (int state = COLI_STATE_UNKNOWN_0; state <= COLI_STATE_UNKNOWN_1; state++) {
    if ((info.unknown0c & (1 << state)) != 0) {
      object->setState(static_cast<ColiState>(state));
    } else {
      object->clearState(static_cast<ColiState>(state));
    }
  }

  const unknown031 *shape = info.unknown80;
  switch (shape->unknown00) {
  case unknown031::TYPE_UNKNOWN_0:
    // __LINE__ of the game: it is the line argument of the operator new.
#line 245
    object->unknowne8.reset(new (FrameworkMemory::getAllocator(5), 16, __FILE__, __LINE__) unknown131(*static_cast<const unknown131 *>(shape)));
    object->bindReferenceFrame(frame);
    object->resetSphere(static_cast<const unknown131 *>(shape)->unknown04);
    break;
  case unknown031::TYPE_UNKNOWN_1:
#line 254
    object->unknowne8.reset(new (FrameworkMemory::getAllocator(5), 16, __FILE__, __LINE__) unknown132(*static_cast<const unknown132 *>(shape)));
    object->bindReferenceFrame(frame);
    object->resetCapsule(static_cast<const unknown132 *>(shape)->unknown04, static_cast<const unknown132 *>(shape)->unknown08, false);
    break;
  case unknown031::TYPE_UNKNOWN_2: {
    const unknown137 &box = static_cast<const unknown133 *>(shape)->unknown10;
#line 263
    object->unknowne8.reset(new (FrameworkMemory::getAllocator(5), 16, __FILE__, __LINE__) unknown133(*static_cast<const unknown133 *>(shape)));
    object->bindReferenceFrame(frame);
    object->resetBox(box.unknown00, box.unknown10);
    break;
  }
  default:
    break;
  }

  if (frame.get() != nullptr) {
    object->setInstantlyMatrix(frame->getSyncedWorldMatrix());
  }
}

void ColiObject::setColiType(ColiType type) {
  this->unknown30 = type;
  if (type == COLI_TYPE_UNKNOWN_0) {
    unknown34 |= FLAG_UNKNOWN_0;
  }
}

void ColiObject::setPriority(int priority) {
  if (m_coliObject != nullptr && m_coliObject->unknown24 == idcoli::unknown098_1) {
    idcoli::IDColiParmsCharacter params(m_coliObject);
    params.setPriority(priority);
  }
}

void ColiObject::setMaterialFlag(u32 flag) {
  if (m_coliObject == nullptr) {
    return;
  }

  switch (m_coliObject->unknown24) {
  case idcoli::unknown098_1: {
    idcoli::IDColiParmsCharacter params(m_coliObject);
    params.setMaterialBit(flag);
    break;
  }
  case idcoli::unknown098_2: {
    idcoli::IDColiParmsPhantom params(m_coliObject);
    params.setMaterialBit(flag);
    break;
  }
  default:
    break;
  }
}

void ColiObject::setState(ColiState state) {
  if (m_coliObject != nullptr && m_coliObject->unknown24 == idcoli::unknown098_1) {
    idcoli::IDColiParmsCharacter params(m_coliObject);
    params.setState(static_cast<idcoli::ColiState>(state));
  }
}

void ColiObject::clearState(ColiState state) {
  if (m_coliObject != nullptr && m_coliObject->unknown24 == idcoli::unknown098_1) {
    idcoli::IDColiParmsCharacter params(m_coliObject);
    params.clearState(static_cast<idcoli::ColiState>(state));
  }
}

void ColiObject::bindReferenceFrame(const mm::mtl::IntrusivePtr<ReferenceFrame> &frame) { unknown28 = frame; }

void ColiObject::resetSphere(f32 radius) {
  if (unknowne8.get() == nullptr || unknowne8.get()->unknown00 != unknown031::TYPE_UNKNOWN_0) {
    return;
  }

  static_cast<unknown131 *>(unknowne8.get())->unknown04 = radius;
  if (m_coliObject == nullptr) {
    return;
  }

  switch (m_coliObject->unknown24) {
  case idcoli::unknown098_1: {
    idcoli::IDColiParmsCharacter params(m_coliObject);
    params.createSphere(radius);
    break;
  }
  case idcoli::unknown098_2: {
    idcoli::IDColiParmsPhantom params(m_coliObject);
    params.createSphere(radius);
    break;
  }
  default:
    break;
  }
}

void ColiObject::resetCapsule(f32 radius, f32 height, bool flag) {
  unknown031 *coliShape = unknowne8.get();
  if (coliShape == nullptr || coliShape->unknown00 != unknown031::TYPE_UNKNOWN_1) {
    return;
  }

  static_cast<unknown132 *>(coliShape)->unknown04 = radius;
  static_cast<unknown132 *>(coliShape)->unknown08 = height;
  if (m_coliObject == nullptr) {
    return;
  }

  switch (m_coliObject->unknown24) {
  case idcoli::unknown098_1: {
    idcoli::IDColiParmsCharacter params(m_coliObject);
    params.createCapsule(radius, height, flag);
    break;
  }
  case idcoli::unknown098_2: {
    idcoli::IDColiParmsPhantom params(m_coliObject);
    params.createCapsule(radius, height);
    break;
  }
  default:
    break;
  }
}

void ColiObject::resetBox(const mm::Vec3 &size, bool flag) {
  if (unknowne8.get() == nullptr || unknowne8.get()->unknown00 != unknown031::TYPE_UNKNOWN_2) {
    return;
  }

  static_cast<unknown133 *>(unknowne8.get())->unknown10.unknown00 = size;
  if (m_coliObject == nullptr) {
    return;
  }

  switch (m_coliObject->unknown24) {
  case idcoli::unknown098_1: {
    idcoli::IDColiParmsCharacter params(m_coliObject);
    params.createBox(size, flag);
    break;
  }
  case idcoli::unknown098_2: {
    idcoli::IDColiParmsPhantom params(m_coliObject);
    params.createBox(size);
    break;
  }
  default:
    break;
  }
}

void ColiObject::resetCharacter(f32 radius, f32 height) {
  unknown031 *coliShape = unknowne8.get();
  if (coliShape == nullptr || coliShape->unknown00 != unknown031::TYPE_UNKNOWN_3) {
    return;
  }

  static_cast<unknown134 *>(coliShape)->unknown04 = radius;
  static_cast<unknown134 *>(coliShape)->unknown08 = height;
  if (m_coliObject == nullptr) {
    return;
  }

  switch (m_coliObject->unknown24) {
  case idcoli::unknown098_1: {
    idcoli::IDColiParmsCharacter params(m_coliObject);
    params.createCharacter(radius, height);
    break;
  }
  case idcoli::unknown098_2: {
    idcoli::IDColiParmsPhantom params(m_coliObject);
    params.createCharacter(radius, height);
    break;
  }
  default:
    break;
  }
}

void ColiObject::setMatrix(const mm::Mat44 &matrix) {
  f32 scale = unknowne0;
  m_matrix = matrix;
  mm::Mat44 world(matrix);
  for (u32 row = 0; row < 3; row++) {
    for (u32 column = 0; column < 3; column++) {
      world.rows[row][column] = scale * world.rows[row][column];
    }
  }
  world = unknown60 * world;
  if (m_coliObject != nullptr) {
    if (m_coliObject->unknown24 == idcoli::unknown098_1) {
      idcoli::IDColiParmsCharacter params(m_coliObject);
      params.setMatrix(world);
    } else if (m_coliObject->unknown24 == idcoli::unknown098_2) {
      idcoli::IDColiParmsPhantom params(m_coliObject);
      params.setMatrix(world);
    }
  }
}

void ColiObject::setInstantlyMatrix(const mm::Mat44 &matrix) {
  f32 scale = unknowne0;
  m_matrix = matrix;
  mm::Mat44 world(matrix);
  for (u32 row = 0; row < 3; row++) {
    for (u32 column = 0; column < 3; column++) {
      world.rows[row][column] = scale * world.rows[row][column];
    }
  }
  world = unknown60 * world;
  if (m_coliObject != nullptr) {
    if (m_coliObject->unknown24 == idcoli::unknown098_1) {
      idcoli::IDColiParmsCharacter params(m_coliObject);
      params.setInstantlyMatrix(world);
    } else if (m_coliObject->unknown24 == idcoli::unknown098_2) {
      idcoli::IDColiParmsPhantom params(m_coliObject);
      params.setInstantlyMatrix(world);
    }
  }
}

ColiObject::ColiObject() : m_coliObject(nullptr), unknown34(0), unknown58(nullptr), unknowne0(1.0f) {
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
  case idcoli::unknown098_1: {
    idcoli::IDColiParmsCharacter params(m_coliObject);
    params.setUserData(&unknownf0);
    break;
  }
  case idcoli::unknown098_2: {
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

  return m_coliObject->unknown24 == idcoli::unknown098_1;
}

bool ColiObject::isPhantom() const {
  if (m_coliObject == nullptr) {
    return false;
  }

  return m_coliObject->unknown24 == idcoli::unknown098_2;
}

const mm::Mat44 &ColiObject::getMatrix() const { return m_matrix; }

int ColiObject::getPriority() const {
  if (m_coliObject != nullptr && m_coliObject->unknown24 == idcoli::unknown098_1) {
    idcoli::IDColiParmsCharacter params(m_coliObject);
    return params.getPriority();
  }

  return 0;
}

bool ColiObject::isGrand() const {
  if (m_coliObject == nullptr) {
    return false;
  }

  return m_coliObject->unknown24 == idcoli::unknown098_3;
}

bool ColiObject::testAttribute(ColiAtrr attribute) const {
  if (m_coliObject != nullptr && m_coliObject->unknown24 == idcoli::unknown098_1) {
    idcoli::IDColiParmsCharacter params(m_coliObject);
    return params.isAttr(static_cast<idcoli::ColiAtrr>(attribute));
  }

  return false;
}

bool ColiObject::testState(ColiState state) const {
  if (m_coliObject != nullptr && m_coliObject->unknown24 == idcoli::unknown098_1) {
    idcoli::IDColiParmsCharacter params(m_coliObject);
    return params.isState(static_cast<idcoli::ColiState>(state));
  }

  return false;
}

void ColiObject::setActivate(bool isActivate) {
  if (isActivate) {
    clearState(COLI_STATE_UNKNOWN_2);
  } else {
    setState(COLI_STATE_UNKNOWN_2);
  }
}

bool ColiObject::isActivate() const { return !testState(COLI_STATE_UNKNOWN_2); }

u32 ColiObject::getHitMaterialFlag() const {
  if (m_coliObject == nullptr) {
    return 0;
  }

  switch (m_coliObject->unknown24) {
  case idcoli::unknown098_1: {
    idcoli::IDColiParmsCharacter params(m_coliObject);
    return ~params.getOffMaterialBit();
  }
  case idcoli::unknown098_2: {
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
  case idcoli::unknown098_1: {
    idcoli::IDColiParmsCharacter params(m_coliObject);
    return params.getMaterialBit();
  }
  case idcoli::unknown098_2: {
    idcoli::IDColiParmsPhantom params(m_coliObject);
    return params.getMaterialBit();
  }
  default:
    return 0;
  }
}

void ColiObject::setAdsorption(f32 adsorption) {
  if (m_coliObject != nullptr && m_coliObject->unknown24 == idcoli::unknown098_1) {
    idcoli::IDColiParmsCharacter params(m_coliObject);
    params.setAdsorption(adsorption);
  }
}

f32 ColiObject::getAdsorption() const {
  if (m_coliObject != nullptr && m_coliObject->unknown24 == idcoli::unknown098_1) {
    idcoli::IDColiParmsCharacter params(m_coliObject);
    return params.getAdsorption();
  }

  return 0.0f;
}

bool ColiObject::isLanding() const {
  if (m_coliObject != nullptr && m_coliObject->unknown24 == idcoli::unknown098_1) {
    return m_coliObject->unknown20 & idcoli::IDColiObj::FLAG_UNKNOWN_0;
  }

  return false;
}

bool ColiObject::isContactWall() const {
  if (m_coliObject != nullptr && m_coliObject->unknown24 == idcoli::unknown098_1) {
    return m_coliObject->unknown20 & idcoli::IDColiObj::FLAG_UNKNOWN_2;
  }

  return false;
}

bool ColiObject::isOutRange() const {
  if (m_coliObject != nullptr && m_coliObject->unknown24 == idcoli::unknown098_1) {
    return m_coliObject->unknown20 & idcoli::IDColiObj::FLAG_UNKNOWN_1;
  }

  return false;
}

bool ColiObject::getAABB(mm::Vec3 &min, mm::Vec3 &max) const {
  if (m_coliObject == nullptr) {
    return false;
  }

  switch (m_coliObject->unknown24) {
  case idcoli::unknown098_1: {
    idcoli::IDColiParmsCharacter params(m_coliObject);
    min = params.getMin();
    max = params.getMax();
    return true;
  }
  case idcoli::unknown098_2: {
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
  bool isEnable = unknown48.unknown001(EVENT_UNKNOWN_0);
  if (unknown48.unknown08 != nullptr && isEnable) {
    unknown48.unknown08->enter(info);
  }
}

void ColiObject::leave(const IColiEventListener::LeaveInfo &info) {
  bool isEnable = unknown48.unknown001(EVENT_UNKNOWN_2);
  if (unknown48.unknown08 != nullptr && isEnable) {
    unknown48.unknown08->leave(info);
  }
}

void IColiEventListener::contact(const EnterInfo &info) {}

void ColiObject::contact(const IColiEventListener::EnterInfo &info) {
  if (unknown48.unknown08 != nullptr && unknown48.unknown001(EVENT_UNKNOWN_1)) {
    unknown48.unknown08->contact(info);
  }
}

void ColiObject::update() {}

void ColiObject::postUpdate() {
  if (unknown30 == COLI_TYPE_UNKNOWN_0 && !(unknown34 & FLAG_UNKNOWN_0)) {
    return;
  }

  if (unknown28.get() != nullptr && m_coliObject != nullptr) {
    unknown34 &= ~FLAG_UNKNOWN_0;
    setMatrix(unknown28->getSyncedWorldMatrix());
  }
}

} // namespace fw

template void mm::mtl::Vector<fw::ColiObject *>::expand(size_t, size_t);
template void mm::mtl::Vector<fw::ColiObject *>::extend(size_t, size_t, fw::ColiObject *const &);
template void mm::mtl::Vector<fw::ColiObject *>::resize(size_t, fw::ColiObject *const &);
