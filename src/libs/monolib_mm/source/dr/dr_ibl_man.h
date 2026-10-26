#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrIBLObj;

class DrIBLMan {
public:
  bool isValid() const;
  void releaseObj(DrIBLObj *obj);

  u8 _000[0x910];
  DrIBLObj *unknown910; // Inferred role: current IBL object; original member name unknown.
};

static_assert(offsetof(DrIBLMan, unknown910) == 0x910, "");

} // namespace ml
