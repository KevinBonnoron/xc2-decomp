#include <string.h>

#include "idcoli/idcoli.h"
#include "types.h"

namespace mm {
struct Mat44;
} // namespace mm

namespace idcoli {

const char *IDColiPartsMoveGrand::getName() const { return m_moveObj->unknown1b0; }

void IDColiPartsMoveGrand::setMatrix(const mm::Mat44 &matrix) { m_moveObj->setMat(matrix); }

void IDColiPartsMoveGrand::setUserData(void *userData) { m_moveObj->unknown1b8 = userData; }

void *IDColiPartsMoveGrand::getUserData() { return m_moveObj->unknown1b8; }

u16 IDColiPartsMoveGrand::getID() const { return m_moveObj->unknown1a2; }

IDColiParmsGrand::IDColiParmsGrand(IDColiObj *object) : m_work(&static_cast<IDColiObjGrand *>(object)->unknown50) {}

int IDColiParmsGrand::getMoveMax() const { return m_work->unknown78; }

IDColiPartsMoveGrand IDColiParmsGrand::getMoveObj(u32 index) { return IDColiPartsMoveGrand(&m_work->unknown70[index]); }

int IDColiParmsGrand::getMoveObjIdx(const char *name) {
  for (int i = 0; i < m_work->unknown78; i++) {
    if (strcmp(m_work->unknown70[i].unknown1b0, name) == 0) {
      return i;
    }
  }

  return -1;
}

} // namespace idcoli
