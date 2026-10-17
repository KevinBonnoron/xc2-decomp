#pragma once
#include <stddef.h>

#include "types.h"

namespace layer {

class LayerAccFormat {
public:
  LayerAccFormat();
  LayerAccFormat(const void *data);

  u32 format;
  u8 _04[0x05 - 0x04];
  bool mask;
  u8 _06[0x08 - 0x06];
};

static_assert(offsetof(LayerAccFormat, mask) == 0x05, "");
static_assert(sizeof(LayerAccFormat) == 0x08, "");

} // namespace layer
