#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
class DrMdlObj;

class DrResMdoInstMdlObj {
public:
  DrResMdoInstMdlObj();
  ~DrResMdoInstMdlObj();
  void releaseWork();
  void releaseCall();

  DrMdlObj *unknown00; // Inferred role: model object; original member name unknown.
  s32 unknown08;       // Inferred role: remaining display count; original member name unknown.
};

static_assert(offsetof(DrResMdoInstMdlObj, unknown08) == 0x08, "");
static_assert(sizeof(DrResMdoInstMdlObj) == 0x10, "");

} // namespace ml
