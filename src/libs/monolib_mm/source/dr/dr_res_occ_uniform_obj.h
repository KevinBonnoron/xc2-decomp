#pragma once
#include <stddef.h>

#include "mm_math/mm_mat44.h"
#include "types.h"

namespace ml {

class DrMan;

class DrResOccUniformObj {
public:
  mm::Mat44 *getMatTbl(int index) { return &m_mats[index]; }
  DrResOccUniformObj(DrMan *drMan, int max);
  ~DrResOccUniformObj();
  void begin();
  void end();
  mm::Mat44 *getMatTbl();

  s32 m_max;
  s32 m_num;
  void *m_buffer;
  mm::Mat44 *m_mats;
};

static_assert(offsetof(DrResOccUniformObj, m_buffer) == 0x08, "");
static_assert(sizeof(DrResOccUniformObj) == 0x18, "");

} // namespace ml
