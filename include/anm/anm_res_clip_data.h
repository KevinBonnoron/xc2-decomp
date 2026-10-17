#pragma once
#include <stddef.h>

#include "anm/anm_asm_listener.h" // IWYU pragma: keep
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace anm {

class Binding;

struct ResClipInfo {
  u8 _00[0x10];
  f32 speed;
  f32 weight;
};

class ResClipData {
public:
  const ResClipInfo *m_pInfo;
  const Binding *m_pBinding;
  f32 m_startFrame;
  f32 m_endFrame;
  mm::mtl::FixedArray<mm::mtl::Vector<AsmKeyframeAnnotation>, 5> m_frameAnnotations;
  u8 _e0[0xe8 - 0xe0];
};

static_assert(offsetof(ResClipData, m_frameAnnotations) == 0x18, "");
static_assert(sizeof(ResClipData) == 0xe8, "");

} // namespace anm
