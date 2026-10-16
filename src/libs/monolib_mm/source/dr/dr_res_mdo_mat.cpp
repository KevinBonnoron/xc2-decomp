#include "dr/dr_res_mdo_mat.h"

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

} // namespace ml
