#pragma once
#include <stddef.h>

#include "layer/layer_base.h"
#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace layer {

class LayerFontManager;

struct LyrFontInfoData {
  u16 unknown00; // Inferred role: character code; original member name unknown.
  u8 unknown02;  // Inferred role: left offset; original member name unknown.
  u8 unknown03;  // Inferred role: width; original member name unknown.
};

static_assert(sizeof(LyrFontInfoData) == 0x4, "");

class LayerFontResObj : public LayerBase {
public:
  struct unknown001 {
    u8 _00[0x0c];
    u32 unknown0c; // Inferred role: offset of the font info table; original member name unknown.
    u32 unknown10; // Inferred role: offset of the index table; original member name unknown.
    u8 _14[0x18 - 0x14];
    u32 unknown18; // Inferred role: offset of the hash table; original member name unknown.
    u8 _1c[0x20 - 0x1c];
    u32 unknown20; // Inferred role: hash mask; original member name unknown.
    u32 unknown24; // Inferred role: offset of the texture image; original member name unknown.
    u32 unknown28; // Inferred role: size of the texture image; original member name unknown.
    u32 unknown2c; // Inferred role: offset of the texture info; original member name unknown.
    u32 unknown30; // Inferred role: line height; original member name unknown.
  };

  struct unknown002 {
    u32 unknown00; // Inferred role: texture width; original member name unknown.
    u32 unknown04; // Inferred role: texture height; original member name unknown.
    u32 unknown08; // Inferred role: glyph spacing x; original member name unknown.
    u32 unknown0c; // Inferred role: glyph spacing y; original member name unknown.
    u32 unknown10; // Inferred role: glyphs per row; original member name unknown.
  };

  struct unknown003 {
    u16 unknown00; // Inferred role: offset of the bucket entries; original member name unknown.
    u16 unknown02; // Inferred role: bucket entry count; original member name unknown.
  };

  LayerFontResObj(LayerFontManager *manager);
  ~LayerFontResObj() override;
  const LyrFontInfoData *getFontInfo(u16 &index, u16 code) const;
  void getFontUvParms(f32 &u, f32 &v, f32 &w, f32 &h, u16 index) const;
  void setFontData(const void *data);
  void setupResource();
  void release() override;

  LayerFontManager *unknown20; // Inferred role: font manager; original member name unknown.
  u32 unknown28;               // Inferred role: flags; original member name unknown.
  u8 _2c[0x30 - 0x2c];
  const void *unknown30;                // Inferred role: font data; original member name unknown.
  const unknown001 *unknown38;          // Inferred role: font data header; original member name unknown.
  const unknown003 *unknown40;          // Inferred role: hash table; original member name unknown.
  const u16 *unknown48;                 // Inferred role: index table; original member name unknown.
  const LyrFontInfoData *unknown50;     // Inferred role: font info table; original member name unknown.
  const unknown002 *unknown58;          // Inferred role: texture info; original member name unknown.
  grlib::CGLibTextureBuffer *unknown60; // Inferred role: texture buffer; original member name unknown.
  f32 unknown68;                        // Inferred role: texture ratio x; original member name unknown.
  f32 unknown6c;                        // Inferred role: texture ratio y; original member name unknown.
  f32 unknown70;                        // Inferred role: line height; original member name unknown.
  f32 unknown74;                        // Inferred role: double line height; original member name unknown.
};

static_assert(offsetof(LayerFontResObj, unknown20) == 0x20, "");
static_assert(offsetof(LayerFontResObj, unknown28) == 0x28, "");
static_assert(offsetof(LayerFontResObj, unknown30) == 0x30, "");
static_assert(offsetof(LayerFontResObj, unknown38) == 0x38, "");
static_assert(offsetof(LayerFontResObj, unknown40) == 0x40, "");
static_assert(offsetof(LayerFontResObj, unknown48) == 0x48, "");
static_assert(offsetof(LayerFontResObj, unknown50) == 0x50, "");
static_assert(offsetof(LayerFontResObj, unknown58) == 0x58, "");
static_assert(offsetof(LayerFontResObj, unknown60) == 0x60, "");
static_assert(offsetof(LayerFontResObj, unknown68) == 0x68, "");
static_assert(offsetof(LayerFontResObj, unknown70) == 0x70, "");
static_assert(offsetof(LayerFontResObj, unknown74) == 0x74, "");
static_assert(sizeof(LayerFontResObj) == 0x78, "");

} // namespace layer
