#include "dr/dr_res_mdo_mat.h"

#include <string.h>

#include "dr/dr_man.h"
#include "dr/dr_res_mdo_mesh_obj.h"
#include "mm_math/mm_mat44.h"

namespace ml {

DrResMdoMat &DrResMdoMat::operator=(const DrResMdoMat &other) {
  m_color = other.m_color;
  m_param0 = other.m_param0;
  m_param1 = other.m_param1;
  return *this;
}

void DrResMdoMat::setColor(f32 r, f32 g, f32 b, f32 a) {
  m_color.r = r;
  m_color.g = g;
  m_color.b = b;
  m_color.a = a;
}

void DrResMdoMat::setAlpha(f32 alpha) { m_color.a = alpha; }

void DrResMdoMat::setName(const char *name) { m_name = name; }

DrResMdoMeshParts::DrResMdoMeshParts() : m_flags(0) {}

DrResMdoMeshParts::~DrResMdoMeshParts() {}

DrResMdoMeshParts &DrResMdoMeshParts::operator=(const DrResMdoMeshParts &other) {
  if (m_flags & FLAG_MAT_ADD) {
    memcpy(m_matrix, other.m_matrix, sizeof(mm::Mat44));
  }
  m_defAlphas[0] = other.m_defAlphas[0];
  m_defAlphas[1] = other.m_defAlphas[1];
  m_alpha = other.m_alpha;
  m_flags = other.m_flags;
  m_volumeFadeEffect = other.m_volumeFadeEffect;
  return *this;
}

void DrResMdoMeshParts::setName(const char *name) { m_name = name; }

void DrResMdoMeshParts::setBoneName(const char *name) { m_boneName = name; }

void DrResMdoMeshParts::setMatAdd(mm::Mat44 *matrix, const mm::Mat44 *baseMat, const mm::Mat44 *ofsMat, int index) {
  m_matrix = matrix;
  m_baseMat = baseMat;
  m_ofsMat = const_cast<mm::Mat44 *>(ofsMat);
  memcpy(matrix, baseMat, sizeof(mm::Mat44));
  m_matIndex = index;
}

void DrResMdoMeshParts::setRegisterMatrix(int index, bool isRegister) {
  if (m_flags & FLAG_MAT_ADD) {
    if (isRegister) {
      if (m_flags & 1) {
        m_flags &= ~0x100;
      } else {
        m_flags |= 0x100;
      }
    } else if (m_flags & 1) {
      m_flags |= 0x200;
    } else {
      m_flags &= ~0x200;
    }
  }
}

void DrResMdoMeshParts::setDefAlpha(f32 alpha) {
  int index = DrMan::s_nDblStockIdx;
  m_defAlphas[index] = alpha;
  m_flags |= 2 << index;
  m_defAlphas[DrMan::s_nDblIdx] = alpha;
}

void DrResMdoMeshParts::updateAlpha() {
  int index = DrMan::s_nDblIdx;
  u32 bit = 2 << index;
  if (m_flags & bit) {
    m_flags &= ~bit;
    m_alpha = m_defAlphas[index];
  }
}

} // namespace ml
