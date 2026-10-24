#pragma once
#include <stddef.h>

#include "mm_math/mm_mat44.h"
#include "types.h"

namespace ml {

class DrMan;

class DrResOccUniformObj {
public:
  mm::Mat44 *getMatTbl(int index) { return &unknown10[index]; }
  DrResOccUniformObj(DrMan *drMan, int max);
  ~DrResOccUniformObj();
  void begin();
  void end();
  mm::Mat44 *getMatTbl();

  s32 unknown00; // Inferred role: max; original member name unknown.
  s32 unknown04; // Inferred role: num; original member name unknown.
  void *m_buffer;
  mm::Mat44 *unknown10; // Inferred role: mats; original member name unknown.
};

static_assert(offsetof(DrResOccUniformObj, m_buffer) == 0x08, "");
static_assert(sizeof(DrResOccUniformObj) == 0x18, "");

} // namespace ml
