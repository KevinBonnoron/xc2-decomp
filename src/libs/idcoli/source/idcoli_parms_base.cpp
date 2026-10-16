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

void IDColiParmsBase::setPriority(int priority) { m_object->m_priority = priority; }

int IDColiParmsBase::getPriority() const { return m_object->m_priority; }

void IDColiParmsBase::setUserData(void *userData) { m_object->m_userData = userData; }

void *IDColiParmsBase::getUserData() { return m_object->m_userData; }

bool IDColiParmsBase::isAttr(ColiAtrr attribute) const { return (m_object->m_attr & (1 << attribute)) != 0; }

bool IDColiParmsBase::isState(ColiState state) const { return (m_object->m_state & (1 << state)) != 0; }

void IDColiParmsBase::setState(ColiState state) {
  IDColiObjBase *object = m_object;
  object->m_state |= 1 << state;
}

void IDColiParmsBase::clearState(ColiState state) {
  IDColiObjBase *object = m_object;
  object->m_state &= ~(1 << state);
}

void IDColiParmsBase::setMaterialBit(u32 bit) { m_object->m_materialBit = bit; }

u32 IDColiParmsBase::getMaterialBit() const { return m_object->m_materialBit; }

u32 *IDColiParmsBase::getMaterialData() { return &m_object->m_materialData; }

void IDColiParmsBase::setOffMaterialBit(u32 bit) { m_object->m_offMaterialBit = bit; }

u32 IDColiParmsBase::getOffMaterialBit() const { return m_object->m_offMaterialBit; }

void IDColiParmsBase::setMatrix(const mm::Mat44 &matrix) {
  m_object->m_matrix = matrix;
  m_object->m_updateFlags |= IDColiObj::UPDATE_MATRIX << IDColiManager::s_nStkIdx;
}

const mm::Mat44 &IDColiParmsBase::getMatrix() const { return m_object->m_matrix; }

const mm::Vec3 &IDColiParmsBase::getMax() const { return m_object->m_max; }

const mm::Vec3 &IDColiParmsBase::getMin() const { return m_object->m_min; }

void IDColiParmsBase::setInstantlyMatrix(const mm::Mat44 &matrix) {
  m_object->m_matrix = matrix;
  m_object->m_updateFlags |= IDColiObj::UPDATE_MATRIX << IDColiManager::s_nStkIdx;
  m_object->sizeUpdate();
}

} // namespace idcoli
