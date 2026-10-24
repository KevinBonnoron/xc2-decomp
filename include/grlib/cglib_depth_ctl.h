#pragma once
#include "grlib/cglib_render_target.h"
#include "types.h"

namespace mm {
struct Col4;
} // namespace mm

enum GrlCompare {
  GRL_COMPARE_NEVER,
  GRL_COMPARE_LESS,
  GRL_COMPARE_EQUAL,
  GRL_COMPARE_LEQUAL,
  GRL_COMPARE_GREATER,
  GRL_COMPARE_NOTEQUAL,
  GRL_COMPARE_GEQUAL,
  GRL_COMPARE_ALWAYS,
};

enum GrlStencil {
  GRL_STENCIL_KEEP = 1,
  GRL_STENCIL_ZERO,
  GRL_STENCIL_REPLACE,
  GRL_STENCIL_INCR,
  GRL_STENCIL_DECR,
  GRL_STENCIL_INVERT,
  GRL_STENCIL_INCR_WRAP,
  GRL_STENCIL_DECR_WRAP,
};

namespace grlib {

class CGLibColorBuffer;

class CGLibDepthCtl {
public:
  static void setDepthControl(u8 isTest, u8 isWrite, GrlCompare compare);
  static void setDepthStencilControl(u8 isTest, u8 isWrite, GrlCompare compare, u8 isStencil, GrlCompare stencilCompare, u32 ref, u32 mask, u32 writeMask, GrlStencil fail, GrlStencil depthFail,
                                     GrlStencil pass);
  static void clearColorBuffer(CGLibColorBuffer &colorBuffer, const mm::Col4 &color, GrlClaerMask mask);
  static void clearIntColorBuffer(CGLibColorBuffer &colorBuffer, const int *color, GrlClaerMask mask);
};

} // namespace grlib
