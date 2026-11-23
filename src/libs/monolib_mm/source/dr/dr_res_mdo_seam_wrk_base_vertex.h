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
  void setupVertex(int index, DrResMdoSeamMemObj *memObj);
  void changeMemVertex();

  DrResMdoSeamMemObj *m_drResMdoSeamMemObj; // Inferred role: memory object; original member name unknown.
  DrResMdoVertex *m_drResMdoVertex;         // Inferred role: vertex; original member name unknown.
  s32 unknown10;                            // Inferred role: index; original member name unknown.
};

static_assert(offsetof(DrResMdoSeamWrkBaseVertex, m_drResMdoVertex) == 0x08, "");
static_assert(offsetof(DrResMdoSeamWrkBaseVertex, unknown10) == 0x10, "");
static_assert(sizeof(DrResMdoSeamWrkBaseVertex) == 0x18, "");

} // namespace ml
