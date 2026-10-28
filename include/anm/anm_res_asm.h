#pragma once
#include <stddef.h>

#include "anm/anm_array-inl.h"
#include "types.h"

namespace anm {

class Skeleton;
struct ResVariable;
struct ResState;
class ResStateData;
class ResResolver;
struct AsmAnnotetion;

struct ResAppendix {
  const char *name;
  const void *data;
};

struct ResStateArray {
  u8 _00[0x18];
  Array<ResState *> unknown18;  // Inferred role: states; original member name unknown.
  Array<ResVariable> unknown28; // Inferred role: variables; original member name unknown.
  u8 _38[0x50 - 0x38];
  Array<ResAppendix> unknown50; // Inferred role: appendices, sorted by name; original member name unknown.
};

static_assert(offsetof(ResStateArray, unknown18) == 0x18, "");
static_assert(offsetof(ResStateArray, unknown28) == 0x28, "");
static_assert(offsetof(ResStateArray, unknown50) == 0x50, "");
static_assert(sizeof(ResAppendix) == 0x10, "");

class ResASM {
public:
  ResStateData *findStateData(const char *name);
  const ResStateData *findResStateData(const char *name) const;
  bool setAttribute(u32 category, const char *state, u64 attribute);
  bool setEnterAnnotation(u32 type, const char *state, const AsmAnnotetion &annotation);
  bool setLeaveAnnotation(u32 type, const char *state, const AsmAnnotetion &annotation);
  bool setFrameAnnotation(u32 type, const char *state, f32 frame, const AsmAnnotetion &annotation);
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
