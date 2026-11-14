#pragma once
#include <stddef.h>

#include "dr/dr_calc_clip_man.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ml {

class DrCalcViewWork;

class DrCalcCpPlaneObj : public DrCalcClipMan::unknown009<DrCalcCpPlaneObj> {
public:
  // Inferred role: header of the clip plane data; original type name unknown.
  struct unknown005 {
    u32 unknown00; // Inferred role: offset of the plane data; original member name unknown.
    u32 unknown04; // Inferred role: offset of the plane parameters; original member name unknown.
    s32 unknown08; // Inferred role: plane count; original member name unknown.
  };

  // Inferred role: clip plane data; original type name unknown.
  struct unknown006 {
    f32 unknown00[3]; // Inferred role: center; original member name unknown.
    f32 unknown0c;    // Inferred role: bounding radius; original member name unknown.
    f32 unknown10[3]; // Inferred role: plane normal; original member name unknown.
    f32 unknown1c;    // Inferred role: plane distance; original member name unknown.
    f32 unknown20[3]; // Inferred role: first axis; original member name unknown.
    f32 unknown2c;    // Inferred role: first half extent; original member name unknown.
    f32 unknown30[3]; // Inferred role: second axis; original member name unknown.
    f32 unknown3c;    // Inferred role: second half extent; original member name unknown.
  };

  // Inferred role: clip plane parameters; original type name unknown.
  struct unknown007 {
    u8 _00[0x08 - 0x00];
    f32 unknown08; // Inferred role: maximum distance; original member name unknown.
    u32 unknown0c; // Inferred role: global index; original member name unknown.
    f32 unknown10; // Inferred role: rotation; original member name unknown.
    f32 unknown14; // Inferred role: rotation; original member name unknown.
    f32 unknown18; // Inferred role: rotation; original member name unknown.
    f32 unknown1c; // Inferred role: minimum distance; original member name unknown.
    u8 _20[0x2c - 0x20];
  };

  // Inferred role: visible plane work; original type name unknown.
  struct unknown008 {
    mm::Vec3 unknown00; // Inferred role: vector from the plane center to the view position; original member name unknown.
    f32 unknown10;      // Inferred role: negated plane distance of the view position; original member name unknown.
    u16 unknown14;      // Inferred role: plane index; original member name unknown.
    u16 unknown16;      // Inferred role: view position is in front of the plane; original member name unknown.
    u8 _18[0x20 - 0x18];
  };

  DrCalcCpPlaneObj(const void *data);
  ~DrCalcCpPlaneObj();
  void update(DrCalcViewWork *viewWork);
  void release();
  bool testClip(const mm::Vec3 &position, f32 radius);

  const unknown006 *unknown10; // Inferred role: plane data; original member name unknown.
  const unknown007 *unknown18; // Inferred role: plane parameters; original member name unknown.
  mm::Vec3 unknown20;          // Inferred role: view position; original member name unknown.
  unknown008 *unknown30;       // Inferred role: visible plane work; original member name unknown.
  s32 unknown38;               // Inferred role: visible plane count; original member name unknown.
  s32 unknown3c;               // Inferred role: plane count; original member name unknown.
  u32 unknown40;               // Inferred role: state flags; original member name unknown.
};

static_assert(offsetof(DrCalcCpPlaneObj::unknown006, unknown10) == 0x10, "");
static_assert(offsetof(DrCalcCpPlaneObj::unknown006, unknown20) == 0x20, "");
static_assert(offsetof(DrCalcCpPlaneObj::unknown006, unknown30) == 0x30, "");
static_assert(sizeof(DrCalcCpPlaneObj::unknown006) == 0x40, "");
static_assert(offsetof(DrCalcCpPlaneObj::unknown007, unknown08) == 0x08, "");
static_assert(offsetof(DrCalcCpPlaneObj::unknown007, unknown0c) == 0x0c, "");
static_assert(offsetof(DrCalcCpPlaneObj::unknown007, unknown10) == 0x10, "");
static_assert(offsetof(DrCalcCpPlaneObj::unknown007, unknown1c) == 0x1c, "");
static_assert(sizeof(DrCalcCpPlaneObj::unknown007) == 0x2c, "");
static_assert(offsetof(DrCalcCpPlaneObj::unknown008, unknown10) == 0x10, "");
static_assert(offsetof(DrCalcCpPlaneObj::unknown008, unknown14) == 0x14, "");
static_assert(offsetof(DrCalcCpPlaneObj::unknown008, unknown16) == 0x16, "");
static_assert(sizeof(DrCalcCpPlaneObj::unknown008) == 0x20, "");
static_assert(offsetof(DrCalcCpPlaneObj, unknown08) == 0x08, "");
static_assert(offsetof(DrCalcCpPlaneObj, unknown10) == 0x10, "");
static_assert(offsetof(DrCalcCpPlaneObj, unknown18) == 0x18, "");
static_assert(offsetof(DrCalcCpPlaneObj, unknown20) == 0x20, "");
static_assert(offsetof(DrCalcCpPlaneObj, unknown30) == 0x30, "");
static_assert(offsetof(DrCalcCpPlaneObj, unknown38) == 0x38, "");
static_assert(offsetof(DrCalcCpPlaneObj, unknown3c) == 0x3c, "");
static_assert(offsetof(DrCalcCpPlaneObj, unknown40) == 0x40, "");

} // namespace ml
