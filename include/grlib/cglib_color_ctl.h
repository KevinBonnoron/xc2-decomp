#pragma once

namespace mm {
struct Col4;
} // namespace mm

enum GrlBlendFunc {
  GRL_BLEND_FUNC_SRC_ALPHA = 5,
  GRL_BLEND_FUNC_ONE_MINUS_SRC_ALPHA = 6,
};

enum GrlBlendCombine {
  GRL_BLEND_COMBINE_ADD = 1,
};

enum GrlLogicType {
  GRL_LOGIC_TYPE_COPY = 3,
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
  static void setBlendOffControl(GrlLogicType logic);
  static void setColorBufferOn();
  static void setColorBufferOff();
  static void clearMainFrameBuffer(const mm::Col4 &color);
};

} // namespace grlib
