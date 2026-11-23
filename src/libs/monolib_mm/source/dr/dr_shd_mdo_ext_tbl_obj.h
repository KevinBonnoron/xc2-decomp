#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrShdMdoDecExtTbl;
class DrShdMdoDecShdObj;
struct MdsMatTechnique;

class DrShdMdoExtTblObj {
public:
  // Inferred type: extension table archive header; the original type name is unknown.
  struct unknown001 {
    u8 _00[0x08 - 0x00];
    u32 unknown08; // Inferred role: entry table offset; original member name unknown.
    s32 unknown0c; // Inferred role: entry count; original member name unknown.
    u8 _10[0x18 - 0x10];
    u32 unknown18; // Inferred role: table data offset; original member name unknown.
  };

  // Inferred type: extension table archive entry; the original type name is unknown.
  struct unknown002 {
    u32 unknown00; // Inferred role: table offset; original member name unknown.
    u32 unknown04; // Inferred role: unknown; original member name unknown.
  };

  DrShdMdoExtTblObj();
  static int getDecWorkSize(int declarationNum, const u8 *data);
  int setDecObj(DrShdMdoDecShdObj *obj, u8 *work, const u8 *data, int declarationNum, const MdsMatTechnique *technique, const u8 *extData);

  DrShdMdoDecShdObj *m_drShdMdoDecShdObj; // Inferred role: shader object; original member name unknown.
  DrShdMdoDecExtTbl *m_drShdMdoDecExtTbl; // Inferred role: extension tables; original member name unknown.
};

static_assert(offsetof(DrShdMdoExtTblObj::unknown001, unknown08) == 0x08, "");
static_assert(offsetof(DrShdMdoExtTblObj::unknown001, unknown0c) == 0x0c, "");
static_assert(offsetof(DrShdMdoExtTblObj::unknown001, unknown18) == 0x18, "");
static_assert(sizeof(DrShdMdoExtTblObj::unknown002) == 0x08, "");
static_assert(offsetof(DrShdMdoExtTblObj, m_drShdMdoDecExtTbl) == 0x08, "");

} // namespace ml
