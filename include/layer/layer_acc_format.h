#pragma once
#include <stddef.h>

#include "types.h"

namespace layer {

class LayerAccFormat {
public:
  LayerAccFormat();
  LayerAccFormat(const void *data);
  void setLayerData(const void *data);

  u32 unknown00;  // Inferred role: format; original member name unknown.
  bool unknown04; // Inferred role: has extra data; original member name unknown.
  bool unknown05; // Inferred role: mask; original member name unknown.
  bool unknown06; // Inferred role: multiple entries; original member name unknown.
  u8 _07[0x08 - 0x07];
};

static_assert(offsetof(LayerAccFormat, unknown04) == 0x04, "");
static_assert(offsetof(LayerAccFormat, unknown05) == 0x05, "");
static_assert(offsetof(LayerAccFormat, unknown06) == 0x06, "");
static_assert(sizeof(LayerAccFormat) == 0x08, "");

} // namespace layer
