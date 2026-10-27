#pragma once
#include <stddef.h>

#include "mm_mtl/reference_object.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {

struct EffectAnnotationData {
  u8 unknown00[0x120]; // Inferred role: annotation record of 0x120 bytes; original member names unknown.
};

class EffectResData : public mm::mtl::ReferenceObject {
public:
  explicit EffectResData(mm::mtl::IAllocator *allocator);
  ~EffectResData() override {}
  void term();

  mm::mtl::Vector<EffectAnnotationData> unknown10; // Inferred role: annotations; original member name unknown.
};

static_assert(sizeof(EffectAnnotationData) == 0x120, "");
static_assert(offsetof(EffectResData, unknown10) == 0x10, "");
static_assert(sizeof(EffectResData) == 0x38, "");

} // namespace fw
