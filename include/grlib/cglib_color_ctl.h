#pragma once
#include "types.h"

namespace mm {
struct Col4;
} // namespace mm

enum GrlBlendFunc {
  GRL_BLEND_FUNC_ZERO = 1,
  GRL_BLEND_FUNC_ONE = 2,
  GRL_BLEND_FUNC_SRC_COLOR = 3,
  GRL_BLEND_FUNC_ONE_MINUS_SRC_COLOR = 4,
  GRL_BLEND_FUNC_SRC_ALPHA = 5,
  GRL_BLEND_FUNC_ONE_MINUS_SRC_ALPHA = 6,
  GRL_BLEND_FUNC_ONE_MINUS_DST_COLOR = 10,
};

enum GrlBlendCombine {
  GRL_BLEND_COMBINE_ADD = 1,
  GRL_BLEND_COMBINE_SUBTRACT = 2,
  GRL_BLEND_COMBINE_MIN = 4,
  GRL_BLEND_COMBINE_MAX = 5,
};

enum GrlLogicType {
  GRL_LOGIC_TYPE_COPY = 3,
  GRL_LOGIC_TYPE_OR = 7,
};

namespace grlib {

enum GrlMrtType {
  GRL_MRT_TYPE_0,
  GRL_MRT_TYPE_1,
  GRL_MRT_TYPE_2,
};

class CGLibColorCtl {
public:
  static void setBlendControl(GrlBlendFunc source, GrlBlendFunc destination, GrlBlendCombine combine, GrlLogicType logic);
  static void setBlendControl(GrlBlendFunc source, GrlBlendFunc destination, GrlBlendCombine combine, GrlBlendFunc alphaSource,
                              GrlBlendFunc alphaDestination, GrlBlendCombine alphaCombine, GrlLogicType logic);
  static void setBlendOffControl(GrlLogicType logic);
  static void setColorBufferOn();
  static void setColorBufferOff();
  static void setColorChannelMask(u8 red, u8 green, u8 blue, u8 alpha);
  static void clearMainFrameBuffer(const mm::Col4 &color);
};

} // namespace grlib
