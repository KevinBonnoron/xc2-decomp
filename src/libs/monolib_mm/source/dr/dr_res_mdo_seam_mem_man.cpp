#include "dr/dr_res_mdo_seam_mem_man.h"

#include "dr/dr_res_mdo_seam_res.h"

namespace ml {

int DrResMdoSeamMemMan::getUseMax() const {
  const DrResMdoSeamMemObj *obj = unknown00;
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
  const DrResMdoSeamMemObj *obj = unknown00;
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
  const DrResMdoSeamMemObj *obj = unknown00;
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
  const DrResMdoSeamMemObj *obj = unknown00;
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
  const DrResMdoSeamMemObj *obj = unknown00;
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
  const DrResMdoSeamMemObj *obj = unknown00;
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

} // namespace ml
