#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace gf {

class GfAppend;

class GfAppendInfo {
public:
  // Evidence: GfAppendUtil::setupWeapon frees both vectors (sizes at 0x50 and 0xa8) and clears the u32 at 0xb0;
  // GfObjUtil::getAppend reads vector [weapon alternate flag] element [GFOBJ_MOUNT index]; GfAppendInfo::operator= copies 0x58 bytes twice.
  mm::mtl::FixedVector<GfAppend *, 10> unknown00[2]; // Inferred role: append sets; original member name unknown.
  u32 unknownb0;                                     // Inferred role: selected append set; original member name unknown.
};

static_assert(offsetof(GfAppendInfo, unknown00) == 0x00, "");
static_assert(offsetof(GfAppendInfo, unknownb0) == 0xb0, "");
static_assert(sizeof(GfAppendInfo) == 0xb8, "");

} // namespace gf
