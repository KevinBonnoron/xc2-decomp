#pragma once
#include <stddef.h>

#include "anm/anm_asm_listener.h" // IWYU pragma: keep
#include "anm/anm_res_clip_data.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace anm {

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
  const ResState *m_pResState;
  mm::mtl::Vector<ResClipData> m_clips;
  u64 m_attributes[4];
  mm::mtl::FixedArray<mm::mtl::Vector<AsmAnnotetion>, 5> m_enterAnnotations;
  mm::mtl::FixedArray<mm::mtl::Vector<AsmAnnotetion>, 5> m_leaveAnnotations;
};

static_assert(offsetof(ResStateData, m_clips) == 0x8, "");
static_assert(offsetof(ResStateData, m_enterAnnotations) == 0x50, "");
static_assert(offsetof(ResStateData, m_leaveAnnotations) == 0x118, "");
static_assert(sizeof(ResStateData) == 0x1e0, "");

} // namespace anm
