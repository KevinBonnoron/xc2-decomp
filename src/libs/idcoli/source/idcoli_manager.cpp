#include <stddef.h>

#include "idcoli/idcoli.h"
#include "idcoli/idcoli_mem_handle_allocator.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"
#include "types.h"

namespace ml {
class WinProc;
} // namespace ml

namespace idcoli {

IDColiMemHandleAllocator::IDColiMemHandleAllocator() {}

IDColiMemHandleAllocator::IDColiMemHandleAllocator(mtl::ALLOC_HANDLE handle) : unknown08(handle) {}

void IDColiMemHandleAllocator::setMemHandle(mtl::ALLOC_HANDLE handle) { unknown08 = handle; }

mtl::ALLOC_HANDLE IDColiMemHandleAllocator::getMemHandle() const { return unknown08; }

void *IDColiMemHandleAllocator::allocate(size_t size, size_t alignment) { return mtl::MemManager::allocate(unknown08, size, alignment, false, "no name", 0); }

void IDColiMemHandleAllocator::deallocate(void *pointer) {
  if (pointer != nullptr) {
    mtl::MemManager::deallocate(pointer, 0, false);
  }
}

void IDColiManager::update() {
  addDelUpdate();
  for (int i = 0; i < 4; i++) {
    updateList(unknown08[i]);
  }
}

void IDColiManager::consistentUpdate() {
  unknownd8[0]->begin();
  unknownd8[1]->begin();
  updateConsistentList(unknown08[1]);
  updateConsistentList(unknown08[2]);
  unknownd8[0]->end();
  unknownd8[1]->end();
}

void IDColiManager::tail() {
  s_nDebIdx = s_nDebIdx == 0;
  s_nStkIdx = s_nDebIdx == 0;
}

IDColiObj *IDColiManager::getUseObject(ColiLinkList<IDColiObj> &list) {
  for (IDColiObj *object = list.m_head; object != nullptr; object = object->unknown10) {
    if (!object->isDeleteCall() && !(object->unknown18 & 4) && !(object->unknown1c & 0x80)) {
      return object;
    }
  }

  return nullptr;
}

bool IDColiObj::isDeleteCall() const { return (unknown1c & (1 << IDColiManager::s_nDebIdx)) != 0; }

void IDColiManager::updateList(ColiLinkList<IDColiObj> &list) {
  for (IDColiObj *object = list.m_head; object != nullptr; object = object->unknown10) {
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
