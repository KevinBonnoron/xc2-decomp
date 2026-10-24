#pragma once
#include <stddef.h>

#include "types.h"

namespace layer {

class LayerAccFormat {
public:
  LayerAccFormat();
  LayerAccFormat(const void *data);

  u32 unknown00; // Inferred role: format; original member name unknown.
  u8 _04[0x05 - 0x04];
  bool unknown05; // Inferred role: mask; original member name unknown.
  u8 _06[0x08 - 0x06];
};

static_assert(offsetof(LayerAccFormat, unknown05) == 0x05, "");
static_assert(sizeof(LayerAccFormat) == 0x08, "");

} // namespace layer
