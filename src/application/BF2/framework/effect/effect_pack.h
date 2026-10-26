#pragma once
#include <stddef.h>
#include <string>

#include "framework/effect/effect_manager.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace fw {
class EffectData;

class EffectPack : public mm::mtl::ReferenceObject {
public:
  EffectPack(mtl::ALLOC_HANDLE handle, void *data, u32 size, const char *name, bool isCopy);
  ~EffectPack() override;
  static EffectPack *createFromMemory(void *data, u32 size, const char *name, bool isCopy);
  static u32 getEfbNum(void *data);
  void *searchEfb(const char *name) const;
  EffectData *searchData(const char *name) const;

  void *unknown10;                  // Inferred role: pack data; original member name unknown.
  EffectManager::DataMap unknown18; // Inferred role: effect data by name; original member name unknown.
  u32 unknown50;                    // Inferred role: pack data size; original member name unknown.
  bool unknown54;                   // Inferred role: is copy; original member name unknown.
  u8 _55[0x58 - 0x55];
  mm::mtl::FixStr<128> unknown58; // Inferred role: name; original member name unknown.
};

static_assert(offsetof(EffectPack, unknown10) == 0x10, "");
static_assert(offsetof(EffectPack, unknown18) == 0x18, "");
static_assert(offsetof(EffectPack, unknown50) == 0x50, "");
static_assert(offsetof(EffectPack, unknown58) == 0x58, "");
static_assert(sizeof(EffectPack) == 0xe0, "");

} // namespace fw
