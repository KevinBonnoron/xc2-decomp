#pragma once
#include <stddef.h>

#include "layer/layer_base.h"
#include "types.h"

namespace layer {

class LayerFontManager;
class LayerTextureObj;

class LayerFontIconObj : public LayerBase {
public:
  struct unknown004 {
    u8 _00[0x08];
    u8 unknown08; // Inferred role: flags; original member name unknown.
    u8 _09[0x0c - 0x09];
    u32 unknown0c; // Inferred role: offset of the texture size; original member name unknown.
    u8 _10[0x24 - 0x10];
    u32 unknown24; // Inferred role: offset of the texture; original member name unknown.
    u8 _28[0x2c - 0x28];
    u32 unknown2c; // Inferred role: offset of the icon entries; original member name unknown.
  };

  struct unknown001 {
    u8 _00[0x04];
    u32 unknown04; // Inferred role: texture width; original member name unknown.
    u8 _08[0x0c - 0x08];
    u32 unknown0c; // Inferred role: texture height; original member name unknown.
  };

  struct unknown002 {
    u8 _00[0x18];
    u32 unknown18; // Inferred role: offset of the icon entries; original member name unknown.
  };

  struct unknown005 {
    f32 unknown00; // Inferred role: u scale; original member name unknown.
    f32 unknown04; // Inferred role: v scale; original member name unknown.
    f32 unknown08; // Inferred role: u; original member name unknown.
    f32 unknown0c; // Inferred role: v; original member name unknown.
    f32 unknown10; // Inferred role: scale u; original member name unknown.
    f32 unknown14; // Inferred role: scale v; original member name unknown.
    u8 _18[0x1c - 0x18];
  };

  static_assert(sizeof(unknown005) == 0x1c, "");

  LayerFontIconObj(LayerFontManager *manager, const void *data, LAYER_TYPE type);
  ~LayerFontIconObj() override;
  void release() override;
  virtual void setupResource();
  void createIconRes();
  void getFontUvParms(f32 *uv, u16 index) const;
  void getFontUvOnlyParms(f32 *uv, u16 index) const;

  LayerFontManager *unknown20; // Inferred role: font manager; original member name unknown.
  u32 unknown28;               // Inferred role: flags; original member name unknown.
  u8 _2c[0x30 - 0x2c];
  const unknown004 *unknown30; // Inferred role: icon data; original member name unknown.
  const unknown002 *unknown38; // Inferred role: icon entries header; original member name unknown.
  LayerTextureObj *unknown40;  // Inferred role: texture object; original member name unknown.
  u32 unknown48;               // Inferred role: icon count; original member name unknown.
  f32 unknown4c;               // Inferred role: texture height; original member name unknown.
  f32 unknown50;               // Inferred role: texture width; original member name unknown.
};

static_assert(offsetof(LayerFontIconObj, unknown20) == 0x20, "");
static_assert(offsetof(LayerFontIconObj, unknown28) == 0x28, "");
static_assert(offsetof(LayerFontIconObj, unknown30) == 0x30, "");
static_assert(offsetof(LayerFontIconObj, unknown38) == 0x38, "");
static_assert(offsetof(LayerFontIconObj, unknown40) == 0x40, "");
static_assert(offsetof(LayerFontIconObj, unknown48) == 0x48, "");
static_assert(offsetof(LayerFontIconObj, unknown4c) == 0x4c, "");
static_assert(offsetof(LayerFontIconObj, unknown50) == 0x50, "");

} // namespace layer
