#pragma once
#include <stddef.h>

#include "framework/coli/coli_object.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_plane.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace gf {

// Evidence: the type of the water info parameter of GfEffectGround::tryGetWaterDepth (1.0.0 symbol), which the game's inlined copy in calcSwimEffectParam (0x7100502e34)
// reads at the water sample of GfEnvProperty. The sample is 0x50 bytes (from 0x280 to the flags at 0x2d0): the GfEnvProperty constructor (0x71005a30cc) initialises it with
// the stores of its member initialisers (0x280, 0x2b0 to 0x2c0: the invalid damage id of fw::COLI_INVALID_DAMAGE_ID at 0x2c0, as EnviromentSensor::unknown001 at 0x30) and then
// normalises the plane at 0x290, and EnviromentSensor::writeBackProperty (0x710051fcb0) stores the whole sample in the order of its members, after all its loads.
struct GfCharaWaterInfo {
  GfCharaWaterInfo() : unknown00(0.0f), unknown30(0.0f), unknown34(0.0f), unknown38(0), unknown3c(0), unknown40(fw::COLI_INVALID_DAMAGE_ID) { unknown10.set(mm::Vec3::zero, mm::Vec3::unitY); }

  f32 unknown00;       // Inferred role: water height; original member name unknown.
  mm::Plane unknown10; // Inferred role: water plane; original member name unknown.
  f32 unknown30;       // Inferred role: zero-initialised; original member name unknown.
  f32 unknown34;       // Inferred role: water depth; original member name unknown.
  s32 unknown38;       // Inferred role: water ground material; original member name unknown.
  s32 unknown3c;       // Inferred role: water ground material kind; original member name unknown.
  u32 unknown40;       // Inferred role: damage id; original member name unknown.
};

// Evidence: layout read from the GfEnvProperty constructor (0x71005a30cc, 0x2e0 bytes allocated by GfObjFactory), the loop over eight samples of 0x50 bytes,
// the water sample initialised at 0x280, and the accesses of GfEffectGround (flags at 0x2d0: bit 0 water sample, bit n + 1 ground sample n).
struct GfEnvProperty {
  // Values from gf::getFootGroundIndex: 1, 3, 5 for the "left", "left01", "left02" step names, 2, 4, 6 for the "right" ones. GfComIK::Ground reads sample 0
  // (getPlane, getHitPos) and sample 7 (getPlaneSub, getHitPosSub). Signed underlying type: GfComEnvSensor::flushGroundSingle indexes the samples with `smaddl x8, w19, w8, x20`
  // (1.0.0: 0x710051cb88); an enum without a negative enumerator is unsigned and gives `umaddl`.
  enum GROUND_INDEX : int {
    GROUND_INDEX_UNKNOWN_0,
    GROUND_INDEX_UNKNOWN_1,
    GROUND_INDEX_UNKNOWN_2,
    GROUND_INDEX_UNKNOWN_3,
    GROUND_INDEX_UNKNOWN_4,
    GROUND_INDEX_UNKNOWN_5,
    GROUND_INDEX_UNKNOWN_6,
    GROUND_INDEX_UNKNOWN_7,
  };

  struct unknown001 {
    mm::Vec3 unknown00;  // Inferred role: sampled position; original member name unknown.
    mm::Plane unknown10; // Inferred role: sampled plane; original member name unknown.
  };

  // Evidence: the loop of the GfEnvProperty constructor (0x71005a30cc) initialises the eight samples with these stores, and GfComEnvSensor::flushGroundSingle (0x710051c77c)
  // constructs one on the stack (the normalisation of unitY it leaves behind is the only part the optimiser keeps).
  struct unknown002 : unknown001 {
    unknown002() : unknown30(0), unknown34(0), unknown38(mm::Col4::white), unknown48(0) {
      unknown00 = mm::Vec3::zero;
      unknown10.set(mm::Vec3::zero, mm::Vec3::unitY);
    }

    s32 unknown30;      // Inferred role: zero-initialised; original member name unknown.
    s32 unknown34;      // Inferred role: ground material; original member name unknown.
    mm::Col4 unknown38; // Inferred role: ground color; original member name unknown.
    s32 unknown48;      // Inferred role: ground material kind; original member name unknown.
  };

  // Inferred helper: tests the valid bit of a ground sample; original name unknown.
  bool unknown003(int index) const { return ((1 << (index + 1)) & unknown2d0) != 0; }
  // Inferred helper: ground sample, null when it is not valid; original name unknown.
  const unknown002 *unknown004(int index) const { return unknown003(index) ? &unknown00[index] : nullptr; }

  unknown002 unknown00[8];     // Inferred role: ground samples; original member name unknown.
  GfCharaWaterInfo unknown280; // Inferred role: water sample; original member name unknown.
  u32 unknown2d0;              // Inferred role: valid samples; original member name unknown.
  bool unknown2d4;             // Inferred role: enabled flag written by EnviromentSensor::writeBackProperty (1.0.0: 0x710051fcb0); original member name unknown.
};

static_assert(sizeof(GfEnvProperty::unknown001) == 0x30, "");
static_assert(sizeof(GfCharaWaterInfo) == 0x50, "");
static_assert(offsetof(GfCharaWaterInfo, unknown30) == 0x30, "");
static_assert(offsetof(GfCharaWaterInfo, unknown38) == 0x38, "");
static_assert(offsetof(GfCharaWaterInfo, unknown40) == 0x40, "");
static_assert(sizeof(GfEnvProperty::unknown002) == 0x50, "");
static_assert(offsetof(GfEnvProperty, unknown280) == 0x280, "");
static_assert(offsetof(GfEnvProperty, unknown2d0) == 0x2d0, "");
static_assert(sizeof(GfEnvProperty) == 0x2e0, "");

} // namespace gf
