#pragma once
#include <stddef.h>

#include "dr/dr_res_fetch.h"
#include "types.h"

namespace ml {

class DrShdFetchObj {
public:
  u8 _00[0x20 - 0x00];
  DrResFetch unknown20; // Inferred role: fetch; original member name unknown.
};

static_assert(offsetof(DrShdFetchObj, unknown20) == 0x20, "");

} // namespace ml
