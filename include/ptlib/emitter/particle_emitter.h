#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ptlib {
namespace emitter {

struct EmitterArg {
  u8 _000[0x0fc - 0x000];
  u8 m_blendMode;
  u8 _0fd[0x100 - 0x0fd];
  int m_drawType;
};

static_assert(offsetof(EmitterArg, m_blendMode) == 0xfc, "");
static_assert(offsetof(EmitterArg, m_drawType) == 0x100, "");

class EmitterObj {
public:
  bool isRenderCheck() const;

  u8 _000[0x098 - 0x000];
  EmitterArg *m_pArg;
  u8 _0a0[0x0c8 - 0x0a0];
  EmitterObj *m_pNext;
  u8 _0d0[0x110 - 0x0d0];
  mm::Vec3 m_pos;
  u8 _120[0x12c - 0x120];
  f32 m_alpha;
  u8 _130[0x150 - 0x130];
  s8 m_priorityOffset;
  bool m_isDisp;
  u8 _152[0x260 - 0x152];
  u8 m_priority;
  u8 _261[0x274 - 0x261];
  u8 m_prioIdx;
};

static_assert(offsetof(EmitterObj, m_pArg) == 0x98, "");
static_assert(offsetof(EmitterObj, m_pNext) == 0xc8, "");
static_assert(offsetof(EmitterObj, m_pos) == 0x110, "");
static_assert(offsetof(EmitterObj, m_alpha) == 0x12c, "");
static_assert(offsetof(EmitterObj, m_priorityOffset) == 0x150, "");
static_assert(offsetof(EmitterObj, m_isDisp) == 0x151, "");
static_assert(offsetof(EmitterObj, m_priority) == 0x260, "");
static_assert(offsetof(EmitterObj, m_prioIdx) == 0x274, "");

} // namespace emitter
} // namespace ptlib
