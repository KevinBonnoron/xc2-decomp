#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace ptlib {

struct FxParam;

namespace emitter {
class EmitterManager;
class EmitterObj;
} // namespace emitter

namespace renderer {

namespace sort {

struct EmitterSort {
  bool unknown00; // Inferred role: opaque; original member name unknown.
  u8 unknown01;   // Inferred role: priority; original member name unknown.
  f32 unknown04;  // Inferred role: depth; original member name unknown.
  bool unknown08; // Inferred role: capture; original member name unknown.
  u8 _09[0x10 - 0x09];
  emitter::EmitterObj *unknown10; // Inferred role: emitter; original member name unknown.
};

static_assert(offsetof(EmitterSort, unknown04) == 0x04, "");
static_assert(offsetof(EmitterSort, unknown08) == 0x08, "");
static_assert(offsetof(EmitterSort, unknown10) == 0x10, "");
static_assert(sizeof(EmitterSort) == 0x18, "");

struct Compare {
  bool operator()(const EmitterSort &sort, const EmitterSort &other) const {
    if (sort.unknown01 < other.unknown01) {
      return true;
    }
    if (sort.unknown01 == other.unknown01) {
      if (sort.unknown00 > other.unknown00) {
        return true;
      }
      if (sort.unknown00 == other.unknown00 && sort.unknown04 < other.unknown04) {
        return true;
      }
    }
    return false;
  }
};

} // namespace sort

class RenderGrObj {
public:
  static const u32 EMITTER_SORT_MAX = 4000;

  void prioritySort(emitter::EmitterManager &emitterManager, int prioIdx, FxParam &fxParam, mm::mtl::FixedVector<sort::EmitterSort, EMITTER_SORT_MAX> &sorts);
};

} // namespace renderer
} // namespace ptlib
