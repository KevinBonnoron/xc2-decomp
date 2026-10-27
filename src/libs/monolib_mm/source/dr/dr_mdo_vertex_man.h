#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibVtxInstans;
} // namespace grlib

namespace ml {

class DrCalcStmListObj;
class DrResMdoVertex;

class DrMdoVertexMan {
public:
  DrMdoVertexMan();
  ~DrMdoVertexMan();
  DrResMdoVertex *createVertexObj(const u8 *resource);
  DrResMdoVertex *createVertexObj(DrCalcStmListObj *list);
  void releaseVertexObj(DrResMdoVertex *vertex);
  void update();
  void begin();
  void end();

  static s32 s_nInstansBuffSize;

  DrResMdoVertex *unknown00;         // Inferred role: first vertex; original member name unknown.
  DrResMdoVertex *unknown08;         // Inferred role: last vertex; original member name unknown.
  grlib::CGLibVtxInstans *unknown10; // Inferred role: instance buffer; original member name unknown.
};

static_assert(offsetof(DrMdoVertexMan, unknown08) == 0x08, "");
static_assert(offsetof(DrMdoVertexMan, unknown10) == 0x10, "");

} // namespace ml
