#pragma once
#include <stddef.h>

#include "types.h"

namespace anm {

class ResStateData;
class Skeleton;

class ResASM {
public:
  const ResStateData *findResStateData(const char *name) const;
  void sortAnnotation(u32 type);

  u8 _00[0x18];
  const Skeleton *m_pSkeleton;
};

static_assert(offsetof(ResASM, m_pSkeleton) == 0x18, "");

} // namespace anm
