#pragma once
#include <stddef.h>

#include "anm/anm_reference_object.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace mm {
struct Quat;
} // namespace mm

namespace anm {

class Skeleton;
struct QsTransform;

class MirrorMapper : public ReferenceObject {
public:
  ~MirrorMapper() override;
  void setBonePairTable(s16 *pBonePairTable);
  void mirrorExtractMotion(const QsTransform &source, QsTransform *destination) const;

  const Skeleton *unknown18;           // Inferred role: p skeleton; original member name unknown.
  mm::mtl::Vector<s16> unknown20;      // Inferred role: bone pair table; original member name unknown.
  mm::mtl::Vector<mm::Quat> unknown48; // Inferred role: bone invariants; original member name unknown.
};

static_assert(offsetof(MirrorMapper, unknown18) == 0x18, "");
static_assert(offsetof(MirrorMapper, unknown20) == 0x20, "");
static_assert(offsetof(MirrorMapper, unknown48) == 0x48, "");
static_assert(sizeof(MirrorMapper) == 0x70, "");

} // namespace anm
