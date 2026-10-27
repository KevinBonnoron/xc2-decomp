#include "dr/dr_pixl_post_obj.h"

#include <math.h>

namespace ml {

DrPixlPostObj::DrPixlPostObj(DrMan *drMan, DrPixlMan *pixlMan, DrPixlPostMan *postMan) : unknown00(drMan), unknown08(pixlMan), unknown10(postMan) {}

float DrPixlPostObj::gaussianDistribution(float x, float y, float rho) {
  float g = 1.0f / sqrtf(rho * 6.2831855f * rho);
  g *= expf((x * x + y * y) / (rho * -2.0f * rho));
  return g;
}

void DrPixlPostObj::getSampleOffsetDownScale4x4(int width, int height, float *offsets) {
  float w = static_cast<float>(width);
  float h = static_cast<float>(height);
  float scaleU = 1.0f;
  float scaleV = 1.0f;
  if (width > 1) {
    scaleU = (w - 1.0f) / w;
  }
  float tu = 1.0f / w;
  float tv = 1.0f / h;
  if (height > 1) {
    scaleV = (h - 1.0f) / h;
  }
  int index = 0;
  for (int y = -2; y < 2; y++) {
    for (int x = -2; x < 2; x++) {
      offsets[index * 2] = tu * 0.5f + tu * static_cast<float>(x) * scaleU;
      offsets[index * 2 + 1] = tv * 0.5f + tv * static_cast<float>(y) * scaleV;
      index++;
    }
  }
}

void DrPixlPostObj::calc1PixlOfs(float &x, float &y) {
  int ix = static_cast<int>(x);
  int iy = static_cast<int>(y);
  x = static_cast<float>((ix & 1) + ix);
  y = static_cast<float>((iy & 1) + iy);
}

void DrPixlPostObj::getSampleOffsets_DownScale2x2(int width, int height, float *offsets) {
  float tu = 1.0f / static_cast<float>(width);
  float tv = 1.0f / static_cast<float>(height);
  offsets[0] = tu * -0.5f;
  offsets[1] = tv * -0.5f;
  offsets[2] = tu * 0.5f;
  offsets[3] = tv * -0.5f;
  offsets[4] = tu * -0.5f;
  offsets[5] = tv * 0.5f;
  offsets[6] = tu * 0.5f;
  offsets[7] = tv * 0.5f;
}

} // namespace ml
