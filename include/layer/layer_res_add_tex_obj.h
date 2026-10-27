#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace layer {

class LayerTextureObj;

class LayerResAddTexObj {
public:
  LayerResAddTexObj(grlib::CGLibTextureBuffer *texture, u32 index);
  grlib::CGLibTextureBuffer *getTexObj(u32 index);

  LayerResAddTexObj *unknown00; // Inferred role: previous node; original member name unknown.
  LayerResAddTexObj *unknown08; // Inferred role: next node; original member name unknown.
  const void *unknown10;        // Inferred role: texture resource or texture buffer; original member name unknown.
  LayerTextureObj *unknown18;   // Inferred role: texture object; original member name unknown.
  u16 unknown20;                // Inferred role: texture index; original member name unknown.
  u16 unknown22;                // Inferred role: update flags; original member name unknown.
};

static_assert(offsetof(LayerResAddTexObj, unknown10) == 0x10, "");
static_assert(offsetof(LayerResAddTexObj, unknown18) == 0x18, "");
static_assert(offsetof(LayerResAddTexObj, unknown20) == 0x20, "");
static_assert(offsetof(LayerResAddTexObj, unknown22) == 0x22, "");

} // namespace layer
