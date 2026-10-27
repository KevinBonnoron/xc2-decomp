#pragma once
#include <stddef.h>

#include "anm/anm_asm_listener.h"  // IWYU pragma: keep
#include "anm/anm_res_clip_data.h" // IWYU pragma: keep
#include "mm/mm_std_base.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace anm {

class ResResolver;

struct ResLoopCount {
  u8 _00[0x8];
  s32 min;
  u32 range;
};

enum StateType {
  STATE_TYPE_SIMPLE,
  STATE_TYPE_FROZEN,
  STATE_TYPE_COMPLEX,
};

struct ResState {
  StateType type;
  u8 _04[0x8 - 0x4];
  const char *name;
  u64 attribute;
  u8 _18[0x30 - 0x18];
  const ResLoopCount *loopCount;
};

class ResStateData {
public:
  ResStateData();
  void cleanup();
  void restore(const ResResolver &resolver);
  void sortAnnotation(u32 type);
  void clearFrameAnnotation(u32 type);

  // __LINE__ must be 47 as in the original header: it is the line argument of the assert.
#line 46
  void setAttribute(u32 category, u64 attribute) {
    MM_ASSERT(category > 0);
    unknown30[category - 1] = attribute;
  }
  // Inferred helper: clears the enter annotations of a type; original name unknown.
  void unknown001(u32 type) { unknown50[type].clear(); }
  // Inferred helper: clears the leave annotations of a type; original name unknown.
  void unknown002(u32 type) { unknown118[type].clear(); }
  void setFrameAnnotation(u32 type, u32 clip, f32 frame, const AsmAnnotetion &annotation);
  const ResState *unknown00;                                         // Inferred role: p res state; original member name unknown.
  mm::mtl::Vector<ResClipData> unknown08;                            // Inferred role: clips; original member name unknown.
  u64 unknown30[4];                                                  // Inferred role: attributes; original member name unknown.
  mm::mtl::FixedArray<mm::mtl::Vector<AsmAnnotetion>, 5> unknown50;  // Inferred role: enter annotations; original member name unknown.
  mm::mtl::FixedArray<mm::mtl::Vector<AsmAnnotetion>, 5> unknown118; // Inferred role: leave annotations; original member name unknown.
};

static_assert(offsetof(ResStateData, unknown08) == 0x8, "");
static_assert(offsetof(ResStateData, unknown50) == 0x50, "");
static_assert(offsetof(ResStateData, unknown118) == 0x118, "");
static_assert(sizeof(ResStateData) == 0x1e0, "");

} // namespace anm
