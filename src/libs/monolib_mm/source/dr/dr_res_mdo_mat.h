#pragma once
#include <stddef.h>

#include "mm_math/mm_col4.h"
#include "types.h"

namespace ml {

class DrResMdoMat {
public:
  DrResMdoMat &operator=(const DrResMdoMat &other);
  void setColor(f32 r, f32 g, f32 b, f32 a);
  void setAlpha(f32 alpha);
  void setName(const char *name);

  const char *m_name;
  mm::Col4 m_color;
  u32 m_param0;
  u32 m_param1;
};

static_assert(offsetof(DrResMdoMat, m_color) == 0x08, "");
static_assert(offsetof(DrResMdoMat, m_param0) == 0x18, "");
static_assert(offsetof(DrResMdoMat, m_param1) == 0x1c, "");

} // namespace ml
