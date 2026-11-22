#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrCalcStmListObj;
class DrShdMdoDecShdObj;
struct MdsMatTechnique;

class DrShdMdoMan {
public:
  DrShdMdoMan();
  ~DrShdMdoMan();
  void update();
  DrShdMdoDecShdObj *createShaderObj(const u8 *data, const u8 *vertexData, const MdsMatTechnique *technique);
  DrShdMdoDecShdObj *createShaderObj(DrCalcStmListObj *list, const u8 *vertexData, const MdsMatTechnique *technique);
  void releaseShaderObj(DrShdMdoDecShdObj *obj);

  DrShdMdoDecShdObj *unknown00; // Inferred role: first shader object; original member name unknown.
  DrShdMdoDecShdObj *unknown08; // Inferred role: last shader object; original member name unknown.
};

static_assert(offsetof(DrShdMdoMan, unknown08) == 0x08, "");

} // namespace ml
