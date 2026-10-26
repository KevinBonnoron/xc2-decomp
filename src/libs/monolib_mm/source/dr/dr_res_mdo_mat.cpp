#include "dr/dr_res_mdo_mat.h"

#include <string.h>

#include "dr/dr_man.h"
#include "dr/dr_res_mdo_mesh_obj.h"
#include "mm_math/mm_mat44.h"

namespace ml {

void DrResMdoMeshParts::setResetAlpha(f32 alpha) {
  unknown28 &= ~6;
  unknown34 = alpha;
  unknown2c[1] = alpha;
  unknown2c[0] = alpha;
}

DrResMdoMat &DrResMdoMat::operator=(const DrResMdoMat &other) {
  unknown08 = other.unknown08;
  unknown18 = other.unknown18;
  unknown1c = other.unknown1c;
  return *this;
}

void DrResMdoMat::setColor(f32 r, f32 g, f32 b, f32 a) {
  unknown08.r = r;
  unknown08.g = g;
  unknown08.b = b;
  unknown08.a = a;
}

void DrResMdoMat::setAlpha(f32 alpha) { unknown08.a = alpha; }

void DrResMdoMat::setName(const char *name) { m_name = name; }

DrResMdoMeshParts::DrResMdoMeshParts() : unknown28(0) {}

DrResMdoMeshParts::~DrResMdoMeshParts() {}

DrResMdoMeshParts &DrResMdoMeshParts::operator=(const DrResMdoMeshParts &other) {
  if (unknown28 & FLAG_MAT_ADD) {
    memcpy(unknown10, other.unknown10, sizeof(mm::Mat44));
  }
  unknown2c[0] = other.unknown2c[0];
  unknown2c[1] = other.unknown2c[1];
  unknown34 = other.unknown34;
  unknown28 = other.unknown28;
  unknown3a = other.unknown3a;
  return *this;
}

void DrResMdoMeshParts::setName(const char *name) { m_name = name; }

void DrResMdoMeshParts::setBoneName(const char *name) { m_boneName = name; }

void DrResMdoMeshParts::setMatAdd(mm::Mat44 *matrix, const mm::Mat44 *baseMat, const mm::Mat44 *ofsMat, int index) {
  unknown10 = matrix;
  unknown18 = baseMat;
  unknown20 = const_cast<mm::Mat44 *>(ofsMat);
  memcpy(matrix, baseMat, sizeof(mm::Mat44));
  unknown38 = index;
}

void DrResMdoMeshParts::setRegisterMatrix(int index, bool isRegister) {
  if (unknown28 & FLAG_MAT_ADD) {
    if (isRegister) {
      if (unknown28 & 1) {
        unknown28 &= ~0x100;
      } else {
        unknown28 |= 0x100;
      }
    } else if (unknown28 & 1) {
      unknown28 |= 0x200;
    } else {
      unknown28 &= ~0x200;
    }
  }
}

void DrResMdoMeshParts::setDefAlpha(f32 alpha) {
  int index = DrMan::s_nDblStockIdx;
  unknown2c[index] = alpha;
  unknown28 |= 2 << index;
  unknown2c[DrMan::s_nDblIdx] = alpha;
}

f32 DrResMdoMeshParts::getDefAlpha() const {
  int index = DrMan::s_nDblStockIdx;
  u32 bit = 2 << index;
  if (unknown28 & bit) {
    return unknown2c[index];
  }
  index = DrMan::s_nDblIdx;
  bit = 2 << index;
  if (unknown28 & bit) {
    return unknown2c[index];
  }
  return unknown34;
}

void DrResMdoMeshParts::updateAlpha() {
  int index = DrMan::s_nDblIdx;
  u32 bit = 2 << index;
  if (unknown28 & bit) {
    unknown28 &= ~bit;
    unknown34 = unknown2c[index];
  }
}

DrResMdoMeshObj::DrResMdoMeshObj() : unknown00(nullptr), unknown08(0) {}

DrResMdoMeshObj::~DrResMdoMeshObj() {}

int DrResMdoMeshObj::getIdx(const char *name) const {
  int index = -1;
  u32 num = unknown08;
  if (num != 0) {
    const DrResMdoMeshParts *parts = unknown00;
    for (u32 i = 0; i < num; i++, parts++) {
      if (strcmp(parts->m_name, name) == 0) {
        index = i;
        break;
      }
    }
  }
  return index;
}

void DrResMdoMeshObj::release(DrResMdoMeshObj *&meshObj) {
  if (meshObj != nullptr) {
    meshObj = nullptr;
  }
}

DrResMdoMeshObj &DrResMdoMeshObj::operator=(const DrResMdoMeshObj &other) {
  for (u32 i = 0; i < unknown08; i++) {
    unknown00[i] = other.unknown00[i];
  }
  return *this;
}

} // namespace ml
