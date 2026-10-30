#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
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
  EffectAnnotationData(const EffectAnnotationData &other)
      : unknown00(other.unknown00), unknown24(other.unknown24), unknown28(other.unknown28), unknown4c(other.unknown4c), unknown54(other.unknown54), unknown78(other.unknown78),
        unknown9c(other.unknown9c), unknownc0(other.unknownc0), unknownd0(other.unknownd0), unknownd4(other.unknownd4), unknownd8(other.unknownd8), unknowne0(other.unknowne0),
        unknowne4(other.unknowne4), unknowne8(other.unknowne8), unknownf0(other.unknownf0) {}

  // Inferred helper types: the copy constructor copies these members as plain blocks; original names unknown.
  struct unknown001 {
    u32 unknown00[2];
  };

  struct unknown002 {
    u32 unknown00[3];
  };

  struct unknown003 {
    u32 unknown00[10];
  };

  // Inferred layout from the copy constructor at 0x7100169b84; original member names unknown.
  mm::mtl::FixStr<32> unknown00;
  u32 unknown24;
  mm::mtl::FixStr<32> unknown28;
  unknown001 unknown4c;
  mm::mtl::FixStr<32> unknown54;
  mm::mtl::FixStr<32> unknown78;
  mm::mtl::FixStr<32> unknown9c;
  unknown002 unknownc0;
  u32 unknowncc; // Inferred role: not copied by the copy constructor; original member name unknown.
  u32 unknownd0;
  u32 unknownd4;
  u32 unknownd8;
  u32 unknowndc; // Inferred role: not copied by the copy constructor; original member name unknown.
  u32 unknowne0;
  u32 unknowne4;
  u32 unknowne8;
  u32 unknownec; // Inferred role: not copied by the copy constructor; original member name unknown.
  unknown003 unknownf0;
  u8 unknown118[0x120 - 0x118]; // Inferred role: not copied by the copy constructor; original member names unknown.
};

struct EffectAnnotationTbl {
  u8 unknown00[0x118]; // Inferred role: annotation table record of 0x118 bytes; original member names unknown.
};

class EffectResData : public mm::mtl::ReferenceObject {
public:
  // Inferred role: setup tbl; original type name unknown.
  struct unknown004 {
    EffectAnnotationTbl *unknown00; // Inferred role: annotation tables; original member name unknown.
    u32 unknown08;                  // Inferred role: tables size in bytes; original member name unknown.
  };

  struct SetupInfo {
    mm::mtl::IAllocator *unknown00;                 // Inferred role: allocator; original member name unknown.
    mm::mtl::FixedVector<unknown004, 53> unknown08; // Inferred role: annotation tables; original member name unknown.
  };

  explicit EffectResData(mm::mtl::IAllocator *allocator);
  ~EffectResData() override;
  static EffectResData *createEffectResData(const SetupInfo &info);
  void init(const SetupInfo &info);
  void term();

  mm::mtl::Vector<EffectAnnotationData> unknown10; // Inferred role: annotations; original member name unknown.
};

static_assert(offsetof(EffectAnnotationData, unknown24) == 0x24, "");
static_assert(offsetof(EffectAnnotationData, unknown28) == 0x28, "");
static_assert(offsetof(EffectAnnotationData, unknown4c) == 0x4c, "");
static_assert(offsetof(EffectAnnotationData, unknown54) == 0x54, "");
static_assert(offsetof(EffectAnnotationData, unknown78) == 0x78, "");
static_assert(offsetof(EffectAnnotationData, unknown9c) == 0x9c, "");
static_assert(offsetof(EffectAnnotationData, unknownc0) == 0xc0, "");
static_assert(offsetof(EffectAnnotationData, unknownd0) == 0xd0, "");
static_assert(offsetof(EffectAnnotationData, unknowne0) == 0xe0, "");
static_assert(offsetof(EffectAnnotationData, unknownf0) == 0xf0, "");
static_assert(sizeof(EffectAnnotationData) == 0x120, "");
static_assert(sizeof(EffectAnnotationTbl) == 0x118, "");
static_assert(sizeof(EffectResData::unknown004) == 0x10, "");
static_assert(offsetof(EffectResData::SetupInfo, unknown08) == 0x08, "");
static_assert(sizeof(EffectResData::SetupInfo) == 0x360, "");
static_assert(offsetof(EffectResData, unknown10) == 0x10, "");
static_assert(sizeof(EffectResData) == 0x38, "");

} // namespace fw
