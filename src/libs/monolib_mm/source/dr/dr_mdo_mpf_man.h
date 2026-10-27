#pragma once
#include <stddef.h>

#include "grlib/cglib_dbl_uniform_block.h"
#include "types.h"

namespace ml {
struct _MPFWorkAutoInf;

class DrMdoMpfMan {
public:
  void freeMemWork(_MPFWorkAutoInf *work);
  void begin();
  static int getMpfWindMax();
  void updateInstanceBuff(u32 offset, u32 size);
  u32 advanceInstanceBuffOsf(u32 size);
  void addMpfObj();
  bool delMpfObj();
  u8 *getTempMemTbl(int size);
  void releaseList(_MPFWorkAutoInf *work);

  u8 _00[0x08 - 0x00];
  s32 unknown08; // Inferred role: mpf object count; original member name unknown.
  u8 _0c[0x98 - 0x0c];
  grlib::CGLibDblUniformBlock unknown98; // Inferred role: instance uniform block; original member name unknown.
  u8 _c8[0xd0 - 0x98 - sizeof(grlib::CGLibDblUniformBlock)];
  u32 unknownd0; // Inferred role: instance buffer offset; original member name unknown.
  u8 _d4[0xd8 - 0xd4];
  _MPFWorkAutoInf *unknownd8; // Inferred role: work list end; original member name unknown.
  _MPFWorkAutoInf *unknowne0; // Inferred role: work list end; original member name unknown.
  u8 _e8[0x3d10 - 0xe8];
  u8 *unknown3d10; // Inferred role: temporary memory; original member name unknown.
  u8 _3d18[0x3d20 - 0x3d18];
  s32 unknown3d20; // Inferred role: temporary memory used size; original member name unknown.
  f32 unknown3d24; // Inferred role: unknown value set to one by begin; original member name unknown.
};

static_assert(offsetof(DrMdoMpfMan, unknown08) == 0x08, "");
static_assert(offsetof(DrMdoMpfMan, unknown98) == 0x98, "");
static_assert(offsetof(DrMdoMpfMan, unknownd0) == 0xd0, "");
static_assert(offsetof(DrMdoMpfMan, unknownd8) == 0xd8, "");
static_assert(offsetof(DrMdoMpfMan, unknowne0) == 0xe0, "");
static_assert(offsetof(DrMdoMpfMan, unknown3d10) == 0x3d10, "");
static_assert(offsetof(DrMdoMpfMan, unknown3d20) == 0x3d20, "");
static_assert(offsetof(DrMdoMpfMan, unknown3d24) == 0x3d24, "");

} // namespace ml
