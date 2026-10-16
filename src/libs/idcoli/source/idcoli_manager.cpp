#include "idcoli/idcoli.h"
#include "types.h"

namespace ml {
class WinProc;
} // namespace ml

namespace idcoli {

void IDColiManager::update() {
  addDelUpdate();
  for (int i = 0; i < 4; i++) {
    updateList(m_objLists[i]);
  }
}

void IDColiManager::consistentUpdate() {
  m_treeTops[0]->begin();
  m_treeTops[1]->begin();
  updateConsistentList(m_objLists[1]);
  updateConsistentList(m_objLists[2]);
  m_treeTops[0]->end();
  m_treeTops[1]->end();
}

void IDColiManager::tail() {
  s_nDebIdx = s_nDebIdx == 0;
  s_nStkIdx = s_nDebIdx == 0;
}

IDColiObj *IDColiManager::getUseObject(ColiLinkList<IDColiObj> &list) {
  for (IDColiObj *object = list.m_head; object != nullptr; object = object->m_next) {
    if (!object->isDeleteCall() && !(object->m_state & 4) && !(object->m_updateFlags & 0x80)) {
      return object;
    }
  }

  return nullptr;
}

bool IDColiObj::isDeleteCall() const { return (m_updateFlags & (1 << IDColiManager::s_nDebIdx)) != 0; }

void IDColiManager::updateList(ColiLinkList<IDColiObj> &list) {
  for (IDColiObj *object = list.m_head; object != nullptr; object = object->m_next) {
    object->update();
  }
}

void IDColiManager::poolUpdate(void *object) { static_cast<IDColiObj *>(object)->update(); }

int IDColiManager::isGblId(u32 id) { return m_gblIdTbl[id >> 5] & (1 << (id & 31)); }

void IDColiManager::setGblId(u32 id, bool isClear) {
  if (isClear) {
    m_gblIdTbl[id >> 5] &= ~(1 << (id & 31));
  } else {
    m_gblIdTbl[id >> 5] |= 1 << (id & 31);
  }
}

void *IDColiManager::getGblIdTbl() { return m_gblIdTbl; }

void IDColiManager::openDebugWindow(ml::WinProc *window) {}

void IDColiManager::debugDrawCharacter(bool isDraw) {}

void IDColiManager::debugDrawGrand(bool isDraw) {}

void IDColiManager::debugDrawPhantom(bool isDraw) {}

} // namespace idcoli
