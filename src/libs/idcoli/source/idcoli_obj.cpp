#include "idcoli/idcoli.h"

namespace idcoli {

IDColiObj::IDColiObj() {
  m_next = nullptr;
  m_updateFlags = 0;
  m_attr = 9;
  m_state = 3;
  _40 = 0;
  m_userData = nullptr;
  m_prev = nullptr;
  _30 = 0;
  _38 = 0;
  m_materialData = 0;
  m_materialBit = 0;
}

void IDColiObj::release() {
  m_userData = nullptr;
  m_updateFlags |= 1 << IDColiManager::s_nStkIdx;
}

void IDColiObj::setDeleteCall() { m_updateFlags |= 1 << IDColiManager::s_nStkIdx; }

bool IDColiObj::isDeleteAll() const { return (m_updateFlags & 3) != 0; }

} // namespace idcoli
