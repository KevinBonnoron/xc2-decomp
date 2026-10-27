#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {

class DrResEtcTexList {
public:
  // Inferred role: texture list resource header; original type name unknown.
  struct unknown001 {
    u8 _00[0x08];
    s32 unknown08; // Inferred role: texture count; original member name unknown.
    u32 unknown0c; // Inferred role: offset of the texture table; original member name unknown.
  };

  // Inferred role: texture table entry; original type name unknown.
  struct unknown002 {
    u32 unknown00; // Inferred role: image size; original member name unknown.
    u32 unknown04; // Inferred role: image offset; original member name unknown.
    u32 unknown08; // Inferred role: name offset; original member name unknown.
    u32 unknown0c; // Inferred role: texture id; original member name unknown.
    u8 _10[0x18 - 0x10];
  };

  void releaseTexture();
  void release();
  grlib::CGLibTextureBuffer *getTextureID(u32 id);
  grlib::CGLibTextureBuffer *getTextureName(const char *name);

  u8 _00[0x08 - 0x00];
  DrResEtcTexList *unknown08;           // Inferred role: next; original member name unknown.
  grlib::CGLibTextureBuffer *unknown10; // Inferred role: textures; original member name unknown.
  const unknown001 *unknown18;          // Inferred role: resource; original member name unknown.
  s32 unknown20;                        // Inferred role: texture count; original member name unknown.
  u8 _24[0x28 - 0x24];
  void *unknown28; // Inferred role: texture memory; original member name unknown.
  u32 unknown30;   // Inferred role: flags; original member name unknown.
};

static_assert(sizeof(DrResEtcTexList::unknown002) == 0x18, "");
static_assert(offsetof(DrResEtcTexList, unknown08) == 0x08, "");
static_assert(offsetof(DrResEtcTexList, unknown10) == 0x10, "");
static_assert(offsetof(DrResEtcTexList, unknown18) == 0x18, "");
static_assert(offsetof(DrResEtcTexList, unknown20) == 0x20, "");
static_assert(offsetof(DrResEtcTexList, unknown28) == 0x28, "");
static_assert(offsetof(DrResEtcTexList, unknown30) == 0x30, "");

} // namespace ml
