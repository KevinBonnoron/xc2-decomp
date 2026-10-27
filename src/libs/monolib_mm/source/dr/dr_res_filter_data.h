#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {

class DrMan;

// Evidence: member offsets and strides from DrResFilterData::setFilterData, updateColorFileter, findFilterTexture and the constructor.
class DrResFilterData {
public:
  // Inferred type: color filter slot; the original type name is unknown.
  struct unknown001 {
    grlib::CGLibTextureBuffer *unknown00; // Inferred role: first texture; original member name unknown.
    grlib::CGLibTextureBuffer *unknown08; // Inferred role: second texture; original member name unknown.
    grlib::CGLibTextureBuffer *unknown10; // Inferred role: previous first texture; original member name unknown.
    grlib::CGLibTextureBuffer *unknown18; // Inferred role: previous second texture; original member name unknown.
    s16 unknown20;                        // Inferred role: requested first texture id; original member name unknown.
    s16 unknown22;                        // Inferred role: requested second texture id; original member name unknown.
    s16 unknown24;                        // Inferred role: current first texture id; original member name unknown.
    s16 unknown26;                        // Inferred role: current second texture id; original member name unknown.
    u32 unknown28;                        // Inferred role: unknown; original member name unknown.
    f32 unknown2c;                        // Inferred role: transition time; original member name unknown.
    f32 unknown30;                        // Inferred role: transition duration; original member name unknown.
    f32 unknown34;                        // Inferred role: transition ratio; original member name unknown.
  };

  // Inferred type: texture table entry; the original type name is unknown.
  struct unknown002 {
    u32 unknown00; // Inferred role: texture data offset; original member name unknown.
    u32 unknown04; // Inferred role: texture data size; original member name unknown.
    u32 unknown08; // Inferred role: texture id; original member name unknown.
    u32 unknown0c[4];
  };

  ~DrResFilterData();
  void clear();
  void set2LayerFilterTex(int index, int first, int second, f32 time);
  void setFilterTex(int index, int texture, f32 time);
  grlib::CGLibTextureBuffer *findFilterTexture(u32 id) const;

  DrMan *unknown00;                     // Inferred role: dr man; original member name unknown.
  const unknown002 *unknown08;          // Inferred role: texture table; original member name unknown.
  unknown001 unknown10[4];              // Inferred role: filter slots; original member name unknown.
  grlib::CGLibTextureBuffer *unknownf0; // Inferred role: textures; original member name unknown.
  s32 unknownf8;                        // Inferred role: texture count; original member name unknown.
  u8 _fc[0x100 - 0xfc];
  s32 unknown100; // Inferred role: unknown; original member name unknown.
};

static_assert(sizeof(DrResFilterData::unknown001) == 0x38, "");
static_assert(sizeof(DrResFilterData::unknown002) == 0x1c, "");
static_assert(offsetof(DrResFilterData, unknown10) == 0x10, "");
static_assert(offsetof(DrResFilterData, unknownf0) == 0xf0, "");
static_assert(offsetof(DrResFilterData, unknownf8) == 0xf8, "");
static_assert(offsetof(DrResFilterData, unknown100) == 0x100, "");

} // namespace ml
