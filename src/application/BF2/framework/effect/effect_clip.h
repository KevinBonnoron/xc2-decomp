#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_vector.h"
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

struct EffectAnnotationTbl {
  u8 unknown00[0x118]; // Inferred role: annotation table record of 0x118 bytes; original member names unknown.
};

class EffectResData : public mm::mtl::ReferenceObject {
public:
  struct SetupTbl {
    EffectAnnotationTbl *unknown00; // Inferred role: annotation tables; original member name unknown.
    u32 unknown08;                  // Inferred role: tables size in bytes; original member name unknown.
  };

  struct SetupInfo {
    mm::mtl::IAllocator *unknown00;               // Inferred role: allocator; original member name unknown.
    mm::mtl::FixedVector<SetupTbl, 53> unknown08; // Inferred role: annotation tables; original member name unknown.
  };

  explicit EffectResData(mm::mtl::IAllocator *allocator);
  ~EffectResData() override;
  static EffectResData *createEffectResData(const SetupInfo &info);
  void init(const SetupInfo &info);
  void term();

  mm::mtl::Vector<EffectAnnotationData> unknown10; // Inferred role: annotations; original member name unknown.
};

static_assert(sizeof(EffectAnnotationData) == 0x120, "");
static_assert(sizeof(EffectAnnotationTbl) == 0x118, "");
static_assert(sizeof(EffectResData::SetupTbl) == 0x10, "");
static_assert(offsetof(EffectResData::SetupInfo, unknown08) == 0x08, "");
static_assert(sizeof(EffectResData::SetupInfo) == 0x360, "");
static_assert(offsetof(EffectResData, unknown10) == 0x10, "");
static_assert(sizeof(EffectResData) == 0x38, "");

} // namespace fw
