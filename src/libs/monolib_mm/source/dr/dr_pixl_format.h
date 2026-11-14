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
  static const f32 s_fPixelScale[19]; // Name from the game symbol _ZN2ml12DrPixlFormat13s_fPixelScaleE; also in torna and xc1de.
};

} // namespace ml
