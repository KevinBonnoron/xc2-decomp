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
    MotionParam() : unknown00(0), unknown04(0.0f), unknown08(0.0f), unknown0c(0.0f), unknown10(0.0f), unknown14(0.0f), unknown18(0.0f) {}

    bool has(ParamType type) const { return (unknown00 & (1 << type)) != 0; }

    u32 unknown00; // Inferred role: flags; original member name unknown.
    f32 unknown04; // Inferred role: pos x; original member name unknown.
    f32 unknown08; // Inferred role: pos y; original member name unknown.
    f32 unknown0c; // Inferred role: scale x; original member name unknown.
    f32 unknown10; // Inferred role: scale y; original member name unknown.
    f32 unknown14; // Inferred role: rot; original member name unknown.
    f32 unknown18; // Inferred role: alpha; original member name unknown.
  };

  u32 searchMotion(const char *name) const;
  f32 getMotionLength(u32 motion) const;
  void getMotionParamDefault(u32 motion, MotionParam &param) const;
  void getMotionParamDelta(u32 motion, f32 begin, f32 end, MotionParam &param) const;
};

static_assert(offsetof(UIMotionData::MotionParam, unknown18) == 0x18, "");
static_assert(sizeof(UIMotionData::MotionParam) == 0x1c, "");

} // namespace ui
