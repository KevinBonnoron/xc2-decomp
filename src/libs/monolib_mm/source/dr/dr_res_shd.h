#pragma once
#include "types.h"

namespace ml {

class DrResShdMpf {
public:
  u8 _00[0x38 - 0x00];
};

static_assert(sizeof(DrResShdMpf) == 0x38, "");

class DrResShdPrePass {
public:
  u8 _00[0x40 - 0x00];
};

static_assert(sizeof(DrResShdPrePass) == 0x40, "");

class DrResShdShw {
public:
  u8 _00[0x30 - 0x00];
};

static_assert(sizeof(DrResShdShw) == 0x30, "");

class DrResShdStreamOut {
public:
  u8 _00[0x18 - 0x00];
};

static_assert(sizeof(DrResShdStreamOut) == 0x18, "");

class DrResShdObjMot {
public:
  u8 _00[0x20 - 0x00];
};

static_assert(sizeof(DrResShdObjMot) == 0x20, "");

} // namespace ml
