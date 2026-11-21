#pragma once
#include <stddef.h>

#include "dr/dr_res_query_acc.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {
class DrCalcViewWork;

// Inferred base: DrMdoCtlNom::occRender passes the DrResClip it holds as the DrResQueryAcc argument of
// DrPixlOccQuery::occRenderAABB (0x710080fa34), and the destructor runs the body of DrResQueryAcc::releaseQuery on the
// first member (0x71008693c0).
class DrResClip : public DrResQueryAcc {
public:
  DrResClip();
  ~DrResClip();
  bool clipChkOccOff(DrCalcViewWork *viewWork, const mm::Vec3 &position, f32 radius);

  u32 unknown08; // Inferred role: clip state flags; original member name unknown.
  s32 unknown0c; // Inferred role: state frame counter; original member name unknown.
  s32 unknown10; // Inferred role: occlusion query pixel; original member name unknown.
};

static_assert(offsetof(DrResClip, unknown08) == 0x08, "");
static_assert(offsetof(DrResClip, unknown0c) == 0x0c, "");
static_assert(offsetof(DrResClip, unknown10) == 0x10, "");

} // namespace ml
