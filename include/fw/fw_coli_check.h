#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace fw {
class ColiObject;

struct ColiCheckConfig {
  u32 flags;
  u32 attributeMask;
  f32 length;
  f32 margin;
  u32 resultMode;
  bool flag14;
  bool flag15;
};

static_assert(offsetof(ColiCheckConfig, resultMode) == 0x10, "");
static_assert(offsetof(ColiCheckConfig, flag15) == 0x15, "");

template <u32 N> class TColiCheckResult {
public:
  struct Hit {
    mm::Vec3 position;
    mm::Vec3 normal;
    u8 _20[0x40 - 0x20];
    ColiObject *object;
    u8 _48[0x50 - 0x48];
  };

  TColiCheckResult() : hitCount(0), isHit(false) {}

  void clear() {
    isHit = false;
    hits.clear();
    hitCount = 0;
  }

  u32 getCount() const { return hits.size(); }

  const mm::Vec3 &getPosition(u32 index) const {
    if (index < getCount()) {
      return hits[index].position;
    }

    return mm::Vec3::zero;
  }

  const mm::Vec3 &getNormal(u32 index) const {
    if (index < getCount()) {
      return hits[index].normal;
    }

    return mm::Vec3::zero;
  }

  u32 getHandle(u32 index) const {
    if (index < getCount()) {
      if (hits[index].object != nullptr) {
        return hits[index].object->userData.handle;
      }
    }

    return 0;
  }

  mm::mtl::FixedVector<Hit, N> hits;
  u32 hitCount;
  bool isHit;
};

static_assert(sizeof(TColiCheckResult<256>::Hit) == 0x50, "");
static_assert(offsetof(TColiCheckResult<256>, hitCount) == 0x5010, "");
static_assert(offsetof(TColiCheckResult<256>, isHit) == 0x5014, "");

class ColiCheck {
public:
  static bool testObjectChara(TColiCheckResult<256> &result, ColiObject *object, const ColiCheckConfig &config);
  static bool testObjectPhantom(TColiCheckResult<256> &result, ColiObject *object, const ColiCheckConfig &config);
  static bool getSnapPos(mm::Vec3 &result, const mm::Vec3 &position, f32 distance, u32 mask);
};

} // namespace fw
