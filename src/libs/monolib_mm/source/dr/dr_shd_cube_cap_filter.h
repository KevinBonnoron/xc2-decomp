#pragma once
#include <stddef.h>

namespace ml {

class DrMan;

class DrShdCubeCapFilter {
public:
  DrShdCubeCapFilter(DrMan *man);
  ~DrShdCubeCapFilter();

  DrMan *m_drMan; // Inferred role: dr manager; original member name unknown.
};

static_assert(offsetof(DrShdCubeCapFilter, m_drMan) == 0x00, "");

} // namespace ml
