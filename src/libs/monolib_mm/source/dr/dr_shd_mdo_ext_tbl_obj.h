#pragma once
#include <stddef.h>

namespace ml {

class DrShdMdoDecExtTbl;
class DrShdMdoDecShdObj;

class DrShdMdoExtTblObj {
public:
  DrShdMdoExtTblObj();

  DrShdMdoDecShdObj *unknown00; // Inferred role: shader object; original member name unknown.
  DrShdMdoDecExtTbl *unknown08; // Inferred role: extension tables; original member name unknown.
};

static_assert(offsetof(DrShdMdoExtTblObj, unknown08) == 0x08, "");

} // namespace ml
