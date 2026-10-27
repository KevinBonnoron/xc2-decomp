#pragma once
#include <stddef.h>

#include "mm_mtl/fixstr.h"
#include "types.h"

namespace layer {

class LayerRceObj {
public:
  LayerRceObj(const void *data, const char *name);
  ~LayerRceObj();
  void setRceData(const void *data, const char *name);

  LayerRceObj *unknown00;        // Inferred role: previous node; original member name unknown.
  LayerRceObj *unknown08;        // Inferred role: next node; original member name unknown.
  mm::mtl::FixStr<16> unknown10; // Inferred role: name; original member name unknown.
  const void *unknown28;         // Inferred role: rce data; original member name unknown.
  u32 unknown30;                 // Inferred role: release flags; original member name unknown.
};

static_assert(offsetof(LayerRceObj, unknown10) == 0x10, "");
static_assert(offsetof(LayerRceObj, unknown28) == 0x28, "");
static_assert(offsetof(LayerRceObj, unknown30) == 0x30, "");

} // namespace layer
