#pragma once
#include <stddef.h>
#include <string.h>

#include "idcoli/idcoli_util_coli.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace idcoli {
class IDColiObj;
} // namespace idcoli

namespace fw {
class ColiObject;
class ColiUserData;

struct ColiCheckConfig {
  static const u32 FLAG_UNKNOWN_0 = 1 << 0; // Inferred role: test the ground objects; original name unknown.
  static const u32 FLAG_UNKNOWN_1 = 1 << 1; // Inferred role: test the character objects; original name unknown.
  static const u32 FLAG_UNKNOWN_2 = 1 << 2; // Inferred role: test the phantom objects; original name unknown.
  static const u32 FLAG_UNKNOWN_3 = 1 << 3; // Inferred role: test the ground character objects; original name unknown.

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
  // Inferred role: hit; original type name unknown.
  struct unknown001 {
    mm::Vec3 position;
    mm::Vec3 normal;
    mm::Vec3 unknown20;                  // Inferred role: hit vector; original member name unknown.
    const idcoli::unknown250 *unknown30; // Inferred role: material; original member name unknown.
    void *unknown38;                     // Inferred role: user data of the hit object; original member name unknown.
    ColiObject *object;
    u32 unknown48; // Inferred role: hit flags; original member name unknown.
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

  // Inferred helper: user data of the object of a hit, as getHandle reads the handle; original name unknown.
  ColiUserData *unknown002(u32 index) const {
    if (index < getCount()) {
      const unknown001 &hit = hits[index];
      if (hit.object != nullptr) {
        return hit.object->unknown58;
      }
    }

    return nullptr;
  }

  const idcoli::unknown250 &getMaterial(u32 index) const {
    if (index < hitCount) {
      if (hits[index].unknown30 != nullptr) {
        return *hits[index].unknown30;
      }
    }

    static bool bInitialized = false;
    static idcoli::unknown250 nullData;
    if (!bInitialized) {
      memset(&nullData, 0, sizeof(nullData));
      bInitialized = true;
    }

    return nullData;
  }

  mm::mtl::FixedVector<unknown001, N> hits;
  u32 hitCount;
  bool isHit;
};

static_assert(sizeof(TColiCheckResult<256>::unknown001) == 0x50, "");
static_assert(offsetof(TColiCheckResult<256>::unknown001, unknown30) == 0x30, "");
static_assert(offsetof(TColiCheckResult<256>::unknown001, unknown38) == 0x38, "");
static_assert(offsetof(TColiCheckResult<256>::unknown001, object) == 0x40, "");
static_assert(offsetof(TColiCheckResult<256>::unknown001, unknown48) == 0x48, "");
static_assert(offsetof(TColiCheckResult<256>, hitCount) == 0x5010, "");
static_assert(offsetof(TColiCheckResult<256>, isHit) == 0x5014, "");

class ColiCheckCallback : public idcoli::IDColiCallBack {
public:
  static const u32 HIT_FLAG_UNKNOWN_2 = 1 << 2; // Inferred role: set on every hit; original name unknown.
  static const u32 HIT_FLAG_UNKNOWN_3 = 1 << 3; // Inferred role: the hit object was found; original name unknown.

  static int m_prevWarningFrame;

  explicit ColiCheckCallback(TColiCheckResult<256> &result) : unknown08(&result) {}

  void coli_callback(void *userData) override;
  void coli_param_callback(void *userData, const idcoli::IDColiCallArg &arg) override;

  TColiCheckResult<256> *unknown08; // Inferred role: result the hits are added to; original member name unknown.
  bool unknown10;                   // Inferred role: take the hit vector of the callback argument; original member name unknown.
};

static_assert(offsetof(ColiCheckCallback, unknown08) == 0x8, "");
static_assert(offsetof(ColiCheckCallback, unknown10) == 0x10, "");
static_assert(sizeof(ColiCheckCallback) == 0x18, "");

class ColiCheck {
public:
  static bool testLine(TColiCheckResult<256> &result, const mm::Vec3 &start, const mm::Vec3 &end, const ColiCheckConfig &config);
  static bool testLineChara(TColiCheckResult<256> &result, const mm::Vec3 &start, const mm::Vec3 &end, const ColiCheckConfig &config);
  static bool testLinePhantom(TColiCheckResult<256> &result, const mm::Vec3 &start, const mm::Vec3 &end, const ColiCheckConfig &config);
  static bool testLineColi(TColiCheckResult<256> &result, const idcoli::IDColiObj *object, const mm::Vec3 &start, const mm::Vec3 &end, const ColiCheckConfig &config);
  static bool testRay(TColiCheckResult<256> &result, const mm::Vec3 &start, const mm::Vec3 &direction, f32 length, f32 backLength, const ColiCheckConfig &config);
  static bool testRayChara(TColiCheckResult<256> &result, const mm::Vec3 &start, const mm::Vec3 &direction, f32 length, f32 backLength, const ColiCheckConfig &config);
  static bool testRayPhantom(TColiCheckResult<256> &result, const mm::Vec3 &start, const mm::Vec3 &direction, f32 length, f32 backLength, const ColiCheckConfig &config);
  static bool testRayColi(TColiCheckResult<256> &result, const idcoli::IDColiObj *object, const mm::Vec3 &start, const mm::Vec3 &direction, f32 length, f32 backLength, const ColiCheckConfig &config);
  static bool testSphere(TColiCheckResult<256> &result, const mm::Vec3 &center, f32 radius, const ColiCheckConfig &config);
  static bool testSphereChara(TColiCheckResult<256> &result, const mm::Vec3 &center, f32 radius, const ColiCheckConfig &config);
  static bool testSpherePhantom(TColiCheckResult<256> &result, const mm::Vec3 &center, f32 radius, const ColiCheckConfig &config);
  static bool testSphereColi(TColiCheckResult<256> &result, const idcoli::IDColiObj *object, const mm::Vec3 &center, f32 radius, const ColiCheckConfig &config);
  static bool testCapsule(TColiCheckResult<256> &result, const mm::Vec3 &start, const mm::Vec3 &end, f32 radius, const ColiCheckConfig &config);
  static bool testCapsuleChara(TColiCheckResult<256> &result, const mm::Vec3 &start, const mm::Vec3 &end, f32 radius, const ColiCheckConfig &config);
  static bool testCapsulePhantom(TColiCheckResult<256> &result, const mm::Vec3 &start, const mm::Vec3 &end, f32 radius, const ColiCheckConfig &config);
  static bool testCapsuleColi(TColiCheckResult<256> &result, const idcoli::IDColiObj *object, const mm::Vec3 &start, const mm::Vec3 &end, f32 radius, const ColiCheckConfig &config);
  static bool testObject(TColiCheckResult<256> &result, ColiObject *object, const ColiCheckConfig &config);
  static bool testObjectChara(TColiCheckResult<256> &result, ColiObject *object, const ColiCheckConfig &config);
  static bool testObjectPhantom(TColiCheckResult<256> &result, ColiObject *object, const ColiCheckConfig &config);
  static ColiObject *getObjectFromUserData(u32 handle);
  static bool moveColi(mm::Vec3 &result, const mm::Vec3 &position, const mm::Vec3 &move);
  static bool getSnapPos(mm::Vec3 &result, const mm::Vec3 &position, f32 distance, u32 mask);
};

} // namespace fw
