#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
class DrResMdoLodParts;
struct DrResMdlLodArg;

class DrResMdoLodGrp {
public:
  DrResMdoLodGrp();
  void setup(DrResMdoLodParts *parts, int partsNum, bool isFixed, bool isChange);
  bool update(DrResMdlLodArg &arg, u32 &flags);

  DrResMdoLodParts *m_drResMdoLodParts; // Inferred role: lod parts; original member name unknown.
  s32 unknown08;                        // Inferred role: lod parts count; original member name unknown.
  s32 unknown0c;                        // Inferred role: cleared with the lod parts count; original member name unknown.
  union {
    u32 unknown10; // Inferred role: flags; original member name unknown.
    struct {
      u8 : 5;
      bool unknown10_5 : 1; // Inferred role: lod change flag; original member name unknown.
    };
  };
  u8 _14[0x20 - 0x14];
};

static_assert(offsetof(DrResMdoLodGrp, unknown08) == 0x08, "");
static_assert(offsetof(DrResMdoLodGrp, unknown10) == 0x10, "");
static_assert(sizeof(DrResMdoLodGrp) == 0x20, "");

} // namespace ml
