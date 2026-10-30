#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrMan;
class DrShdFetchObj;

class DrShdFetchMan {
public:
  DrShdFetchMan(DrMan *drMan);
  void releaseFetchObj(DrShdFetchObj *obj);

  DrShdFetchObj *unknown00; // Inferred role: first fetch object; original member name unknown.
  DrShdFetchObj *unknown08; // Inferred role: last fetch object; original member name unknown.
  DrMan *unknown10;         // Inferred role: dr manager; original member name unknown.
  s32 unknown18;            // Inferred role: fetch object count; original member name unknown.
};

static_assert(offsetof(DrShdFetchMan, unknown10) == 0x10, "");
static_assert(offsetof(DrShdFetchMan, unknown18) == 0x18, "");

} // namespace ml
