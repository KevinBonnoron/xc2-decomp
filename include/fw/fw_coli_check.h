#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace fw {
class ColiObject;

struct ColiCheckConfig {
  u32 unknown00;  // Inferred role: flags; original member name unknown.
  u32 unknown04;  // Inferred role: attribute mask; original member name unknown.
  f32 unknown08;  // Inferred role: length; original member name unknown.
  f32 unknown0c;  // Inferred role: margin; original member name unknown.
  u32 unknown10;  // Inferred role: result mode; original member name unknown.
  bool unknown14; // Inferred role: flag14; original member name unknown.
  bool unknown15; // Inferred role: flag15; original member name unknown.
};

static_assert(offsetof(ColiCheckConfig, unknown10) == 0x10, "");
static_assert(offsetof(ColiCheckConfig, unknown15) == 0x15, "");

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
  static bool testLineChara(TColiCheckResult<256> &result, const mm::Vec3 &start, const mm::Vec3 &end, const ColiCheckConfig &config);
  static bool testLine(TColiCheckResult<256> &result, const mm::Vec3 &start, const mm::Vec3 &end, const ColiCheckConfig &config);
  static bool testObjectChara(TColiCheckResult<256> &result, ColiObject *object, const ColiCheckConfig &config);
  static bool testObjectPhantom(TColiCheckResult<256> &result, ColiObject *object, const ColiCheckConfig &config);
  static ColiObject *getObjectFromUserData(u32 handle);
  static bool moveColi(mm::Vec3 &result, const mm::Vec3 &position, const mm::Vec3 &move);
  static bool getSnapPos(mm::Vec3 &result, const mm::Vec3 &position, f32 distance, u32 mask);
};

} // namespace fw
