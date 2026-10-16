#pragma once
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {

class ScnRenderDrEnvColi {
public:
  ScnRenderDrEnvColi(s32 index);
  ~ScnRenderDrEnvColi();
  bool testEnvColi(const mm::Vec3 &position, f32 radius);
  s32 getWindId() const;
  bool isRoom() const;

  u8 _00[0x08 - 0x00];
};

} // namespace ml
