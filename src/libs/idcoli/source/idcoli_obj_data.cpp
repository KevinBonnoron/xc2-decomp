#include <string.h>

#include "idcoli/idcoli.h"
#include "idcoli/idcoli_util_coli.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"
#include "types.h"

namespace idcoli {

bool IDColiObjData::createBinary(const void *binary) {
  workNodeClear();

  const unknown002 *header = static_cast<const unknown002 *>(binary);
  if (header->unknown00 != 0x4c434843 || header->unknown04 != 0x2712) {
    return false;
  }

  unknown1d0 = header;
  const unknown022 *info = reinterpret_cast<const unknown022 *>(static_cast<const u8 *>(binary) + header->unknown0c);
  unknown1f8 = info->unknown0c;
  unknown1fc = info->unknown04;
  u32 size = info->unknown0c * 0x40;
  if (!(header->unknown08 & 1)) {
    unknown1c |= 0x100;
    size += info->unknown04 * 0xc0;
  } else {
    unknown1c &= ~0x100;
  }
  if (header->unknown08 & 2) {
    unknown1c |= 0x200;
  } else {
    unknown1c &= ~0x200;
  }

  if (size != 0) {
    unknown1e0 = mtl::MemManager::allocate(IDColiManager::get()->unknownf4, size, 0x10, false, "no name", 0);
  }
  u32 offset = 0;
  if (info->unknown0c != 0) {
    unknown1f0 = static_cast<mm::Mat44 *>(unknown1e0);
    offset = info->unknown0c * 0x40;
  }
  if (!(header->unknown08 & 1)) {
    unknown1e8 = reinterpret_cast<unknown008 *>(static_cast<u8 *>(unknown1e0) + offset);
  }

  const unknown001 *bone = reinterpret_cast<const unknown001 *>(reinterpret_cast<const u8 *>(unknown1d0) + info->unknown08);
  unknown1d8 = bone;
  for (int i = 0; i < unknown1f8; i++, bone++) {
    mm::Mat44 &matrix = unknown1f0[i];
    for (int row = 0; row < 4; row++) {
      for (int column = 0; column < 4; column++) {
        matrix.rows[row][column] = bone->unknown00[row][column];
      }
    }
  }

  if (!(header->unknown08 & 1)) {
    const CHCLBaseInfo *primInfo = reinterpret_cast<const CHCLBaseInfo *>(reinterpret_cast<const u8 *>(unknown1d0) + info->unknown00 + info->unknown04 * sizeof(CHCLBaseData));
    unknownc0 = s_TypePrimiteve[primInfo->unknown00];
  }

  if (header->unknown08 & 2) {
    unknown200 = static_cast<IDColiObjGrdChar *>(IDColiManager::get()->createColiGrdChar());
    unknown200->createWorkBuffer(reinterpret_cast<const u8 *>(unknown1d0), this);
    if (info->unknown04 > 0) {
      const CHCLBaseInfo *primInfo = reinterpret_cast<const CHCLBaseInfo *>(reinterpret_cast<const u8 *>(unknown1d0) + info->unknown00 + info->unknown04 * sizeof(CHCLBaseData));
      u32 index = 0;
      for (int i = 0; i < info->unknown04; i++) {
        if (primInfo[i].unknown00 == 5) {
          unknown1e8[i].unknown00 = &unknown200->unknown80[index];
          index++;
        }
      }
    }
  }

  unknown1c &= ~0x800;
  primUpdate();
  unknown1c |= 0x800;
  return true;
}

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

void IDColiObjData::primset_sphere(void *work, IDColiBaseType &type, const CHCLBaseData *data, const CHCLBaseInfo *info) {
  mm::Mat44 matrix;
  calcNodeMatrix(matrix, unknown70, data, info);
  CLSphereWork *sphere = static_cast<CLSphereWork *>(work);
  f32 radius = unknown123(matrix) * IDColiObj::OBJ_CALC_RADIUS;
  sphere->unknown10 = data->unknown00.x * radius;
  sphere->unknown00 = matrix.unknown004();
  type = IDColiBaseType_UNKNOWN_0;
}

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

void IDColiObjData::primset_bone_capsule(void *work, IDColiBaseType &type, const CHCLBaseData *data, const CHCLBaseInfo *info) {
  mm::Mat44 matrix;
  calcNodeMatrix(matrix, unknown70, data, info);
  mm::Mat44 link;
  calcLinkNodeMatrix(link, info);
  CLCapsuleWork *capsule = static_cast<CLCapsuleWork *>(work);
  capsule->unknown00 = matrix.unknown004();
  capsule->unknown10 = link.unknown004();
  f32 radius = unknown123(matrix) * IDColiObj::OBJ_CALC_RADIUS;
  mm::Vec3 axis = capsule->unknown00 - capsule->unknown10;
  if (axis.x * axis.x + axis.y * axis.y + axis.z * axis.z <= 0.001f) {
    CLSphereWork *sphere = static_cast<CLSphereWork *>(work);
    sphere->unknown10 = data->unknown00.x * radius;
    sphere->unknown00 = matrix.unknown004();
    type = IDColiBaseType_UNKNOWN_0;
  } else {
    capsule->unknown50 = data->unknown00.x * radius;
    IDColiPrimitive::calcCapsuleSetup(capsule);
    type = IDColiBaseType_UNKNOWN_2;
  }
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
