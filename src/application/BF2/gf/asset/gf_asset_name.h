#pragma once
#include <stddef.h>

#include "mm_mtl/fixstr.h"
#include "types.h"

namespace gf {

class GfAssetName {
public:
  GfAssetName(const char *name);
  const char *getName();
  void clear();
  bool hasCategory() const;
  const char *getCategory() const;
  void cutCategory();
  void setObjType(u32 type);
  void setIdUpper(u32 id);
  void setIdMiddle(u32 id);
  void setIdLower(u32 id);
  static const char *getPrefix(u32 type);

  char unknown00[16];            // Inferred role: asset name; original member name unknown.
  int unknown10;                 // Inferred role: asset name length; original member name unknown.
  mm::mtl::FixStr<32> unknown14; // Inferred role: object type prefix; original member name unknown.
  mm::mtl::FixStr<64> unknown38; // Inferred role: full name; original member name unknown.
};

static_assert(offsetof(GfAssetName, unknown10) == 0x10, "");
static_assert(offsetof(GfAssetName, unknown14) == 0x14, "");
static_assert(offsetof(GfAssetName, unknown38) == 0x38, "");
static_assert(sizeof(GfAssetName) == 0x7c, "");

} // namespace gf
