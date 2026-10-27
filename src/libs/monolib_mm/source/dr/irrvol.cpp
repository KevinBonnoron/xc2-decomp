#include "dr/irrvol.h"

#include "mm_math/mm_mat44.h"

namespace ml {
namespace irrvol {

void convertSHMatrix(mm::Mat44 &matrix, const f32 *coefficients) {
  matrix.rows[0][0] = coefficients[8] * 0.429043f;
  matrix.rows[0][1] = coefficients[4] * 0.429043f;
  matrix.rows[0][2] = coefficients[7] * 0.429043f;
  matrix.rows[0][3] = coefficients[3] * 0.511664f;
  matrix.rows[1][0] = coefficients[4] * 0.429043f;
  matrix.rows[1][1] = coefficients[8] * -0.429043f;
  matrix.rows[1][2] = coefficients[5] * 0.429043f;
  matrix.rows[1][3] = coefficients[1] * 0.511664f;
  matrix.rows[2][0] = coefficients[7] * 0.429043f;
  matrix.rows[2][1] = coefficients[5] * 0.429043f;
  matrix.rows[2][2] = coefficients[6] * 0.743125f;
  matrix.rows[2][3] = coefficients[2] * 0.511664f;
  matrix.rows[3][0] = coefficients[3] * 0.511664f;
  matrix.rows[3][1] = coefficients[1] * 0.511664f;
  matrix.rows[3][2] = coefficients[2] * 0.511664f;
  matrix.rows[3][3] = coefficients[0] * 0.886227f + coefficients[6] * -0.247708f;
}

void lerpSH(const f32 *from, const f32 *to, f32 ratio, f32 *result) {
  f32 inverse = 1.0f - ratio;
  for (int i = 0; i < 9; i++) {
    result[i] = inverse * from[i] + to[i] * ratio;
  }
}

} // namespace irrvol
} // namespace ml
