#pragma once
#include <stddef.h>

#include "types.h"

namespace ui {

class UIMotionData {
public:
  enum ParamType {
    PARAM_TYPE_POS_X = 0,
    PARAM_TYPE_POS_Y = 1,
    PARAM_TYPE_SCALE_X = 2,
    PARAM_TYPE_SCALE_Y = 3,
    PARAM_TYPE_ROT = 4,
    PARAM_TYPE_ALPHA = 5,
  };

  struct MotionParam {
    MotionParam() : flags(0), posX(0.0f), posY(0.0f), scaleX(0.0f), scaleY(0.0f), rot(0.0f), alpha(0.0f) {}

    bool has(ParamType type) const { return (flags & (1 << type)) != 0; }

    u32 flags;
    f32 posX;
    f32 posY;
    f32 scaleX;
    f32 scaleY;
    f32 rot;
    f32 alpha;
  };

  u32 searchMotion(const char *name) const;
  f32 getMotionLength(u32 motion) const;
  void getMotionParamDefault(u32 motion, MotionParam &param) const;
  void getMotionParamDelta(u32 motion, f32 begin, f32 end, MotionParam &param) const;
};

static_assert(offsetof(UIMotionData::MotionParam, alpha) == 0x18, "");
static_assert(sizeof(UIMotionData::MotionParam) == 0x1c, "");

} // namespace ui
