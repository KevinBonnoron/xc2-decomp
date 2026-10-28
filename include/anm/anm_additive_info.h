#pragma once
#include <stddef.h>

#include "anm/anm_asm_state.h"
#include "anm/anm_res_state_data.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace anm {

class AsmBlender;
class AsmListener;

class AdditiveInfo {
public:
  AdditiveInfo();
  void easeOut(AsmBlender *blender, AsmListener *listener, f32 time, InterpolateType type, InterpolateCurve curve);
  void easeIn(AsmBlender *blender, AsmListener *listener, mm::mtl::IntrusivePtr<AsmState> state, f32 time, f32 weight, InterpolateType type, InterpolateCurve curve);

  mm::mtl::IntrusivePtr<AsmState> unknown00; // Inferred role: state; original member name unknown.
  f32 unknown08;                             // Inferred role: ease time; original member name unknown.
  InterpolateCurve unknown0c;                // Inferred role: ease curve; original member name unknown.
  InterpolateType unknown10;                 // Inferred role: ease type; original member name unknown.
  f32 unknown14;                             // Inferred role: elapsed time; original member name unknown.
  s32 unknown18;                             // Inferred role: ease phase (0 none, 1 in, 2 out); original member name unknown.
  f32 unknown1c;                             // Inferred role: target weight; original member name unknown.
  f32 unknown20;                             // Inferred role: weight scale; original member name unknown.
};

static_assert(offsetof(AdditiveInfo, unknown08) == 0x08, "");
static_assert(offsetof(AdditiveInfo, unknown0c) == 0x0c, "");
static_assert(offsetof(AdditiveInfo, unknown10) == 0x10, "");
static_assert(offsetof(AdditiveInfo, unknown14) == 0x14, "");
static_assert(offsetof(AdditiveInfo, unknown18) == 0x18, "");
static_assert(offsetof(AdditiveInfo, unknown1c) == 0x1c, "");
static_assert(offsetof(AdditiveInfo, unknown20) == 0x20, "");
static_assert(sizeof(AdditiveInfo) == 0x28, "");

} // namespace anm
