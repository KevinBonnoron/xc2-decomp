#pragma once
#include <stddef.h>

#include "anm/anm_array-inl.h"
#include "types.h"

namespace anm {

class Skeleton;
struct ResVariable;
class ResStateData;
class ResResolver;

struct ResStateArray {
  u8 _00[0x28];
  Array<ResVariable> unknown28; // Inferred role: variables; original member name unknown.
};

static_assert(offsetof(ResStateArray, unknown28) == 0x28, "");

class ResASM {
public:
  const ResStateData *findResStateData(const char *name) const;
  void restore(const ResResolver &resolver);
  void clearAnnotations(u32 type);
  void clearEnterAnnotation(u32 type);
  void clearLeaveAnnotation(u32 type);
  void sortAnnotation(u32 type);
  void clearAttribute(u32 category);
  void clearFrameAnnotation(u32 type);

  u8 _00[0x18];
  const Skeleton *m_pSkeleton;
  const ResStateArray *unknown20; // Inferred role: p res state array; original member name unknown.
  Array<ResStateData> unknown28;  // Inferred role: states, sorted by name; original member name unknown.
};

static_assert(offsetof(ResASM, m_pSkeleton) == 0x18, "");
static_assert(offsetof(ResASM, unknown20) == 0x20, "");
static_assert(offsetof(ResASM, unknown28) == 0x28, "");

} // namespace anm
