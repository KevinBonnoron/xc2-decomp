#pragma once
#include <stddef.h>

#include "mm_mtl/fixstr.h"
#include "types.h"

namespace ml {
class DrResMdoInstMdlObj;

class DrResMdoInstMdlInfo {
public:
  // Inferred role: instance model resource header; original type name unknown.
  struct unknown001 {
    u8 _00[0x08];
    s32 unknown08; // Inferred role: model object count; original member name unknown.
  };

  DrResMdoInstMdlInfo();
  ~DrResMdoInstMdlInfo();
  void releaseWork();
  void releaseCall();
  static int calcWorkSize(const u8 *resource);
  static void release(DrResMdoInstMdlInfo *&info);

  s32 unknown00;                  // Inferred role: model object count; original member name unknown.
  DrResMdoInstMdlObj *unknown08;  // Inferred role: model objects; original member name unknown.
  mm::mtl::FixStr<256> unknown10; // Inferred role: resource folder path; original member name unknown.
  const u8 *unknown118;           // Inferred role: resource; original member name unknown.
  u32 unknown120;                 // Inferred role: state flags; original member name unknown.
};

static_assert(offsetof(DrResMdoInstMdlInfo, unknown08) == 0x08, "");
static_assert(offsetof(DrResMdoInstMdlInfo, unknown10) == 0x10, "");
static_assert(offsetof(DrResMdoInstMdlInfo, unknown118) == 0x118, "");
static_assert(offsetof(DrResMdoInstMdlInfo, unknown120) == 0x120, "");
static_assert(sizeof(DrResMdoInstMdlInfo) == 0x128, "");

} // namespace ml
