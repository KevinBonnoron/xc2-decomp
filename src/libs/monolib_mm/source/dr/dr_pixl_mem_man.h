#pragma once
#include <stddef.h>

#include "mm_mtl/singleton.h"
#include "types.h"

namespace ml {

class DrPixlMemMan : public mm::mtl::PtrSingleton<DrPixlMemMan> {
public:
  // Inferred role: memory sizes of one resource category; original type name unknown.
  struct unknown001 {
    u8 _000[0x174];
    u32 unknown174; // Inferred role: velocity buffer memory offset; original member name unknown.
    u32 unknown178; // Inferred role: velocity blur buffer memory offset; original member name unknown.
    u32 unknown17c; // Inferred role: blur output buffer memory offset; original member name unknown.
    u32 unknown180; // Inferred role: max velocity per tile buffer memory offset; original member name unknown.
    u32 unknown184; // Inferred role: max velocity per tile blur buffer memory offset; original member name unknown.
    u32 unknown188; // Inferred role: blur mask buffer memory offset; original member name unknown.
    u8 _18c[0x19c - 0x18c];
    u32 unknown19c[6]; // Inferred role: scale down target sizes of the tone map; original member name unknown.
    u8 _1b4[0x1e8 - 0x1b4];
    u32 unknown1e8; // Inferred role: shadow cache objects memory offset; original member name unknown.
    u32 unknown1ec; // Inferred role: shadow direction depth target memory offset; original member name unknown.
    u32 unknown1f0; // Inferred role: memory size of one shadow cache object; original member name unknown.
    u32 unknown1f4; // Inferred role: last shadow cache objects memory offset; original member name unknown.
    u32 unknown1f8; // Inferred role: last shadow direction depth target memory offset; original member name unknown.
    u32 unknown1fc; // Inferred role: memory size of one last shadow cache object; original member name unknown.
    u8 _200[0x210 - 0x200];
  };

  DrPixlMemMan();
  virtual ~DrPixlMemMan();
  void setupMemBuff();

  u8 _008[0x010 - 0x008];
  unknown001 unknown010[2]; // Inferred role: memory sizes per resource category; original member name unknown.
  u8 _430[0x434 - 0x430];
  u32 unknown434; // Inferred role: mem1 alpha free; original member name unknown.
};

static_assert(sizeof(DrPixlMemMan::unknown001) == 0x210, "");
static_assert(offsetof(DrPixlMemMan, unknown010) == 0x010, "");
static_assert(offsetof(DrPixlMemMan, unknown434) == 0x434, "");

} // namespace ml
