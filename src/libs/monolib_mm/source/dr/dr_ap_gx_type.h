#pragma once
#include "grlib/cglib_color_ctl.h"
#include "types.h"

namespace ml {

class DrAPGxType {
public:
  static void setupScreenQuads(bool isBlend);
  static void setupScreenQuadsWithAlpha();
  static void setupAlphaAddMaterial();
  static void setupBloomAddMaterial(GrlBlendFunc source, GrlBlendFunc destination);
  static void beginOccQuery();
  static void endOccQuery();
  static void beginMaxBlend();
  static void endMaxBlend();
  static void beginShadow();
  static void endShadow();
  static void beginSimpleShadow();
  static void endSimpleShadow();
  static void shadowCacheSetup();
  static void beginAoBlur();
  static void endAoBlur();
  static void beginColorOff();
  static void endColorOff();
  static void setupAlphaChanel(bool isAlpha);
  static void setupCullingOff();
  static void setupCullingFront();
  static void setupCullingBack();
  static void setupStencilPrePassReset();
  static void setupStencilTest(u8 isTest, u8 isWrite, int compare, u8 isStencil, u32 ref, u32 mask, int stencilCompare, int fail, int depthFail,
                               int pass);
  static void setupStencilTestWriteMask(u8 isTest, u8 isWrite, int compare, u8 isStencil, u32 ref, u32 mask, u32 writeMask, int stencilCompare,
                                        int fail, int depthFail, int pass);
  static void setupDepthContl(u8 isTest, u8 isWrite, int compare);
  static void setupBlend(int blend);
  static void getMainScreenSize(int &width, int &height);
};

} // namespace ml
