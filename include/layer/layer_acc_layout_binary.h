#pragma once
#include <stddef.h>

#include "types.h"

namespace layer {

class LayerObj;

struct LyrLayoutPosData {
  u8 _00[0x04];
  u32 unknown04; // Inferred role: name offset; original member name unknown.
  u8 _08[0x18 - 0x08];
  f32 unknown18; // Inferred role: normalized width; original member name unknown.
  f32 unknown1c; // Inferred role: normalized height; original member name unknown.
  f32 unknown20; // Inferred role: normalized x; original member name unknown.
  f32 unknown24; // Inferred role: normalized y; original member name unknown.
  u8 _28[0x2c - 0x28];
  s16 unknown2c; // Inferred role: pixel left; original member name unknown.
  s16 unknown2e; // Inferred role: pixel top; original member name unknown.
  s16 unknown30; // Inferred role: pixel right; original member name unknown.
  s16 unknown32; // Inferred role: pixel bottom; original member name unknown.
};

static_assert(offsetof(LyrLayoutPosData, unknown04) == 0x04, "");
static_assert(offsetof(LyrLayoutPosData, unknown18) == 0x18, "");
static_assert(offsetof(LyrLayoutPosData, unknown2c) == 0x2c, "");
static_assert(offsetof(LyrLayoutPosData, unknown32) == 0x32, "");
static_assert(sizeof(LyrLayoutPosData) == 0x34, "");

class LayerAccLayoutBinary {
public:
  struct unknown001 {
    u32 unknown00; // Inferred role: name offset; original member name unknown.
    u8 _04[0x0c - 0x04];
  };

  LayerAccLayoutBinary(const void *data);
  u32 getPosIdx(const char *name) const;
  const char *getPosName(u32 index) const;
  u32 getResIdx(const char *name) const;
  const char *getResName(u32 index) const;
  void setLayoutPosData(f32 &x, f32 &y, u32 index);
  void setLayoutPosData(f32 &x, f32 &y, const char *name);
  void setLayoutPosData(f32 &x, f32 &y, f32 &width, f32 &height, u32 index);
  void setLayoutPosData(f32 &x, f32 &y, f32 &width, f32 &height, const char *name);
  void setLayoutObj(LayerObj *object, u32 index, bool initScale);
  void setLayoutObj(LayerObj *object, const char *name, bool initScale);

  const u8 *unknown00;               // Inferred role: layout data; original member name unknown.
  u32 unknown08;                     // Inferred role: pos data count; original member name unknown.
  const LyrLayoutPosData *unknown10; // Inferred role: pos data table; original member name unknown.
  s32 unknown18;                     // Inferred role: res name count; original member name unknown.
  const unknown001 *unknown20;       // Inferred role: res name table; original member name unknown.
};

static_assert(sizeof(LayerAccLayoutBinary::unknown001) == 0x0c, "");
static_assert(offsetof(LayerAccLayoutBinary, unknown08) == 0x08, "");
static_assert(offsetof(LayerAccLayoutBinary, unknown10) == 0x10, "");
static_assert(offsetof(LayerAccLayoutBinary, unknown18) == 0x18, "");
static_assert(offsetof(LayerAccLayoutBinary, unknown20) == 0x20, "");
static_assert(sizeof(LayerAccLayoutBinary) == 0x28, "");

} // namespace layer
