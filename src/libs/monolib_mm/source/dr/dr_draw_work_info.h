#pragma once
#include <stddef.h>

#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ml {

class IDrDrawWorkInfo {
public:
  u8 _000[0x90 - 0x000];
  void *m_shadowTex[2]; // Name from CloudCalcParams::getShadowTex; original member name unknown.
  u8 _a0[0xb0 - 0x0a0];
  mm::Vec3 unknownb0;   // Inferred role: camera position; original member name unknown.
  mm::Vec3 unknownc0;   // Inferred role: view direction, copied from DrCalcViewWork::unknown410 by DrCalcViewWork::begin (1.0.0: 0x71008ad8a8); original member name unknown.
  mm::Mat44 unknownd0;  // Inferred role: inverse view matrix, copied from DrCalcViewWork::unknown00 (0x71008ad880); original member name unknown.
  mm::Mat44 unknown110; // Inferred role: view matrix, copied from DrCalcViewWork::unknown40 (0x71008ad894); original member name unknown.
  mm::Mat44 unknown150; // Inferred role: projection matrix, copied from DrCalcViewWork::unknown180 (0x71008ad8a0); the former member unknown170 (cloud density) lies inside it and is removed; original
                        // member name unknown.
  mm::Mat44 unknown190; // Inferred role: projection matrix without jitter, copied from DrCalcViewWork::unknown380 (0x71008ad8ac); original member name unknown.
  u8 _1d0[0x1d4 - 0x1d0];
  f32 m_fogTbl[27]; // Name from CloudCalcParams::getFogTbl; original member name unknown.
  u8 _240[0x420 - 0x240];
  mm::Mat44 m_shadowMatrix[3]; // Name from CloudCalcParams::getShadowMatrix; original member name unknown.
  f32 m_shadowOfs[3];          // Name from CloudCalcParams::getShadowOfs; original member name unknown.
  f32 unknown4ec;              // Role unknown; original member name unknown.
  u8 _4f0[0x534 - 0x4f0];
  f32 unknown534; // Inferred role: aspect, copied from DrCalcViewWork::unknown4c0 by DrCalcViewWork::begin (1.0.0: 0x71008ad8c8); original member name unknown.
  f32 unknown538; // Inferred role: fog start; original member name unknown.
  f32 unknown53c; // Inferred role: fog end; original member name unknown.
  f32 unknown540; // Inferred role: fog density; original member name unknown.
  u8 _544[0x550 - 0x544];
  u32 unknown550; // Inferred role: screen width; original member name unknown.
  u32 unknown554; // Inferred role: screen height; original member name unknown.
  u32 unknown558; // Inferred role: render width, copied by DrCalcViewWork::begin (1.0.0: 0x71008ad930); original member name unknown.
  u32 unknown55c; // Inferred role: render height, copied by DrCalcViewWork::begin (1.0.0: 0x71008ad93c); original member name unknown.
  int unknown560; // Inferred role: loop; original member name unknown.
  u8 _564[0x568 - 0x564];
  bool unknown568; // Inferred role: copy of DrMan::unknown1d62; original member name unknown.
  u8 _569[0x580 - 0x569];
};

static_assert(offsetof(IDrDrawWorkInfo, m_shadowTex) == 0x90, "");
static_assert(offsetof(IDrDrawWorkInfo, unknownb0) == 0xb0, "");
static_assert(offsetof(IDrDrawWorkInfo, unknownc0) == 0xc0, "");
static_assert(offsetof(IDrDrawWorkInfo, unknownd0) == 0xd0, "");
static_assert(offsetof(IDrDrawWorkInfo, unknown110) == 0x110, "");
static_assert(offsetof(IDrDrawWorkInfo, unknown150) == 0x150, "");
static_assert(offsetof(IDrDrawWorkInfo, unknown190) == 0x190, "");
static_assert(offsetof(IDrDrawWorkInfo, m_fogTbl) == 0x1d4, "");
static_assert(offsetof(IDrDrawWorkInfo, m_shadowMatrix) == 0x420, "");
static_assert(offsetof(IDrDrawWorkInfo, m_shadowOfs) == 0x4e0, "");
static_assert(offsetof(IDrDrawWorkInfo, unknown4ec) == 0x4ec, "");
static_assert(offsetof(IDrDrawWorkInfo, unknown538) == 0x538, "");
static_assert(offsetof(IDrDrawWorkInfo, unknown53c) == 0x53c, "");
static_assert(offsetof(IDrDrawWorkInfo, unknown540) == 0x540, "");
static_assert(offsetof(IDrDrawWorkInfo, unknown534) == 0x534, "");
static_assert(offsetof(IDrDrawWorkInfo, unknown550) == 0x550, "");
static_assert(offsetof(IDrDrawWorkInfo, unknown554) == 0x554, "");
static_assert(offsetof(IDrDrawWorkInfo, unknown558) == 0x558, "");
static_assert(offsetof(IDrDrawWorkInfo, unknown55c) == 0x55c, "");
static_assert(offsetof(IDrDrawWorkInfo, unknown560) == 0x560, "");
static_assert(offsetof(IDrDrawWorkInfo, unknown568) == 0x568, "");
static_assert(sizeof(IDrDrawWorkInfo) == 0x580, "");

} // namespace ml
