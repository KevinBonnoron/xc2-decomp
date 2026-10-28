#pragma once
#include <stddef.h>

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

class SimpleMapper : public ReferenceObject {
public:
  SimpleMapper(const Skeleton &skeletonA, const Skeleton &skeletonB, mm::mtl::IAllocator *pAllocator);
  ~SimpleMapper() override;

  const Skeleton *m_pSkeletonA;
  const Skeleton *m_pSkeletonB;
  mm::mtl::Vector<s16> unknown28;                  // Inferred role: bone index of the first skeleton for each bone of the second one; original member name unknown.
  mm::mtl::Vector<mm::mtl::Vector<s16>> unknown50; // Inferred role: extra truck index table for each extra truck slot of the second skeleton; original member name unknown.
};

static_assert(offsetof(SimpleMapper, m_pSkeletonA) == 0x18, "");
static_assert(offsetof(SimpleMapper, m_pSkeletonB) == 0x20, "");
static_assert(offsetof(SimpleMapper, unknown28) == 0x28, "");
static_assert(offsetof(SimpleMapper, unknown50) == 0x50, "");
static_assert(sizeof(SimpleMapper) == 0x78, "");

} // namespace anm
