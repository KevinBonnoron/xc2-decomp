#pragma once
#include <stddef.h>

#include "dr/dr_res_query_acc.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {
class DrCalcViewWork;
struct MdsPosKeepData;

class DrResMdoPos {
public:
  enum Flag {
    FLAG_UNKNOWN_12 = 0x1000, // Inferred role: animated by an inst anm; original name unknown.
  };

  // Inferred role: linked object, only its back pointer at 0x28 is known; original type name unknown.
  struct unknown001 {
    u8 _00[0x28];
    DrResMdoPos *m_drResMdoPos; // Inferred role: back pointer to the position; original member name unknown.
  };

  DrResMdoPos();
  DrResMdoPos(const MdsPosKeepData *keepData);
  ~DrResMdoPos();
  void copy(DrResMdoPos *source);
  void release();
  bool clipTest(DrCalcViewWork *viewWork, const mm::Vec3 &position, f32 radius);
  void setAddAlphaCnt(int count);
  bool setSubAlphaCnt(int count);

  // The game reads the first member in two ways. The constructors, destructor and release (0x71008725f8 to 0x7100872660) store and clear it inline as the pointer to the
  // linked query object (the body of DrResQueryAcc::releaseQuery, 0x71008693d4), while DrResMdoSeamWrkInst::occRender (0x71008896d0) and DrMdoCtlPos::occRender
  // (0x710081828c, 0x71008183c8 and 0x71008184b0) pass the position itself as the DrResQueryAcc argument of DrPixlOccQuery::occRenderPosAABB. Tried instead: DrResQueryAcc as a
  // base class, as DrResClip does (the position constructors then call DrResQueryAcc::DrResQueryAcc, 0x71008693b8, instead of storing the null inline: 12 instructions
  // against 6; making the definition visible with `#include "dr_res_query_acc.cpp"` matches but defines the DrResQueryAcc functions a second time, which the game does not).
  union {
    unknown001 *unknown00;     // Inferred role: linked object; original member name unknown.
    DrResQueryAcc unknown00_1; // Inferred role: occlusion query accessor view of the same member; original member name unknown.
  };
  const MdsPosKeepData *m_mdsPosKeepData; // Inferred role: position keep data; original member name unknown.
  DrResMdoPos *m_drResMdoPos;             // Inferred role: next position in the render list; original member name unknown.
  u16 unknown18;                          // Inferred role: unknown copied value; original member name unknown.
  u8 _1a[0x1c - 0x1a];
  u16 unknown1c; // Inferred role: render list index; original member name unknown.
  u16 unknown1e; // Inferred role: cleared flags; original member name unknown.
  u8 unknown20;  // Inferred role: matrix index of the occlusion query; original member name unknown.
  u8 unknown21;  // Inferred role: alpha count; original member name unknown.
  s8 unknown22;  // Inferred role: lod index, -1 when none; original member name unknown.
  u8 _23[0x28 - 0x23];
};

static_assert(offsetof(DrResMdoPos, m_mdsPosKeepData) == 0x08, "");
static_assert(offsetof(DrResMdoPos, m_drResMdoPos) == 0x10, "");
static_assert(offsetof(DrResMdoPos, unknown18) == 0x18, "");
static_assert(offsetof(DrResMdoPos, unknown1c) == 0x1c, "");
static_assert(offsetof(DrResMdoPos, unknown1e) == 0x1e, "");
static_assert(offsetof(DrResMdoPos, unknown20) == 0x20, "");
static_assert(offsetof(DrResMdoPos, unknown21) == 0x21, "");
static_assert(offsetof(DrResMdoPos, unknown22) == 0x22, "");
static_assert(sizeof(DrResMdoPos) == 0x28, "");

} // namespace ml
