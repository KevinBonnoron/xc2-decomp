#pragma once
#include <stddef.h>

#include "grlib/cglib_occlusion_query.h"
#include "types.h"

namespace ml {
class DrResUseQueryObj;

struct DrResQueryObj {
  DrResQueryObj *next;
  DrResQueryObj *prev;
  grlib::CGLibOcclusionQuery query;
  DrResUseQueryObj *user;
  u8 _30[0x38 - 0x30];
  u32 flags;
};

static_assert(offsetof(DrResQueryObj, query) == 0x10, "");
static_assert(offsetof(DrResQueryObj, user) == 0x28, "");
static_assert(offsetof(DrResQueryObj, flags) == 0x38, "");

class DrPixlOccQuery {
public:
  DrResQueryObj *createObj();
};

} // namespace ml
