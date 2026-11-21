#include "dr/dr_pixl_post_obj.h"

#include <math.h>

#include "dr/dr_ap_cache.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_render_target.h"
#include "dr/dr_shd_data_obj.h"
#include "grlib/cglib_shader.h"
#include "grlib/cglib_uni_base_utility.h"

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

// Inferred role: gaussian weight exp(-(x * x + y * y) / (2 * rho * rho)) / sqrt(2 * pi * rho * rho) of the blur kernels, inlined into the three
// functions below (four call sites); original name unknown. Not gaussianDistribution: the compiled body of that function (`rho * -2.0f * rho`,
// fmov #-2.0 and fmul) differs from the code the blur functions have (`-(x * x + y * y) / ((rho + rho) * rho)`: fadd, fneg, fdiv; 0x7100851d9c,
// 0x7100851ed8, 0x7100852014), so they cannot call it (tried: calling gaussianDistribution from this helper breaks all three). The name is the first
// of this file's sequence: it overloads the header's unknown001, and unknown002 and unknown003 would clash with other files of the unity unit dr.cpp
// (dr_pixl_shadow_man.cpp declares the table unknown002).
static f32 unknown001(f32 x, f32 y, f32 rho) {
  f32 g = 1.0f / sqrtf(rho * 6.2831855f * rho);
  g *= expf(-(x * x + y * y) / (2.0f * rho * rho));
  return g;
}

// 0x7100851d9c. The weight is bound by reference before the call because the game computes the address `index | 2` before calling sqrtf/expf and
// keeps it in x24 (writing offsets[index + 2] directly, or a value local, fails to match).
void DrPixlPostObj::getSampleOffsets_GaussBlur_Horizontally(f32 width, f32 height, int count, f32 *offsets, f32 multiplier, f32 rho) {
  f32 sum = 0.0f;
  int taps = 0;
  int index = 0;
  for (int i = -count; i <= count; i++) {
    offsets[index] = 1.0f / width * static_cast<f32>(i);
    offsets[index + 1] = 0.0f;
    f32 &weight = offsets[index + 2];
    weight = unknown001(static_cast<f32>(i), 0.0f, rho);
    sum += weight;
    index += 4;
    taps++;
  }
  for (int i = 0; i < taps; i++) {
    offsets[i * 4 + 2] = offsets[i * 4 + 2] / sum * multiplier;
  }
}

// Same as getSampleOffsets_GaussBlur_Horizontally, 0x7100851ed8.
void DrPixlPostObj::getSampleOffsets_GaussBlur_Verticaly(f32 width, f32 height, int count, f32 *offsets, f32 multiplier, f32 rho) {
  f32 sum = 0.0f;
  int taps = 0;
  int index = 0;
  for (int i = -count; i <= count; i++) {
    offsets[index] = 0.0f;
    offsets[index + 1] = 1.0f / height * static_cast<f32>(i);
    f32 &weight = offsets[index + 2];
    weight = unknown001(static_cast<f32>(i), 0.0f, rho);
    sum += weight;
    index += 4;
    taps++;
  }
  for (int i = 0; i < taps; i++) {
    offsets[i * 4 + 2] = offsets[i * 4 + 2] / sum * multiplier;
  }
}

// 0x7100852014; the weights use unknown001 like the two blur functions above.
void DrPixlPostObj::getSampleOffsets_Bloom(int width, f32 *offsets, f32 *weights, f32 rho, f32 multiplier, int axis) {
  f32 texel = 1.0f / static_cast<f32>(width);
  weights[0] = unknown001(0.0f, 0.0f, rho) * multiplier;
  offsets[0] = 0.0f;
  offsets[1] = 0.0f;
  for (int i = 1; i < 8; i++) {
    offsets[i * 2] = 0.0f;
    offsets[i * 2 + 1] = 0.0f;
    offsets[i * 2 + axis] = texel * static_cast<f32>(i);
    weights[i] = unknown001(static_cast<f32>(i), 0.0f, rho) * multiplier;
  }
  for (int i = 1; i < 8; i++) {
    weights[i + 7] = weights[i];
    offsets[(i + 7) * 2] = 0.0f;
    offsets[(i + 7) * 2 + 1] = 0.0f;
    offsets[(i + 7) * 2 + axis] = -offsets[i * 2 + axis];
  }
}

void DrPixlPostObj::setShader3DTexture(DrShdDataObj *shader, const grlib::CGLibTextureBuffer &texture) {
  DrAPCache *apCache = unknown00->unknown5c0;
  int location = (shader->unknown38 + shader->unknown58)->getTextureLocation("t3d");
  apCache->begin3DTextureSampling();
  apCache->setTexture(texture, location);
}

void DrPixlPostObj::setShader3DTexture(DrShdDataObj *shader, const grlib::CGLibTextureBuffer &texture, const grlib::CGLibTextureBuffer &shadowTexture) {
  DrAPCache *apCache = unknown00->unknown5c0;
  int location = (shader->unknown38 + shader->unknown58)->getTextureLocation("t3d");
  int shadowLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("tSb");
  apCache->begin3DTextureSampling();
  apCache->setTexture(texture, location);
  apCache->setTexture(shadowTexture, shadowLocation);
}

void DrPixlPostObj::setShader3DTextureTransZ(DrShdDataObj *shader, const grlib::CGLibTextureBuffer &nearTexture, const grlib::CGLibTextureBuffer &farTexture) {
  DrAPCache *apCache = unknown00->unknown5c0;
  int nearLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("t3dNear");
  int farLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("t3dFar");
  apCache->begin3DTextureSampling();
  apCache->setTexture(nearTexture, nearLocation);
  apCache->setTexture(farTexture, farLocation);
}

void DrPixlPostObj::setShader3DTextureTransZ(DrShdDataObj *shader, const grlib::CGLibTextureBuffer &nearTexture, const grlib::CGLibTextureBuffer &nearShadowTexture,
                                             const grlib::CGLibTextureBuffer &farTexture, const grlib::CGLibTextureBuffer &farShadowTexture) {
  DrAPCache *apCache = unknown00->unknown5c0;
  int nearLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("t3dNear");
  int farLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("t3dFar");
  int nearShadowLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("tSbNear");
  int farShadowLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("tSbFar");
  apCache->begin3DTextureSampling();
  apCache->setTexture(nearTexture, nearLocation);
  apCache->setTexture(farTexture, farLocation);
  apCache->setTexture(nearShadowTexture, nearShadowLocation);
  apCache->setTexture(farShadowTexture, farShadowLocation);
}

void DrPixlPostObj::setUVScale_UB(grlib::CGLibUniformEtcUtility &uniform, DrShdDataObj *shader, const DrPixlRenderTarget *target, bool isFilter, u32 location, u32 offset) {
  DrAPCache *apCache = unknown00->unknown5c0;
  f32 scale[4];
  scale[0] = 1.0f;
  scale[1] = 1.0f;
  scale[2] = 0.0f;
  scale[3] = 0.0f;
  if (isFilter) {
    apCache->beginTexSampling(2, 1);
  } else {
    apCache->beginTexSampling(2, 0);
  }
  apCache->setTexture(*target->unknown70, location);
  uniform.setF32SetVec4(offset, scale);
}

} // namespace ml
