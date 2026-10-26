#pragma once
#include <stddef.h>

#include "types.h"

namespace anm {
class MirrorMapper;
class SimpleMapper;
class Skeleton;
} // namespace anm

namespace fw {

class AnimResAsmResolver {
public:
  const anm::Skeleton *getSkekelton() const;
  anm::MirrorMapper *getMirrorMapper() const;
  anm::SimpleMapper *getSimpleMapper() const;

  u8 _00[0x30];                   // Inferred role: vtable pointer and binding tables; original member names unknown.
  const anm::Skeleton *unknown30; // Inferred role: skeleton; original member name unknown.
  anm::MirrorMapper *unknown38;   // Inferred role: mirror mapper; original member name unknown.
  anm::SimpleMapper *unknown40;   // Inferred role: simple mapper; original member name unknown.
};

static_assert(offsetof(AnimResAsmResolver, unknown30) == 0x30, "");
static_assert(offsetof(AnimResAsmResolver, unknown38) == 0x38, "");
static_assert(offsetof(AnimResAsmResolver, unknown40) == 0x40, "");

} // namespace fw
