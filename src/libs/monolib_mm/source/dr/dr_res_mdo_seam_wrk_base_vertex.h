#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
class DrResMdoSeamMemObj;
class DrResMdoVertex;

class DrResMdoSeamWrkBaseVertex {
public:
  DrResMdoSeamWrkBaseVertex();
  void release();
  void changeMemVertex();

  DrResMdoSeamMemObj *unknown00; // Inferred role: memory object; original member name unknown.
  DrResMdoVertex *unknown08;     // Inferred role: vertex; original member name unknown.
  s32 unknown10;                 // Inferred role: index; original member name unknown.
};

static_assert(offsetof(DrResMdoSeamWrkBaseVertex, unknown08) == 0x08, "");
static_assert(offsetof(DrResMdoSeamWrkBaseVertex, unknown10) == 0x10, "");
static_assert(sizeof(DrResMdoSeamWrkBaseVertex) == 0x18, "");

} // namespace ml
