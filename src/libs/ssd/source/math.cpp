#include "ssd/ssd_sound.h"
#include "ssd/ssd_sound_listener.h"

namespace ssd {

void MakeIdentityf34(Mat34 *matrix) {
  matrix->unknown00[0][0] = 1.0f;
  matrix->unknown00[0][1] = 0.0f;
  matrix->unknown00[0][2] = 0.0f;
  matrix->unknown00[1][0] = 0.0f;
  matrix->unknown00[1][1] = 1.0f;
  matrix->unknown00[1][2] = 0.0f;
  matrix->unknown00[2][0] = 0.0f;
  matrix->unknown00[2][1] = 0.0f;
  matrix->unknown00[2][2] = 1.0f;
  matrix->unknown00[3][0] = 0.0f;
  matrix->unknown00[3][1] = 0.0f;
  matrix->unknown00[3][2] = 0.0f;
}

void GetMatAxes(Vector3 *axisX, Vector3 *axisY, Vector3 *axisZ, Vector3 *translation, const Mat34 &matrix) {
  axisX->unknown00 = matrix.unknown00[0][0];
  axisX->unknown04 = matrix.unknown00[0][1];
  axisX->unknown08 = matrix.unknown00[0][2];
  axisY->unknown00 = matrix.unknown00[1][0];
  axisY->unknown04 = matrix.unknown00[1][1];
  axisY->unknown08 = matrix.unknown00[1][2];
  axisZ->unknown00 = matrix.unknown00[2][0];
  axisZ->unknown04 = matrix.unknown00[2][1];
  axisZ->unknown08 = matrix.unknown00[2][2];
  translation->unknown00 = matrix.unknown00[3][0];
  translation->unknown04 = matrix.unknown00[3][1];
  translation->unknown08 = matrix.unknown00[3][2];
}

Vec3 *Vec3Transform(const Mat34 *matrix, const Vec3 *in, Vec3 *out) {
  Vec3 result(in->x * matrix->unknown00[0][0] + in->y * matrix->unknown00[1][0] + in->z * matrix->unknown00[2][0] + matrix->unknown00[3][0],
              in->x * matrix->unknown00[0][1] + in->y * matrix->unknown00[1][1] + in->z * matrix->unknown00[2][1] + matrix->unknown00[3][1],
              in->x * matrix->unknown00[0][2] + in->y * matrix->unknown00[1][2] + in->z * matrix->unknown00[2][2] + matrix->unknown00[3][2]);
  *out = result;
  return out;
}

} // namespace ssd
