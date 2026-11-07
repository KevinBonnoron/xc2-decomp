#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_array.h"
#include "types.h"

namespace ml {
class ScnObjModel;
} // namespace ml

namespace gf {

struct GF_OBJ_HANDLE;
enum VFACC : s32;
enum VFEFF : u32;

enum VFPARTS : s32 {
  VFPARTS_UNKNOWN_FFFFFFFF = -1, // Inferred role: every part; original enumerator name unknown.
};

class GfVolumeFade {
public:
  GfVolumeFade(GF_OBJ_HANDLE *handle, ml::ScnObjModel *model);
  void initializeParam();
  void setEffectType(VFEFF effect);
  void setFadeRatio(VFACC acc, VFPARTS parts, f32 ratio);
  void applyFadeRatio();
  f32 getFadeRatio(VFACC acc, VFPARTS parts) const;
  f32 getFadeRatioForParts(VFPARTS parts) const;

  GF_OBJ_HANDLE *unknown00;                 // Inferred role: object handle; original member name unknown.
  ml::ScnObjModel *unknown08;               // Inferred role: model; original member name unknown.
  bool unknown10;                           // Inferred role: ratio changed, set by setFadeRatio and cleared by applyFadeRatio; original member name unknown.
  mm::mtl::FixedArray<f32, 6> unknown14[5]; // Inferred role: fade ratio per VFACC and VFPARTS; original member name unknown.
  u8 _8c[0x140 - 0x8c];
  VFEFF unknown140; // Inferred role: effect type; original member name unknown.
  u8 _144[0x150 - 0x144];
};

static_assert(offsetof(GfVolumeFade, unknown08) == 0x08, "");
static_assert(offsetof(GfVolumeFade, unknown10) == 0x10, "");
static_assert(offsetof(GfVolumeFade, unknown14) == 0x14, "");
static_assert(offsetof(GfVolumeFade, unknown140) == 0x140, "");
static_assert(sizeof(GfVolumeFade) == 0x150, "");

} // namespace gf
