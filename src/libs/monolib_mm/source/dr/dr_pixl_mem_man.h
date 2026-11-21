#pragma once
#include <stddef.h>

#include "mm_mtl/singleton.h"
#include "types.h"

namespace ml {

class DrPixlMemMan : public mm::mtl::PtrSingleton<DrPixlMemMan> {
public:
  // Inferred role: memory sizes of one resource category; original type name unknown.
  struct unknown001 {
    u32 unknown000[19][2]; // Inferred role: memory area of each pixl object target, [i][0] and [i][1] (DrPixlMan::calcColorBuffer 0x710083cce4); original member name unknown.
    u8 _098[0x0a8 - 0x098];
    u32 unknown0a8; // Inferred role: separate color target memory area; original member name unknown.
    u32 unknown0ac; // Inferred role: memory area of the target res 0x158; original member name unknown.
    u32 unknown0b0; // Inferred role: memory area of the target res 0x160; original member name unknown.
    u32 unknown0b4; // Inferred role: responsive AA mask memory area; original member name unknown.
    u8 _0b8[0x0bc - 0x0b8];
    u32 unknown0bc;    // Inferred role: back face depth memory area; original member name unknown.
    u32 unknown0c0[2]; // Inferred role: depth target memory areas; original member name unknown.
    u32 unknown0c8;    // Inferred role: separate trans depth memory area; original member name unknown.
    u32 unknown0cc;    // Inferred role: light depth memory area; original member name unknown.
    u32 unknown0d0;    // Inferred role: quarter size depth memory area; original member name unknown.
    u32 unknown0d4;    // Inferred role: global IBL fade list memory area; original member name unknown.
    u32 unknown0d8;    // Inferred role: global IBL index mask memory area; original member name unknown.
    u8 _0dc[0x0e8 - 0x0dc];
    u32 unknown0e8[3]; // Inferred role: memory areas of the temporal shadow buffers; original member name unknown.
    u32 unknown0f4[2]; // Inferred role: memory areas of the down depth targets (DrPixlPostMan::setupDepthBuff 0x710084da70); original member name unknown.
    u8 _0fc[0x100 - 0x0fc];
    u32 unknown100; // Inferred role: memory area of the refraction map target; original member name unknown.
    u8 _104[0x108 - 0x104];
    u32 unknown108; // Inferred role: memory area of the quarter normal target; original member name unknown.
    u32 unknown10c; // Inferred role: memory area of the tssao depth target; original member name unknown.
    u8 _110[0x174 - 0x110];
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
  u32 unknown430;           // Inferred role: memory area of the main render target; original member name unknown. `ldr w3, [x8, #0x430]` in DrPixlMan::resetColorBuff 0x710083ccc8.
  u32 unknown434;           // Inferred role: mem1 alpha free; original member name unknown.
};

static_assert(sizeof(DrPixlMemMan::unknown001) == 0x210, "");
static_assert(offsetof(DrPixlMemMan::unknown001, unknown0a8) == 0x0a8, "");
static_assert(offsetof(DrPixlMemMan::unknown001, unknown0bc) == 0x0bc, "");
static_assert(offsetof(DrPixlMemMan::unknown001, unknown0f4) == 0x0f4, "");
static_assert(offsetof(DrPixlMemMan::unknown001, unknown100) == 0x100, "");
static_assert(offsetof(DrPixlMemMan::unknown001, unknown108) == 0x108, "");
static_assert(offsetof(DrPixlMemMan::unknown001, unknown10c) == 0x10c, "");
static_assert(offsetof(DrPixlMemMan::unknown001, unknown0c0) == 0x0c0, "");
static_assert(offsetof(DrPixlMemMan::unknown001, unknown0d8) == 0x0d8, "");
static_assert(offsetof(DrPixlMemMan, unknown010) == 0x010, "");
static_assert(offsetof(DrPixlMemMan, unknown434) == 0x434, "");

} // namespace ml
