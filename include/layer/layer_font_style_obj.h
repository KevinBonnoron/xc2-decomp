#pragma once
#include <stddef.h>

#include "layer/layer_base.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace layer {

struct LyrFontStyleData;

class LayerFontStyleObj : public LayerBase {
public:
  // Inferred layout of a color or icon info entry; original type and member names unknown.
  struct unknown001 {
    u8 _00[0x24];
  };

  void setStyleData(const void *data);
  const LyrFontStyleData *getStyleData(u32 index) const;
  void releaseColorInfo();
  void releaseIconInfo();
  s32 getStyleIndex(const char *name) const;
  const char *getStyleName(u32 index) const;
  const char *getFontName(u32 index) const;
  void createColorInfo(u32 num);
  void createIconInfo(u32 num);

  u8 _1c[0x20 - 0x1c];
  const void *unknown20; // Inferred role: first value of the style info; original member name unknown.
  u32 unknown28;         // Inferred role: style data max; original member name unknown.
  u8 _2c[0x30 - 0x2c];
  const LyrFontStyleData *unknown30; // Inferred role: style data table; original member name unknown.
  u8 _38[0x40 - 0x38];
  f32 unknown40; // Inferred role: ruby scale; original member name unknown.
  u8 _44[0x48 - 0x44];
  mm::mtl::Vector<unknown001> *unknown48; // Inferred role: color info; original member name unknown.
  mm::mtl::Vector<unknown001> *unknown50; // Inferred role: icon info; original member name unknown.
};

static_assert(offsetof(LayerFontStyleObj, unknown20) == 0x20, "");
static_assert(offsetof(LayerFontStyleObj, unknown28) == 0x28, "");
static_assert(offsetof(LayerFontStyleObj, unknown30) == 0x30, "");
static_assert(offsetof(LayerFontStyleObj, unknown40) == 0x40, "");
static_assert(offsetof(LayerFontStyleObj, unknown48) == 0x48, "");

} // namespace layer
