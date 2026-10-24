#pragma once
#include <stddef.h>

#include "layer/layer_base.h"
#include "types.h"

namespace layer {

class LayerFontStyleObj : public LayerBase {
public:
  void releaseColorInfo();
  void releaseIconInfo();
  s32 getStyleIndex(const char *name) const;
  const char *getStyleName(u32 index) const;
  const char *getFontName(u32 index) const;
  void createColorInfo(u32 num);
  void createIconInfo(u32 num);

  u8 _1c[0x28 - 0x1c];
  u32 unknown28; // Inferred role: style data max; original member name unknown.
  u8 _2c[0x40 - 0x2c];
  f32 unknown40; // Inferred role: ruby scale; original member name unknown.
  u8 _44[0x48 - 0x44];
  void *unknown48; // Inferred role: color info; original member name unknown.
  void *unknown50; // Inferred role: icon info; original member name unknown.
};

static_assert(offsetof(LayerFontStyleObj, unknown28) == 0x28, "");
static_assert(offsetof(LayerFontStyleObj, unknown40) == 0x40, "");
static_assert(offsetof(LayerFontStyleObj, unknown48) == 0x48, "");

} // namespace layer
