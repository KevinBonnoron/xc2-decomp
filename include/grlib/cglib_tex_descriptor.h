#pragma once
#include "grlib/cglib_buff_fix_alloc.h"
#include "types.h"

namespace grlib {

class CGLibTexDescriptor : public CGLibBuffFixAlloc {
public:
  u8 _28[0x68 - 0x28];
};

static_assert(sizeof(CGLibTexDescriptor) == 0x68, "");

} // namespace grlib
