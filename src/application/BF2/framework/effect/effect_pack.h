#pragma once
#include <stddef.h>

#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"

namespace fw {

class EffectPack : public mm::mtl::ReferenceObject {
public:
  static EffectPack *createFromMemory(void *data, u32 size, const char *name, bool isCopy);
  void *searchEfb(const char *name) const;

  u8 _0c[0x58 - 0x0c];
  mm::mtl::FixStr<128> unknown58; // Inferred role: name; original member name unknown.
};

static_assert(offsetof(EffectPack, unknown58) == 0x58, "");

} // namespace fw
