#pragma once
#include <stddef.h>

#include "grlib/cglib_occlusion_query.h"
#include "types.h"

namespace ml {
class DrResUseQueryObj;

struct DrResQueryObj {
  u32 getOccZPassCount();
  DrResQueryObj();
  ~DrResQueryObj();
  bool update();
  void begin();
  void end();

  DrResQueryObj *next;
  DrResQueryObj *prev;
  grlib::CGLibOcclusionQuery query;
  DrResUseQueryObj *user;
  DrResQueryObj *subNext;
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
