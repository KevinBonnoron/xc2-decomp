#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
class DrResMdoLodGrp;
class DrResMdoLodParts;
struct DrResMdlLodArg;

class DrResMdoLodObj {
public:
  // Inferred role: model resource header holding the offset of the lod data; original type name unknown.
  struct unknown001 {
    u8 _00[0x02];
    u8 unknown02; // Inferred role: flags, bit 1 marks lod data; original member name unknown.
    u8 _03[0x8c - 0x03];
    u32 unknown8c; // Inferred role: offset of the lod data; original member name unknown.
  };

  // Inferred role: lod data header; original type name unknown.
  struct unknown002 {
    u32 unknown00; // Inferred role: flags; original member name unknown.
    u32 unknown04; // Inferred role: offset of the lod parts data; original member name unknown.
    s32 unknown08; // Inferred role: lod parts count; original member name unknown.
    u32 unknown0c; // Inferred role: offset of the lod group data; original member name unknown.
    s32 unknown10; // Inferred role: lod group count; original member name unknown.
  };

  DrResMdoLodObj();
  ~DrResMdoLodObj();
  static int calcWorkSize(const u8 *resource);
  int setup(const u8 *resource, u8 *work);
  static int create(u8 *work, const u8 *resource);
  static void release(DrResMdoLodObj *&lodObj);
  bool update(DrResMdlLodArg &arg);

  DrResMdoLodParts *m_drResMdoLodParts; // Inferred role: lod parts; original member name unknown.
  DrResMdoLodGrp *m_drResMdoLodGrp;     // Inferred role: lod groups; original member name unknown.
  s32 unknown10;                        // Inferred role: lod parts count; original member name unknown.
  u32 unknown14;                        // Inferred role: lod group count; original member name unknown.
  s32 unknown18;                        // Inferred role: state; original member name unknown.
  u32 unknown1c;                        // Inferred role: lod flags; original member name unknown.
  u8 _20[0x30 - 0x20];
};

static_assert(offsetof(DrResMdoLodObj::unknown001, unknown02) == 0x02, "");
static_assert(offsetof(DrResMdoLodObj::unknown001, unknown8c) == 0x8c, "");
static_assert(offsetof(DrResMdoLodObj::unknown002, unknown08) == 0x08, "");
static_assert(offsetof(DrResMdoLodObj::unknown002, unknown10) == 0x10, "");

static_assert(offsetof(DrResMdoLodObj, m_drResMdoLodGrp) == 0x08, "");
static_assert(offsetof(DrResMdoLodObj, unknown10) == 0x10, "");
static_assert(offsetof(DrResMdoLodObj, unknown14) == 0x14, "");
static_assert(offsetof(DrResMdoLodObj, unknown18) == 0x18, "");
static_assert(offsetof(DrResMdoLodObj, unknown1c) == 0x1c, "");
static_assert(sizeof(DrResMdoLodObj) == 0x30, "");

} // namespace ml
