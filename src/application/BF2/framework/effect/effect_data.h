#pragma once
#include <stddef.h>

#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"

namespace fw {

class EffectData : public mm::mtl::ReferenceObject {
public:
  void *getHandle() const;
  const char *getName() const;
  EffectData(void *data, u32 size, const char *name, bool isExternal);
  ~EffectData() override;

  void *handle;
  mm::mtl::FixStr<128> name;
  bool isExternal;
};

static_assert(offsetof(EffectData, handle) == 0x10, "");
static_assert(offsetof(EffectData, isExternal) == 0x9c, "");
static_assert(sizeof(EffectData) == 0xa0, "");

} // namespace fw
