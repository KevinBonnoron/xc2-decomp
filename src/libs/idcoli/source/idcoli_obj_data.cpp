#include <string.h>

#include "idcoli/idcoli.h"
#include "mm_math/mm_mat44.h"

namespace idcoli {
struct CHCLBaseInfo;

bool IDColiObjData::nodeUpdate() {
  if (unknown1fc != 0) {
    primUpdate();
    return true;
  }
  return false;
}

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

void IDColiObjData::primset_base(void *work, IDColiBaseType &type, const CHCLBaseData *data, const CHCLBaseInfo *info) {
  mm::Mat44 matrix;
  calcNodeMatrix(matrix, unknown70, data, info);
  IDColiPrimitive::createBaseCharacter(work, type, matrix, data->unknown00);
}

void IDColiObjData::primset_capsule(void *work, IDColiBaseType &type, const CHCLBaseData *data, const CHCLBaseInfo *info) {
  mm::Mat44 matrix;
  calcNodeMatrix(matrix, unknown70, data, info);
  IDColiPrimitive::createBaseCapsule(work, type, matrix, data->unknown00);
}

void IDColiObjData::primset_box(void *work, IDColiBaseType &type, const CHCLBaseData *data, const CHCLBaseInfo *info) {
  mm::Mat44 matrix;
  calcNodeMatrix(matrix, unknown70, data, info);
  IDColiPrimitive::createBaseBox(work, type, matrix, data->unknown00);
}

void IDColiObjData::primset_poli(void *work, IDColiBaseType &type, const CHCLBaseData *data, const CHCLBaseInfo *info) {
  mm::Mat44 matrix;
  calcNodeMatrix(matrix, unknown70, data, info);
  IDColiPrimitive::createBasePoli(work, type, matrix, data->unknown00);
}

void IDColiObjData::primset_subbase(void *work, IDColiBaseType &type, const CHCLBaseData *data, const CHCLBaseInfo *info) {
  mm::Mat44 matrix;
  calcNodeMatrix(matrix, unknown70, data, info);
  IDColiPrimitive::createSubBaseCharacter(work, type, matrix, data->unknown00, (unknown1c & (1 << 11)) == 0);
}

} // namespace idcoli
