#pragma once
#include <stddef.h>

namespace ml {

class DrShdMdoDecShdObj;

class DrShdMdoMan {
public:
  DrShdMdoMan();
  void update();

  DrShdMdoDecShdObj *unknown00; // Inferred role: first shader object; original member name unknown.
  DrShdMdoDecShdObj *unknown08; // Inferred role: last shader object; original member name unknown.
};

static_assert(offsetof(DrShdMdoMan, unknown08) == 0x08, "");

} // namespace ml
