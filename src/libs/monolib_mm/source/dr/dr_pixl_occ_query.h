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

  DrResQueryObj *unknown00;             // Inferred role: next; original member name unknown.
  DrResQueryObj *unknown08;             // Inferred role: prev; original member name unknown.
  grlib::CGLibOcclusionQuery unknown10; // Inferred role: query; original member name unknown.
  DrResUseQueryObj *unknown28;          // Inferred role: user; original member name unknown.
  DrResQueryObj *unknown30;             // Inferred role: sub next; original member name unknown.
  u32 unknown38;                        // Inferred role: flags; original member name unknown.
};

static_assert(offsetof(DrResQueryObj, unknown10) == 0x10, "");
static_assert(offsetof(DrResQueryObj, unknown28) == 0x28, "");
static_assert(offsetof(DrResQueryObj, unknown38) == 0x38, "");

class DrPixlOccQuery {
public:
  DrResQueryObj *createObj();
  void end();
};

} // namespace ml
