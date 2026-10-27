#pragma once
#include <stddef.h>

namespace ml {

class DrMan;

class DrShdCubeCapFilter {
public:
  DrShdCubeCapFilter(DrMan *man);
  ~DrShdCubeCapFilter();

  DrMan *unknown00; // Inferred role: dr manager; original member name unknown.
};

static_assert(offsetof(DrShdCubeCapFilter, unknown00) == 0x00, "");

} // namespace ml
