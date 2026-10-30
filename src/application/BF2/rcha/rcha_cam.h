#pragma once
#include "rcha/rcha_node.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

class RchaCam : public RchaNode {
public:
  RchaCam();
  virtual ~RchaCam();
  virtual void setup(mtl::ALLOC_HANDLE handle, const void *data);
  void getPos(mm::Vec3 *pos, f32 frame) const;
  void getRot(mm::Vec3 *rot, f32 frame) const;

private:
  u8 _19a0[0x1a20 - 0x19a0];
};

static_assert(sizeof(RchaCam) == 0x1a20, "");
