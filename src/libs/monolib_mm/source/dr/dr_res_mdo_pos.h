#pragma once
#include <stddef.h>

#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {
class DrCalcViewWork;
struct MdsPosKeepData;

class DrResMdoPos {
public:
  // Inferred role: linked object, only its back pointer at 0x28 is known; original type name unknown.
  struct unknown001 {
    u8 _00[0x28];
    DrResMdoPos *unknown28; // Inferred role: back pointer to the position; original member name unknown.
  };

  DrResMdoPos();
  DrResMdoPos(const MdsPosKeepData *keepData);
  ~DrResMdoPos();
  void copy(DrResMdoPos *source);
  void release();
  bool clipTest(DrCalcViewWork *viewWork, const mm::Vec3 &position, f32 radius);
  void setAddAlphaCnt(int count);
  bool setSubAlphaCnt(int count);

  unknown001 *unknown00;           // Inferred role: linked object; original member name unknown.
  const MdsPosKeepData *unknown08; // Inferred role: position keep data; original member name unknown.
  u8 _10[0x18 - 0x10];
  u16 unknown18; // Inferred role: unknown copied value; original member name unknown.
  u8 _1a[0x1e - 0x1a];
  u16 unknown1e; // Inferred role: cleared flags; original member name unknown.
  u8 _20[0x21 - 0x20];
  u8 unknown21; // Inferred role: alpha count; original member name unknown.
  u8 unknown22; // Inferred role: copied value; original member name unknown.
  u8 _23[0x28 - 0x23];
};

static_assert(offsetof(DrResMdoPos, unknown08) == 0x08, "");
static_assert(offsetof(DrResMdoPos, unknown18) == 0x18, "");
static_assert(offsetof(DrResMdoPos, unknown1e) == 0x1e, "");
static_assert(offsetof(DrResMdoPos, unknown21) == 0x21, "");
static_assert(offsetof(DrResMdoPos, unknown22) == 0x22, "");
static_assert(sizeof(DrResMdoPos) == 0x28, "");

} // namespace ml
