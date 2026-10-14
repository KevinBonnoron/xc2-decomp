#pragma once
#include "mm_mtl/fixed_queue.h"
#include "types.h"

namespace gf {

class GfBdatUniqueMotion {
public:
  struct PresetInfo;

  struct PresetKey {
    u16 ids[6];
  };

  static void queryPreset(mm::mtl::FixedQueue<const PresetInfo *, 32> *presets, const PresetKey &key);
};

} // namespace gf
