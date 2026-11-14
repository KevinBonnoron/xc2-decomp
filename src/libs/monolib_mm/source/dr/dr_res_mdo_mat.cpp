#include "dr/dr_res_mdo_mat.h"

#include <math.h>
#include <string.h>

#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_man.h"
#include "dr/dr_mdo_mat.h"
#include "dr/dr_res_mdo_mesh_obj.h"
#include "grlib/cglib_tri_uniform_block.h"
#include "grlib/cglib_uniform_array.h"
#include "grlib/shd_util.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"

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
  if (unknown28 & FLAG_UNKNOWN_27) {
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
  if (unknown28 & FLAG_UNKNOWN_27) {
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

void DrResMdoMeshObj::updateUniforom(grlib::CGLibTriUniformArray *uniforms, bool isOld) {
  mm::Mat44 viewMat;
  mm::Mat44 viewProj;
  f32 params[4] = {0.0f, 0.0f, 0.0f, 0.0f};
  DrCalcViewWork *view = DrMan::get()->unknown580->unknown10;
  for (u32 i = 0; i < unknown08; i++) {
    DrResMdoMeshParts *parts = &unknown00[i];
    if ((parts->unknown28 & (DrResMdoMeshParts::FLAG_UNKNOWN_0 | 8)) == DrResMdoMeshParts::FLAG_UNKNOWN_0 && 0.0f < parts->unknown34) {
      grlib::CGLibTriUniformBlock *block = &(*uniforms)[parts->unknown38];
      f32 *buff = static_cast<f32 *>(block->getBuff());
      viewProj.unknown009(*parts->unknown10, view->unknown200);
      viewMat.unknown009(*parts->unknown10, view->unknown40);
      grlib::ShdMat44TransposeMat44(buff, viewProj);
      grlib::ShdMat44TransposeMat34(buff + 0x10, *parts->unknown10);
      grlib::ShdMat44TransposeMat34(buff + 0x1c, viewMat);
      params[0] = parts->unknown28 & 8 ? 0.0f : parts->unknown34;
      const mm::Mat44 &matrix = *parts->unknown10;
      mm::Vec3 axis(matrix.rows[0][0] + matrix.rows[1][0] + matrix.rows[2][0], matrix.rows[0][1] + matrix.rows[1][1] + matrix.rows[2][1], matrix.rows[0][2] + matrix.rows[1][2] + matrix.rows[2][2]);
      params[1] = sqrtf(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z) * DrMdoMat::MDL_SCALE_PARAMS;
      grlib::ShdF32SetVec4(buff + 0x28, params);
      block->updateData();
      if (isOld) {
        buff = static_cast<f32 *>(block->getOldBuff());
        grlib::ShdMat44TransposeMat44(buff, viewProj);
        grlib::ShdMat44TransposeMat34(buff + 0x10, *parts->unknown10);
        grlib::ShdMat44TransposeMat34(buff + 0x1c, viewMat);
        grlib::ShdF32SetVec4(buff + 0x28, params);
        block->updateOldData();
      }
    }
  }
}

bool DrResMdoMeshObj::updateDisplayCheck(bool isDisp) {
  bool isChange = false;
  for (u32 i = 0; i < unknown08; i++) {
    DrResMdoMeshParts *parts = &unknown00[i];
    if (parts->unknown28 & 0x100) {
      parts->unknown28 &= ~0x100;
      parts->unknown28 |= 1;
      isChange = true;
    }
    if (parts->unknown28 & 0x200) {
      parts->unknown28 &= ~0x200;
      parts->unknown28 &= ~1;
      isChange = true;
    }
    if (getParts(i)->unknown28 & 0x10) {
      if (isDisp) {
        getParts(i)->unknown28 |= 8;
      } else {
        getParts(i)->unknown28 &= ~8;
      }
    }
    parts->updateAlpha();
    f32 alpha = parts->unknown28 & 8 ? 0.0f : parts->unknown34;
    if (alpha <= 0.02f) {
      if (parts->unknown28 & 0x8000) {
        parts->unknown28 &= ~0x8000;
        isChange = true;
      }
    } else if (!(parts->unknown28 & 0x8000)) {
      parts->unknown28 |= 0x8000;
      isChange = true;
    }
    if (alpha < 0.98f) {
      if (parts->unknown28 & 0x10000) {
        parts->unknown28 &= ~0x10000;
        isChange = true;
      }
    } else if (!(parts->unknown28 & 0x10000)) {
      parts->unknown28 |= 0x10000;
      isChange = true;
    }
  }
  return isChange;
}

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
