#pragma once
#include "grlib/cglib_texture_buffer.h"
#include "types.h"

namespace ml {

class DrPixlFormat {
public:
  static f32 getPixelScale(u32 format);

  static GrlDepthFormat s_ShadowFormat;
  static GrlSurfaceFormat s_BlurVelFormat;
  static GrlSurfaceFormat s_BlurOutFormat;
  static GrlSurfaceFormat s_BlurMaskFormat;
  static GrlSurfaceFormat s_ToneMapFormat;
  static GrlSurfaceFormat s_DirShadowFormat;
  static GrlSurfaceFormat s_MrtFormat[19];
  static GrlDepthFormat s_ZBufferFormat;
  static GrlSurfaceFormat s_BackFaceDepth;
  static GrlSurfaceFormat s_SeparateCol;
  static GrlSurfaceFormat s_ResponsiveAAMask;
  static GrlDepthFormat s_UnbranchZBufferFormat;
  static GrlSurfaceFormat s_LgtLinkGIBFadeList;
  static GrlSurfaceFormat s_LgtLinkGIBIndexMask;
  static GrlSurfaceFormat s_DepthBufferFormat;
  static GrlSurfaceFormat s_QuaterNormalFormat;
  static const f32 s_fPixelScale[19]; // Name from the game symbol _ZN2ml12DrPixlFormat13s_fPixelScaleE; also in torna and xc1de.
};

} // namespace ml
