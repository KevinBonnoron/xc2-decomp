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

bool lessAsmKeyframeAnnotation(const AsmKeyframeAnnotation &annotation, const AsmKeyframeAnnotation &other);

class ResClipData {
public:
  void sortAnnotation(u32 type);

  const ResClipInfo *unknown00; // Inferred role: p info; original member name unknown.
  const Binding *m_pBinding;
  f32 unknown10;                                                            // Inferred role: start frame; original member name unknown.
  f32 unknown14;                                                            // Inferred role: end frame; original member name unknown.
  mm::mtl::FixedArray<mm::mtl::Vector<AsmKeyframeAnnotation>, 5> unknown18; // Inferred role: frame annotations; original member name unknown.
  bool unknowne0;                                                           // Inferred role: annotation dirty; original member name unknown.
  u8 _e1[0xe8 - 0xe1];
};

static_assert(offsetof(ResClipData, unknown18) == 0x18, "");
static_assert(offsetof(ResClipData, unknowne0) == 0xe0, "");
static_assert(sizeof(ResClipData) == 0xe8, "");

} // namespace anm
