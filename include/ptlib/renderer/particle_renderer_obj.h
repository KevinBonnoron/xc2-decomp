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
  bool isOpaque;
  u8 priority;
  f32 depth;
  bool isCapture;
  u8 _09[0x10 - 0x09];
  emitter::EmitterObj *emitter;
};

static_assert(offsetof(EmitterSort, depth) == 0x04, "");
static_assert(offsetof(EmitterSort, isCapture) == 0x08, "");
static_assert(offsetof(EmitterSort, emitter) == 0x10, "");
static_assert(sizeof(EmitterSort) == 0x18, "");

struct Compare {
  bool operator()(const EmitterSort &sort, const EmitterSort &other) const {
    if (sort.priority < other.priority) {
      return true;
    }
    if (sort.priority == other.priority) {
      if (sort.isOpaque > other.isOpaque) {
        return true;
      }
      if (sort.isOpaque == other.isOpaque && sort.depth < other.depth) {
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
