#pragma once

#include "grlib/cglib_render_target.h"
#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
class CGLibUniformEtcUtility;
} // namespace grlib

namespace ml {

class DrMan;
class DrPixlMan;
class DrPixlPostMan;
class DrPixlRenderTarget;
class DrShdDataObj;

// Inferred role: releases and deletes a render target; original name unknown.
inline void unknown001(grlib::CGLibRenderTarget *&target) {
  grlib::CGLibRenderTarget *renderTarget = target;
  if (renderTarget != nullptr) {
    renderTarget->releaseWork();
    delete renderTarget;
    target = nullptr;
  }
}

class DrPixlPostObj {
public:
  DrPixlPostObj(DrMan *drMan, DrPixlMan *pixlMan, DrPixlPostMan *postMan);
  static float gaussianDistribution(float x, float y, float rho);
  static void getSampleOffsets_GaussBlur_Horizontally(f32 a, f32 b, int count, f32 *offsets, f32 c, f32 d);
  static void getSampleOffsets_GaussBlur_Verticaly(f32 a, f32 b, int count, f32 *offsets, f32 c, f32 d);
  static void getSampleOffsetDownScale4x4(int width, int height, float *offsets);
  static void calc1PixlOfs(float &x, float &y);
  static void getSampleOffsets_DownScale2x2(int width, int height, float *offsets);
  void setShader3DTexture(DrShdDataObj *shader, const grlib::CGLibTextureBuffer &texture);
  void setShader3DTexture(DrShdDataObj *shader, const grlib::CGLibTextureBuffer &texture, const grlib::CGLibTextureBuffer &shadowTexture);
  void setShader3DTextureTransZ(DrShdDataObj *shader, const grlib::CGLibTextureBuffer &nearTexture, const grlib::CGLibTextureBuffer &farTexture);
  void setShader3DTextureTransZ(DrShdDataObj *shader, const grlib::CGLibTextureBuffer &nearTexture, const grlib::CGLibTextureBuffer &nearShadowTexture, const grlib::CGLibTextureBuffer &farTexture,
                                const grlib::CGLibTextureBuffer &farShadowTexture);
  void setUVScale_UB(grlib::CGLibUniformEtcUtility &uniform, DrShdDataObj *shader, const DrPixlRenderTarget *target, bool isFilter, u32 location, u32 offset);
  void setScaleShader(DrPixlRenderTarget *source);
  void setShaderBloom(DrShdDataObj *shader, grlib::CGLibUniformEtcUtility &uniform);

  DrMan *unknown00;         // Inferred role: driver manager; original member name unknown.
  DrPixlMan *unknown08;     // Inferred role: pixel manager; original member name unknown.
  DrPixlPostMan *unknown10; // Inferred role: post manager; original member name unknown.
};

} // namespace ml
