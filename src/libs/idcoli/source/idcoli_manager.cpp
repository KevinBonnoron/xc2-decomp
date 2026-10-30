#include <stddef.h>
#include <string.h>

#include "idcoli/idcoli.h"
#include "idcoli/idcoli_mem_handle_allocator.h"
#include "ml/critical_section.h"
#include "mm_math/mm_vec3.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"
#include "types.h"

namespace ml {
class WinProc;
class Scn;
} // namespace ml

namespace idcoli {

bool IDColiManager::getGrandAABB(mm::Vec3 &max, mm::Vec3 &min) const {
  max = mm::Vec3(-10000.0f, -10000.0f, -10000.0f);
  min = mm::Vec3(10000.0f, 10000.0f, 10000.0f);
  IDColiObj *object = unknown08[0].m_head;
  if (object != nullptr) {
    for (; object != nullptr; object = object->unknown10) {
      static_cast<IDColiObjGrand *>(object)->getGrandAABB(max, min);
    }

    return true;
  }

  max = mm::Vec3(100.0f, 100.0f, 100.0f);
  min = mm::Vec3(-100.0f, -100.0f, -100.0f);
  return false;
}

ml::CriticalSection &IDColiManager::getCriticalSection() {
  static ml::CriticalSection sect;
  return sect;
}

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

IDColiManager::IDColiManager(ml::Scn *scn, mtl::ALLOC_HANDLE handle, u32 size) {
  unknownf4 = mtl::ALLOC_HANDLE();
  unknownf4 = mtl::MemManager::create(handle, size, "Collision", false);
  m_allocator.setMemHandle(unknownf4);
  memset(unknown08, 0, sizeof(unknown08) + sizeof(unknown48) + sizeof(_c8));
  s_nDebIdx = 0;
  s_nStkIdx = 1;
  unknownf0 = 0;
  unknownd8[0] = nullptr;
  unknownd8[1] = nullptr;
  unknownd8[0] = new (unknownf4) IDColiTreeTop();
  unknownd8[1] = new (unknownf4) IDColiTreeTop();
  m_gblIdTbl = static_cast<u32 *>(mtl::MemManager::allocate(unknownf4, 0x400, 0x20, false, "no name", 0));
  memset(m_gblIdTbl, 0, 0x400);
}

IDColiManager::~IDColiManager() {
  release();
  if (m_gblIdTbl != nullptr) {
    mtl::MemManager::deallocate(m_gblIdTbl, 0, false);
    m_gblIdTbl = nullptr;
  }
  if (unknownd8[0] != nullptr) {
    delete unknownd8[0];
    unknownd8[0] = nullptr;
  }
  if (unknownd8[1] != nullptr) {
    delete unknownd8[1];
    unknownd8[1] = nullptr;
  }
  if (unknownf4.isValid()) {
    mtl::MemManager::erase(unknownf4);
    unknownf4 = mtl::ALLOC_HANDLE();
  }
}

void IDColiManager::release() {
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 4; j++) {
      IDColiObj *object = unknown48[j][i].m_head;
      while (object != nullptr) {
        IDColiObj *next = object->unknown10;
        delete object;
        object = next;
      }
      unknown48[j][i].m_head = nullptr;
      unknown48[j][i].m_tail = nullptr;
    }
  }

  for (int i = 0; i < 4; i++) {
    IDColiObj *object = unknown08[i].m_head;
    while (object != nullptr) {
      IDColiObj *next = object->unknown10;
      delete object;
      object = next;
    }
    unknown08[i].m_head = nullptr;
    unknown08[i].m_tail = nullptr;
  }
}

void IDColiManager::update() {
  addDelUpdate();
  for (int i = 0; i < 4; i++) {
    updateList(unknown08[i]);
  }
}

void IDColiManager::objUpdate() {
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

IDColiObj *IDColiManager::createColiGrand(const void *binary) {
  ml::CS cs(getCriticalSection());
  IDColiObjGrand *object = new (unknownf4) IDColiObjGrand();
  object->createGrand(unknownf4, binary);
  unknown48[0][s_nStkIdx].unknown001(object);
  return object;
}

IDColiObj *IDColiManager::createColiCharacter() {
  ml::CS cs(getCriticalSection());
  IDColiObjCharCheck *object = new (unknownf4) IDColiObjCharCheck(unknownd8[0]);
  unknown48[1][s_nStkIdx].unknown001(object);
  return object;
}

IDColiObj *IDColiManager::createColiPhantom() {
  ml::CS cs(getCriticalSection());
  IDColiObjPhantomCheck *object = new (unknownf4) IDColiObjPhantomCheck(unknownd8[1]);
  unknown48[2][s_nStkIdx].unknown001(object);
  return object;
}

IDColiObj *IDColiManager::createColiGrdChar() {
  ml::CS cs(getCriticalSection());
  IDColiObjGrdChar *object = new (unknownf4) IDColiObjGrdChar();
  unknown48[3][s_nStkIdx].unknown001(object);
  return object;
}

void IDColiManager::addList(ColiLinkList<IDColiObj> &list, ColiLinkList<IDColiObj> &source, bool isSweep) {
  IDColiObj *object = source.m_head;
  while (object != nullptr) {
    IDColiObj *prev = object->unknown08;
    IDColiObj *next = object->unknown10;
    if (prev == nullptr) {
      if (next == nullptr) {
        source.m_head = nullptr;
        source.m_tail = nullptr;
      } else {
        source.m_head = next;
        next->unknown08 = nullptr;
      }
    } else if (next == nullptr) {
      source.m_tail = prev;
      prev->unknown10 = nullptr;
    } else {
      prev->unknown10 = next;
      object->unknown10->unknown08 = object->unknown08;
    }
    object->unknown08 = nullptr;
    object->unknown10 = nullptr;

    if (isSweep) {
      static_cast<IDColiObjBase *>(object)->sweepPush(static_cast<IDColiObjBase *>(getUseObject(list)));
    }

    if (list.m_tail == nullptr) {
      list.m_head = object;
      list.m_tail = object;
      object->unknown08 = nullptr;
    } else {
      list.m_tail->unknown10 = object;
      object->unknown08 = list.m_tail;
      list.m_tail = object;
    }
    object->unknown10 = nullptr;
    object = next;
  }

  source.m_head = nullptr;
  source.m_tail = nullptr;
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
