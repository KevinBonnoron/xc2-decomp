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
