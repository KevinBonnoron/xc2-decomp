#pragma once
#include <stddef.h>

#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"

namespace fw {

class EffectData : public mm::mtl::ReferenceObject {
public:
  static EffectData *createFromMemory(void *data, u32 size, const char *name, bool isExternal);
  void *getHandle() const;
  const char *getName() const;
  EffectData(void *data, u32 size, const char *name, bool isExternal);
  ~EffectData() override;

  void *m_handle;
  mm::mtl::FixStr<128> m_name;
  bool unknown9c; // Inferred role: external; original member name unknown.
};

static_assert(offsetof(EffectData, m_handle) == 0x10, "");
static_assert(offsetof(EffectData, unknown9c) == 0x9c, "");
static_assert(sizeof(EffectData) == 0xa0, "");

} // namespace fw
