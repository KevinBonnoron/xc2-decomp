#pragma once
#include <stddef.h>
#include <string.h>
#include <utility>

#include "framework/coli/coli_object.h"
#include "idcoli/idcoli_util_coli.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace idcoli {
class IDColiObj;
} // namespace idcoli

namespace fw {

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

// Name from the game symbols _ZNSt3__16__sortIRN2gf11ContactLessEPN2fw11ContactInfoEEEvT0_S7_T_ (1.0.0: 0x710051fe78), its __sort3/__sort4/__sort5 and insertion sorts (0x71005209bc..0x71005214c0),
// which sort the hits of a TColiCheckResult<256>: searchVertical (0x710051e1e0) calls __sort with the begin of the hit vector and begin + count, and the element stride is 0x50 (`mov w9, #80; madd x1,
// x8, x9, x23`). Layout evidence: the element copies of the sorts move 0x4c bytes (three Vec3 member copies at 0x00, 0x10 and 0x20, then 8-byte words at 0x30, 0x38 and 0x40 and a 4-byte word at
// 0x48), the data size of a class whose last member is the u32 at 0x48; the other members are the ones the ColiCheck functions and TColiCheckResult read. The move constructor: the sorts build their
// swap temporary (`value_type t(std::move(a))`) behind the self-assignment guard of Vec3::operator=(Vec3 &&) (__sort3 +0x74, 0x7100520a30: `mov x11, sp; cmp x11, x0; b.eq` around the three Vec3
// copies, the pointers and the flags copied after it), which the implicit move constructor does not give (Vec3 has no move constructor, so the implicit one copies). Measured: with the move
// constructor below, __sort, __sort3, __sort4, __sort5, __insertion_sort_3 and __insertion_sort_incomplete match the game; without it __sort3 has 408 instructions against 423. The other special
// members are the defaulted ones that a user-declared move constructor deletes.
struct ContactInfo {
  ContactInfo() {}
  ContactInfo(ContactInfo &&other) { *this = std::move(other); }
  ContactInfo(const ContactInfo &) = default;
  ContactInfo &operator=(const ContactInfo &) = default;
  ContactInfo &operator=(ContactInfo &&) = default;

  mm::Vec3 position;
  mm::Vec3 normal;
  mm::Vec3 unknown20;                  // Inferred role: hit vector; original member name unknown.
  const idcoli::unknown250 *unknown30; // Inferred role: material; original member name unknown.
  void *unknown38;                     // Inferred role: user data of the hit object; original member name unknown.
  ColiObject *object;
  u32 unknown48; // Inferred role: hit flags; original member name unknown.
};

static_assert(sizeof(ContactInfo) == 0x50, "");
static_assert(offsetof(ContactInfo, normal) == 0x10, "");
static_assert(offsetof(ContactInfo, unknown20) == 0x20, "");
static_assert(offsetof(ContactInfo, unknown30) == 0x30, "");
static_assert(offsetof(ContactInfo, unknown38) == 0x38, "");
static_assert(offsetof(ContactInfo, object) == 0x40, "");
static_assert(offsetof(ContactInfo, unknown48) == 0x48, "");

template <u32 N> class TColiCheckResult {
public:
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
      const ContactInfo &hit = hits[index];
      if (hit.object != nullptr) {
        return hit.object->m_coliUserData;
      }
    }

    return nullptr;
  }

  // Inferred helper: the user data pointer that the callback stored with a hit (the hit offset 0x38), null for an index out of range; original name unknown.
  // Evidence: EnviromentSensor::searchHorizon (1.0.0: 0x710051eb80, +0x2f8..+0x31c) tests the index against the count, reads [hit + 0x38] and tests it for null before calling its getRTTI.
  void *unknown003(u32 index) const {
    if (index < getCount()) {
      return hits[index].unknown38;
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

  mm::mtl::FixedVector<ContactInfo, N> hits;
  u32 hitCount;
  bool isHit;
};

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
