#pragma once
#include <stddef.h>

#include "anm/anm_array-inl.h"
#include "anm/anm_qs_transform.h"
#include "anm/anm_reference_object.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace anm {

class Skeleton;

// Inferred helper: bone pair mapping entry of the skeleton mapper data, 0x40 bytes; original name unknown.
struct unknown00d {
  u16 unknown00; // Inferred role: source bone index; original member name unknown.
  u16 unknown02; // Inferred role: destination bone index; original member name unknown.
  u8 _04[0x10 - 0x04];
  QsTransform unknown10; // Inferred role: offset transform; original member name unknown.
};

static_assert(offsetof(unknown00d, unknown02) == 0x02, "");
static_assert(offsetof(unknown00d, unknown10) == 0x10, "");
static_assert(sizeof(unknown00d) == 0x40, "");

// Inferred helper: chain mapping entry of the skeleton mapper data, 0x70 bytes; original name unknown.
struct unknown00e {
  u8 _00[0x02];
  u16 unknown02; // Inferred role: destination bone index; original member name unknown.
  u16 unknown04; // Inferred role: source bone index; original member name unknown.
  u16 unknown06; // Inferred role: chain end bone index; original member name unknown.
  u8 _08[0x10 - 0x08];
  QsTransform unknown10; // Inferred role: offset transform; original member name unknown.
  u8 _40[0x70 - 0x40];
};

static_assert(offsetof(unknown00e, unknown02) == 0x02, "");
static_assert(offsetof(unknown00e, unknown04) == 0x04, "");
static_assert(offsetof(unknown00e, unknown06) == 0x06, "");
static_assert(offsetof(unknown00e, unknown10) == 0x10, "");
static_assert(sizeof(unknown00e) == 0x70, "");

struct SkeletonMapperData {
  u8 _00[0x18];
  const char *unknown18;       // Inferred role: source skeleton name; original member name unknown.
  const char *unknown20;       // Inferred role: destination skeleton name; original member name unknown.
  u32 unknown28;               // Inferred role: source skeleton bone count; original member name unknown.
  u32 unknown2c;               // Inferred role: destination skeleton bone count; original member name unknown.
  Array<unknown00d> unknown30; // Inferred role: bone pair entries; original member name unknown.
  Array<unknown00e> unknown40; // Inferred role: chain entries; original member name unknown.
};

static_assert(offsetof(SkeletonMapperData, unknown18) == 0x18, "");
static_assert(offsetof(SkeletonMapperData, unknown20) == 0x20, "");
static_assert(offsetof(SkeletonMapperData, unknown28) == 0x28, "");
static_assert(offsetof(SkeletonMapperData, unknown2c) == 0x2c, "");
static_assert(offsetof(SkeletonMapperData, unknown30) == 0x30, "");
static_assert(offsetof(SkeletonMapperData, unknown40) == 0x40, "");

class SkeletonMapper : public ReferenceObject {
public:
  SkeletonMapper(const Skeleton &skeletonA, const Skeleton &skeletonB, const SkeletonMapperData &data, mm::mtl::IAllocator *pAllocator);
  ~SkeletonMapper() override;
  static bool enableBind(const Skeleton &skeletonA, const Skeleton &skeletonB, const SkeletonMapperData &data);

  const Skeleton *unknown18;           // Inferred role: source skeleton; original member name unknown.
  const Skeleton *unknown20;           // Inferred role: destination skeleton; original member name unknown.
  const SkeletonMapperData *unknown28; // Inferred role: mapper data; original member name unknown.
  mm::mtl::Vector<u16> unknown30;      // Inferred role: bone chain work buffer; original member name unknown.
};

static_assert(offsetof(SkeletonMapper, unknown18) == 0x18, "");
static_assert(offsetof(SkeletonMapper, unknown20) == 0x20, "");
static_assert(offsetof(SkeletonMapper, unknown28) == 0x28, "");
static_assert(offsetof(SkeletonMapper, unknown30) == 0x30, "");
static_assert(sizeof(SkeletonMapper) == 0x58, "");

} // namespace anm
