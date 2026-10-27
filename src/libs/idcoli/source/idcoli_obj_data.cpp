#include <string.h>

#include "idcoli/idcoli.h"
#include "mm_math/mm_mat44.h"

namespace idcoli {

const char *IDColiObjData::getBoneName(int index) const { return reinterpret_cast<const char *>(unknown1d0) + unknown1d8[index].unknown40; }

int IDColiObjData::getBoneIdx(const char *name) const {
  for (int i = 0; i < unknown1f8; i++) {
    if (strcmp(name, getBoneName(i)) == 0) {
      return i;
    }
  }

  return -1;
}

void IDColiObjData::setBoneMatrix(int index, const mm::Mat44 &matrix) { unknown1f0[index] = matrix; }

mm::Mat44 &IDColiObjData::getBoneMatrix(int index) { return unknown1f0[index]; }

} // namespace idcoli
