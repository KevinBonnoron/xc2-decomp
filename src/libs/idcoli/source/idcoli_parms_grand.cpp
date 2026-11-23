#include <string.h>

#include "idcoli/idcoli.h"
#include "types.h"

namespace mm {
struct Mat44;
} // namespace mm

namespace idcoli {

const char *IDColiPartsMoveGrand::getName() const { return m_moveObj->m_name; }

void IDColiPartsMoveGrand::setMatrix(const mm::Mat44 &matrix) { m_moveObj->setMat(matrix); }

void IDColiPartsMoveGrand::setUserData(void *userData) { m_moveObj->m_userData = userData; }

void *IDColiPartsMoveGrand::getUserData() { return m_moveObj->m_userData; }

u16 IDColiPartsMoveGrand::getID() const { return m_moveObj->m_iDCmfPosInfo.m_iD; }

IDColiParmsGrand::IDColiParmsGrand(IDColiObj *object) : m_work(&static_cast<IDColiObjGrand *>(object)->m_iDColiGrandWork) {}

int IDColiParmsGrand::getMoveMax() const { return m_work->m_moveMax; }

IDColiPartsMoveGrand IDColiParmsGrand::getMoveObj(u32 index) { return IDColiPartsMoveGrand(&m_work->m_moveObj[index]); }

int IDColiParmsGrand::getMoveObjIdx(const char *name) {
  for (int i = 0; i < m_work->m_moveMax; i++) {
    if (strcmp(m_work->m_moveObj[i].m_name, name) == 0) {
      return i;
    }
  }

  return -1;
}

} // namespace idcoli
