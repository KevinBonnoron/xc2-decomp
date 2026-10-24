#include "idcoli/idcoli.h"
#include "mm_math/mm_mat44.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace idcoli {
enum ColiAtrr : int;
enum ColiState : int;

IDColiParmsBase::IDColiParmsBase(IDColiObj *object) : m_object(static_cast<IDColiObjBase *>(object)) {}

void IDColiParmsBase::setPriority(int priority) { m_object->unknown1cc = priority; }

int IDColiParmsBase::getPriority() const { return m_object->unknown1cc; }

void IDColiParmsBase::setUserData(void *userData) { m_object->unknown48 = userData; }

void *IDColiParmsBase::getUserData() { return m_object->unknown48; }

bool IDColiParmsBase::isAttr(ColiAtrr attribute) const { return (m_object->unknown20 & (1 << attribute)) != 0; }

bool IDColiParmsBase::isState(ColiState state) const { return (m_object->unknown18 & (1 << state)) != 0; }

void IDColiParmsBase::setState(ColiState state) {
  IDColiObjBase *object = m_object;
  object->unknown18 |= 1 << state;
}

void IDColiParmsBase::clearState(ColiState state) {
  IDColiObjBase *object = m_object;
  object->unknown18 &= ~(1 << state);
}

void IDColiParmsBase::setMaterialBit(u32 bit) { m_object->unknown2c = bit; }

u32 IDColiParmsBase::getMaterialBit() const { return m_object->unknown2c; }

u32 *IDColiParmsBase::getMaterialData() { return &m_object->unknown28; }

void IDColiParmsBase::setOffMaterialBit(u32 bit) { m_object->unknownc8 = bit; }

u32 IDColiParmsBase::getOffMaterialBit() const { return m_object->unknownc8; }

void IDColiParmsBase::setMatrix(const mm::Mat44 &matrix) {
  m_object->unknown70 = matrix;
  m_object->unknown1c |= IDColiObj::UPDATE_MATRIX << IDColiManager::s_nStkIdx;
}

const mm::Mat44 &IDColiParmsBase::getMatrix() const { return m_object->unknown70; }

const mm::Vec3 &IDColiParmsBase::getMax() const { return m_object->unknown50; }

const mm::Vec3 &IDColiParmsBase::getMin() const { return m_object->unknown60; }

void IDColiParmsBase::setInstantlyMatrix(const mm::Mat44 &matrix) {
  m_object->unknown70 = matrix;
  m_object->unknown1c |= IDColiObj::UPDATE_MATRIX << IDColiManager::s_nStkIdx;
  m_object->sizeUpdate();
}

} // namespace idcoli
