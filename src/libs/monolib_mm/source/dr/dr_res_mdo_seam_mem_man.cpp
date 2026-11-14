#include "dr/dr_res_mdo_seam_mem_man.h"

#include <string.h>

#include "dr/dr_res_mdo_seam_res.h"
#include "mtl/mem_manager.h"

namespace ml {

DrResMdoSeamMemMan::DrResMdoSeamMemMan() : unknown24(0), unknown28(0), unknown2c(0), unknown30(0), unknown38(nullptr) {
  unknown00.unknown00 = nullptr;
  unknown00.unknown08 = nullptr;
  unknown10.unknown00 = nullptr;
  unknown10.unknown08 = nullptr;
}

DrResMdoSeamMemMan::~DrResMdoSeamMemMan() { releaseMem(); }

void DrResMdoSeamMemMan::releaseMem() {
  for (u32 i = 0; i < unknown30; i++) {
    unknown38[i].~DrResMdoSeamMemObj();
  }
  unknown30 = 0;
  if (unknown38 != nullptr) {
    mtl::MemManager::deallocate(unknown38, 0, false);
    unknown38 = nullptr;
  }
  unknown2c = 0;
  unknown10.unknown00 = nullptr;
  unknown10.unknown08 = nullptr;
  unknown00.unknown00 = nullptr;
  unknown00.unknown08 = nullptr;
}

void DrResMdoSeamMemMan::cntMemUpdate() {
  if (unknown440 == 0) {
    for (int i = 0; i < unknown444; i++) {
      if (unknown240[i] != nullptr) {
        unknown240[i]->unknown24 &= ~2;
      }
    }
  }
  if (unknown440++ > 0) {
    for (int i = 0; i < unknown444; i++) {
      if (unknown40[i] != nullptr) {
        clearMemObj(unknown40[i], unknown00);
        unknown40[i] = nullptr;
      }
    }
    unknown440 = 0;
    unknown444 = 0;
    unknown2c &= ~2;
  }
}

bool DrResMdoSeamMemMan::memTempCopy() {
  bool isEmpty = true;
  for (int i = 0; i < unknown444; i++) {
    unknown40[i] = copyTempBuff(unknown240[i]);
    if (unknown40[i] != nullptr) {
      isEmpty = false;
      unknown2c |= 2;
    }
  }
  return isEmpty;
}

DrResMdoSeamMemObj *DrResMdoSeamMemMan::copyMemObj(DrResMdoSeamMemObj *obj, DrResChankList<DrResMdoSeamMemObj> &list) {
  DrResMdoSeamMemObj *copy = createBackFreeObj(obj->m_size, list, 0);
  if (copy == nullptr) {
    return nullptr;
  }
  changeListAndCopyMemObj(copy, obj, list);
  return copy;
}

void DrResMdoSeamMemMan::changeListAndCopyMemObj(DrResMdoSeamMemObj *first, DrResMdoSeamMemObj *second, DrResChankList<DrResMdoSeamMemObj> &list) {
  memcpy(first->m_buffer, second->m_buffer, second->m_size);
  u8 *buffer = first->m_buffer;
  first->m_buffer = second->m_buffer;
  second->m_buffer = buffer;
  u32 size = first->m_size;
  first->m_size = second->m_size;
  second->m_size = size;
  list.changeList(first, second);
}

int DrResMdoSeamMemMan::getUseMax() const {
  const DrResMdoSeamMemObj *obj = unknown00.unknown00;
  if (obj != nullptr) {
    int count = 0;
    do {
      count += obj->unknown24 & 1;
      obj = obj->unknown10;
    } while (obj != nullptr);
    return count;
  }
  return 0;
}

int DrResMdoSeamMemMan::getFreeMax() const {
  const DrResMdoSeamMemObj *obj = unknown00.unknown00;
  if (obj != nullptr) {
    int count = 0;
    do {
      count += ~obj->unknown24 & 1;
      obj = obj->unknown10;
    } while (obj != nullptr);
    return count;
  }
  return 0;
}

int DrResMdoSeamMemMan::getAllFreeSize() const {
  const DrResMdoSeamMemObj *obj = unknown00.unknown00;
  if (obj != nullptr) {
    int size = 0;
    do {
      if ((obj->unknown24 & 1) == 0) {
        size += obj->m_size;
      }
      obj = obj->unknown10;
    } while (obj != nullptr);
    return size;
  }
  return 0;
}

int DrResMdoSeamMemMan::getAllUseSize() const {
  const DrResMdoSeamMemObj *obj = unknown00.unknown00;
  if (obj != nullptr) {
    int size = 0;
    do {
      if ((obj->unknown24 & 1) != 0) {
        size += obj->m_size;
      }
      obj = obj->unknown10;
    } while (obj != nullptr);
    return size;
  }
  return 0;
}

u32 DrResMdoSeamMemMan::getFreeSize() {
  const DrResMdoSeamMemObj *obj = unknown00.unknown00;
  if (obj == nullptr) {
    return 0;
  }
  u32 maxSize = 0;
  do {
    if ((obj->unknown24 & 1) == 0 && obj->m_size > maxSize) {
      maxSize = obj->m_size;
    }
    obj = obj->unknown10;
  } while (obj != nullptr);
  return maxSize;
}

u32 DrResMdoSeamMemMan::getFreeSize(int &freeCount, int &separatedCount) {
  separatedCount = 0;
  freeCount = 0;
  const DrResMdoSeamMemObj *obj = unknown00.unknown00;
  u32 maxSize = 0;
  if (obj != nullptr) {
    int previous = -1;
    do {
      if ((obj->unknown24 & 1) == 0) {
        freeCount++;
        if (obj->m_size > maxSize) {
          maxSize = obj->m_size;
        }
        if (previous == 1) {
          separatedCount++;
        }
        previous = 0;
      } else {
        previous = 1;
      }
      obj = obj->unknown10;
    } while (obj != nullptr);
  }
  return maxSize;
}

void DrResMdoSeamMemMan::renderMemInfo() {}

bool DrResMdoSeamMemMan::calcPieceMem(bool isCheck) {
  const DrResMdoSeamMemObj *obj = unknown00.unknown00;
  if (obj != nullptr) {
    bool isUse = false;
    int pieceCount = 0;
    do {
      if ((obj->unknown24 & 1) == 0) {
        pieceCount += isUse;
      }
      if ((obj->unknown24 & 1) != 0) {
        isUse = true;
      }
      obj = obj->unknown10;
    } while (obj != nullptr);
    return pieceCount > 19;
  }
  return false;
}

DrResMdoSeamMemObj *DrResMdoSeamMemMan::createFreeObj(u32 size) {
  for (DrResMdoSeamMemObj *obj = unknown00.unknown00; obj != nullptr; obj = obj->unknown10) {
    if ((obj->unknown24 & 1) == 0 && obj->m_size >= size) {
      return unknown001(obj, size, unknown00);
    }
  }
  return nullptr;
}

DrResMdoSeamMemObj *DrResMdoSeamMemMan::createFreeObj(u32 size, DrResChankList<DrResMdoSeamMemObj> &list, int index) {
  for (DrResMdoSeamMemObj *obj = list.unknown00; obj != nullptr; obj = obj->unknown10) {
    if ((obj->unknown24 & 1) == 0 && obj->m_size >= size) {
      return unknown001(obj, size, list);
    }
  }
  return nullptr;
}

DrResMdoSeamMemObj *DrResMdoSeamMemMan::createBackFreeObj(u32 size) {
  for (DrResMdoSeamMemObj *obj = unknown00.unknown08; obj != nullptr; obj = obj->unknown08) {
    if ((obj->unknown24 & 1) == 0 && obj->m_size >= size) {
      return unknown002(obj, size, unknown00);
    }
  }
  return nullptr;
}

DrResMdoSeamMemObj *DrResMdoSeamMemMan::createBackFreeObj(u32 size, DrResChankList<DrResMdoSeamMemObj> &list, int index) {
  for (DrResMdoSeamMemObj *obj = list.unknown08; obj != nullptr; obj = obj->unknown08) {
    if ((obj->unknown24 & 1) == 0 && obj->m_size >= size) {
      return unknown002(obj, size, list);
    }
  }
  return nullptr;
}

DrResMdoSeamMemObj *DrResMdoSeamMemMan::createTopFreeObj(u32 size, DrResChankList<DrResMdoSeamMemObj> &list, int index) {
  for (DrResMdoSeamMemObj *obj = list.unknown00; obj != nullptr; obj = obj->unknown10) {
    if ((obj->unknown24 & 1) == 0) {
      if (obj->m_size < size) {
        return nullptr;
      }
      return unknown001(obj, size, list);
    }
  }
  return nullptr;
}

DrResMdoSeamMemObj *DrResMdoSeamMemMan::createParentFreeObj(DrResMdoSeamMemObj *parent, u32 size) {
  if (parent->m_size < size) {
    return nullptr;
  }
  DrResMdoSeamMemObj *child = unknown10.unknown00;
  if (child == nullptr) {
    return nullptr;
  }
  unknown10.unknown001(child);
  u32 parentSize = parent->m_size;
  parent->m_size = size;
  child->m_size = parentSize - size;
  child->m_buffer = parent->m_buffer + size;
  child->unknown24 = 1;
  unknown00.unknown003(parent, child);
  return child;
}

void DrResMdoSeamMemMan::releaseFreeObj(DrResMdoSeamMemObj *obj) {
  clearMemObj(obj, unknown00);
  if (unknown2c & 2) {
    for (int i = 0; i < unknown444; i++) {
      if (unknown240[i] == obj) {
        unknown240[i] = nullptr;
      }
    }
  }
}

void DrResMdoSeamMemMan::releaseTempFreeObj(DrResMdoSeamMemObj *obj) { clearMemObj(obj, unknown00); }

} // namespace ml
