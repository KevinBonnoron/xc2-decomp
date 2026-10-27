#pragma once
#include "types.h"

namespace ml {

class DrMdoCtlMpfInst {
public:
  DrMdoCtlMpfInst();
  void setupInstMpf(const u8 *resource);

  const u8 *unknown00; // Inferred role: instance data; original member name unknown.
};

} // namespace ml
