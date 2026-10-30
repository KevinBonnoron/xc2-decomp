#pragma once
#include <stddef.h>

#include "dr/dr_res_fetch.h"
#include "types.h"

namespace ml {

class DrShdFetchObj {
public:
  DrShdFetchObj(u32 first, u32 second, u32 third, int num, const MdsMatVertexInfo *infos);
  ~DrShdFetchObj();

  DrShdFetchObj *unknown00; // Inferred role: previous fetch object of DrShdFetchMan; original member name unknown.
  DrShdFetchObj *unknown08; // Inferred role: next fetch object of DrShdFetchMan; original member name unknown.
  u32 unknown10;            // Inferred role: first constructor argument; original member name unknown.
  u32 unknown14;            // Inferred role: second constructor argument; original member name unknown.
  u32 unknown18;            // Inferred role: third constructor argument; original member name unknown.
  s32 unknown1c;            // Inferred role: reference count, set to 1 by the constructor; original member name unknown.
  DrResFetch unknown20;     // Inferred role: fetch; original member name unknown.
};

static_assert(offsetof(DrShdFetchObj, unknown10) == 0x10, "");
static_assert(offsetof(DrShdFetchObj, unknown14) == 0x14, "");
static_assert(offsetof(DrShdFetchObj, unknown18) == 0x18, "");
static_assert(offsetof(DrShdFetchObj, unknown1c) == 0x1c, "");
static_assert(offsetof(DrShdFetchObj, unknown20) == 0x20, "");

} // namespace ml
