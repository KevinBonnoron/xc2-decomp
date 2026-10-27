#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {
struct _IBLPrimHeader;

struct unknown001 { // Inferred role: IBL data header; original name unknown.
  u8 _00[0x08];
  u32 unknown08; // Inferred role: IBL count; original member name unknown.
};

static_assert(offsetof(unknown001, unknown08) == 0x08, "");

struct unknown002 { // Inferred role: IBL entry; original name unknown.
  u8 _00[0x0c];
  u32 unknown0c; // Inferred role: name offset; original member name unknown.
  u8 _10[0x28 - 0x10];
};

static_assert(offsetof(unknown002, unknown0c) == 0x0c, "");
static_assert(sizeof(unknown002) == 0x28, "");

class DrIBLObj {
public:
  bool hasValidIBL() const;
  u32 getIBLNum() const;
  u32 getPriority() const;
  grlib::CGLibTextureBuffer *getAlbedoTexture() const;
  grlib::CGLibTextureBuffer *getNormalTexture() const;
  const char *getIBLName(u32 index) const;
  grlib::CGLibTextureBuffer *debug_getAlbedoTexture(u32 index) const;
  grlib::CGLibTextureBuffer *debug_getNormalTexture(u32 index) const;

  const unknown001 *unknown00; // Inferred role: IBL data; original member name unknown.
  const unknown002 *unknown08; // Inferred role: IBL entries; original member name unknown.
  u8 _10[0x38 - 0x10];
  const _IBLPrimHeader *unknown38; // Inferred role: current IBL primitive; original member name unknown.
  u32 unknown40;                   // Inferred role: texture count; original member name unknown.
  u8 _44[0x48 - 0x44];
  grlib::CGLibTextureBuffer *unknown48; // Inferred role: albedo textures; original member name unknown.
  grlib::CGLibTextureBuffer *unknown50; // Inferred role: normal textures; original member name unknown.
  u32 unknown58;                        // Inferred role: state flags; original member name unknown.
};

static_assert(offsetof(DrIBLObj, unknown08) == 0x08, "");
static_assert(offsetof(DrIBLObj, unknown38) == 0x38, "");
static_assert(offsetof(DrIBLObj, unknown40) == 0x40, "");
static_assert(offsetof(DrIBLObj, unknown48) == 0x48, "");
static_assert(offsetof(DrIBLObj, unknown50) == 0x50, "");
static_assert(offsetof(DrIBLObj, unknown58) == 0x58, "");

} // namespace ml
